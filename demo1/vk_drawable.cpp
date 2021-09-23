#include "vk_drawable.h"

void vk_drawable::create_vertex_buffer(const void* vertex_data,
	uint32_t data_size,
	uint32_t data_stride,
	bool use_texture)
{
	VkResult result;
	bool pass;

	VkBufferCreateInfo buf_info{};
	buf_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	buf_info.pNext = NULL;
	buf_info.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	buf_info.size = data_size;
	buf_info.queueFamilyIndexCount = 0;
	buf_info.pQueueFamilyIndices = nullptr;
	buf_info.sharingMode = VK_SHARING_MODE_CONCURRENT;
	buf_info.flags = 0;

	result = vkCreateBuffer(_core->_device, &buf_info, nullptr, &vertex_buffer.buffer);

	VkMemoryRequirements mem_rqrmnt;
	vkGetBufferMemoryRequirements(_core->_device, vertex_buffer.buffer, &mem_rqrmnt);

	VkMemoryAllocateInfo alloc_info{};
	alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	alloc_info.pNext = nullptr;
	alloc_info.memoryTypeIndex = 0;
	alloc_info.allocationSize = mem_rqrmnt.size;

	pass = _core->memoryTypeFromProperties(mem_rqrmnt.memoryTypeBits,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		&alloc_info.memoryTypeIndex);

	result = vkAllocateMemory(_core->_device, &alloc_info, nullptr, &vertex_buffer.memory);

	vertex_buffer.buffer_info.range = mem_rqrmnt.size;
	vertex_buffer.buffer_info.offset = 0;

	uint8_t* data;
	result = vkMapMemory(_core->_device, vertex_buffer.memory, 0, mem_rqrmnt.size, 0, (void**)&data);

	memcpy(data, vertex_data, data_size);

	vkUnmapMemory(_core->_device, vertex_buffer.memory);

	result = vkBindBufferMemory(_core->_device, vertex_buffer.buffer, vertex_buffer.memory, 0);

	viIpBind.binding = 0;
	viIpBind.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	viIpBind.stride = data_stride;

	viIpAttrb[0].binding = 0;
	viIpAttrb[0].location = 0;
	viIpAttrb[0].format = VK_FORMAT_R32G32B32A32_SFLOAT;
	viIpAttrb[0].offset = 0;

	viIpAttrb[1].binding = 0;
	viIpAttrb[1].location = 1;
	viIpAttrb[1].format = use_texture ? VK_FORMAT_R32G32_SFLOAT : VK_FORMAT_R32G32B32A32_SFLOAT;
	viIpAttrb[1].offset = 16;
}