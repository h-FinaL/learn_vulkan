#pragma once

#include "vk_core.h"

class vk_buffer
{
public:
	vk_buffer(vk_core* core) :
		_pool(core->_pool),
		_device(core->_device)
	{}

	void alloc_command_buffer(VkCommandBuffer* cmdBuf, const VkCommandBufferAllocateInfo* commandBufferInfo = NULL);

	void begin_command_buffer(VkCommandBuffer cmdBuf, VkCommandBufferBeginInfo* inCmdBufInfo = NULL);

	void end_command_buffer(VkCommandBuffer cmdBuf);

	void submit_command_buffer(const VkQueue& queue,
		const VkCommandBuffer* cmdBufList,
		const VkSubmitInfo* submitInfo = NULL,
		const VkFence& fence = VK_NULL_HANDLE);


private:
	VkDevice _device;
	VkCommandPool _pool;
};

