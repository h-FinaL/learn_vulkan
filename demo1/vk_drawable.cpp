#include "vk_drawable.h"

#include <thread>

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

void vk_drawable::prepare()
{
	_cmd_draws.resize(_render->_swap_chain.scPublicVars.colorBuffer.size());

	for (int i = 0; i < _render->_swap_chain.scPublicVars.colorBuffer.size(); i++)
	{
		_buffer.alloc_command_buffer(&_cmd_draws[i]);
		_buffer.begin_command_buffer(_cmd_draws[i]);

		record_command_buffer(i, &_cmd_draws[i]);

		_buffer.end_command_buffer(_cmd_draws[i]);
	}
}

void vk_drawable::record_command_buffer(int current_image, VkCommandBuffer* cmd_draw)
{
	// 设置清除颜色值
	VkClearValue clear_values[2];
	clear_values[0].color.float32[0] = 0.0f;
	clear_values[0].color.float32[1] = 0.0f;
	clear_values[0].color.float32[2] = 0.0f;
	clear_values[0].color.float32[3] = 0.0f;

	clear_values[1].depthStencil.depth = 1.0f;
	clear_values[1].depthStencil.stencil = 0;

	VkRenderPassBeginInfo render_pass_begin{};
	render_pass_begin.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	render_pass_begin.renderPass = _render->_render_pass;
	render_pass_begin.framebuffer = _render->_frame_buffers[current_image];
	render_pass_begin.renderArea.offset.x = 0;
	render_pass_begin.renderArea.offset.y = 0;
	render_pass_begin.renderArea.extent.width = _render->get_width();
	render_pass_begin.renderArea.extent.height = _render->get_height();
	render_pass_begin.clearValueCount = 2;
	render_pass_begin.pClearValues = clear_values;

	//开始录制渲染通道实例
	vkCmdBeginRenderPass(*cmd_draw, &render_pass_begin, VK_SUBPASS_CONTENTS_INLINE);

	// 绑定流水线对象
	vkCmdBindPipeline(*cmd_draw, VK_PIPELINE_BIND_POINT_GRAPHICS, *_pipeline);

	// 绑定顶点缓存与指令缓存
	const VkDeviceSize offsets[1] = { 0 };
	vkCmdBindVertexBuffers(*cmd_draw, 0, 1, &vertex_buffer.buffer, offsets);

	//定义动态视口
	init_viewports(cmd_draw);

	//裁剪
	init_scissors(cmd_draw);

	//完成渲染通道实例录制
	vkCmdEndRenderPass(*cmd_draw);
}

//渲染可绘制对象
void vk_drawable::render()
{
	VkDevice device = _core->_device;
	
	uint32_t& current_color_image = _render->_swap_chain.scPublicVars.currentColorBuffer;
	VkSwapchainKHR& swap_chain = _render->_swap_chain.scPublicVars.swapChain;


	VkFence null_fence = VK_NULL_HANDLE;

	std::this_thread::sleep_for(std::chrono::seconds(1));
	//获取下一个可用的交换链图像索引
	VkResult rs = _render->_swap_chain.fpAcquireNextImageKHR(_core->_device, swap_chain,
		UINT64_MAX, VK_NULL_HANDLE, VK_NULL_HANDLE, &current_color_image);


	VkPipelineStageFlags submit_pipeline_stage_flags = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

	VkSubmitInfo submit_info{};
	submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submit_info.pNext = nullptr;
	submit_info.waitSemaphoreCount = 1;
	submit_info.pWaitSemaphores = &_present_complete_semaphore;
	submit_info.pWaitDstStageMask = &submit_pipeline_stage_flags;
	submit_info.commandBufferCount = (uint32_t)sizeof(&_cmd_draws[current_color_image]) / sizeof(VkCommandBuffer);
	submit_info.pCommandBuffers = &_cmd_draws[current_color_image];
	submit_info.signalSemaphoreCount = 1;
	submit_info.pSignalSemaphores = &_drawing_complete_semaphore;

	_buffer.submit_command_buffer(_core->_que, &_cmd_draws[current_color_image], nullptr);

	VkPresentInfoKHR present{};
	present.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	present.pNext = nullptr;
	present.swapchainCount = 1;
	present.pSwapchains = &swap_chain;
	present.pImageIndices = &current_color_image;
	present.pWaitSemaphores = &_drawing_complete_semaphore;
	present.waitSemaphoreCount = 1;
	present.pResults = nullptr;
	rs = _render->_swap_chain.fpQueuePresentKHR(_core->_que, &present);

	rs = _render->_swap_chain.fpQueuePresentKHR(_core->_que, &present);
}

void vk_drawable::init_viewports(VkCommandBuffer* cmd)
{
	viewport.height = _render->get_height();
	viewport.width = _render->get_width();
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	viewport.x = 0;
	viewport.y = 0;
	vkCmdSetViewport(*cmd, 0, 1, &viewport);
}

void vk_drawable::init_scissors(VkCommandBuffer* cmd)
{
	_scissor.extent.width = _render->get_width();
	_scissor.extent.height = _render->get_height();
	_scissor.offset.x = 0;
	_scissor.offset.y = 0;
	vkCmdSetScissor(*cmd, 0, 1, &_scissor);
}
