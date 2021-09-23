#pragma once

#include <vulkan/vulkan.h>

#include "vk_core.h"

class vk_drawable
{
public:
	vk_drawable(vk_core* core) : _core(core) {}
	void create_vertex_buffer(const void* vertex_data, 
		uint32_t data_size, 
		uint32_t data_stride, 
		bool use_texture);


	struct {
		VkBuffer buffer;
		VkDeviceMemory memory;
		VkDescriptorBufferInfo buffer_info;
	} vertex_buffer;

	VkVertexInputBindingDescription viIpBind;
	VkVertexInputAttributeDescription viIpAttrb[2];

	vk_core* _core;
};

