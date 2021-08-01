#include "vk_buffer.h"


void vk_buffer::allocCommandBuffer(const VkDevice* device,
	const VkCommandPool cmdPool,
	VkCommandBuffer* cmdBuf,
	const VkCommandBufferAllocateInfo*
	commandBufferInfo)
{
	VkResult result;
	if (commandBufferInfo)
	{
		result = vkAllocateCommandBuffers(*device, commandBufferInfo, cmdBuf);
		return;
	}

	VkCommandBufferAllocateInfo cmd_info{};
	cmd_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	cmd_info.pNext = NULL;
	cmd_info.commandPool = cmdPool;
	cmd_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	cmd_info.commandBufferCount = (uint32_t)sizeof(cmdBuf) / sizeof(VkCommandBuffer);

	result = vkAllocateCommandBuffers(*device, &cmd_info, cmdBuf);
}

void vk_buffer::beginCommandBuffer(VkCommandBuffer cmdBuf,
	VkCommandBufferBeginInfo* inCmdBufInfo)
{
	VkResult result;
	if (inCmdBufInfo)
	{
		result = vkBeginCommandBuffer(cmdBuf, inCmdBufInfo);
		return;
	}

	VkCommandBufferInheritanceInfo cmd_buf_inherit_info{};
	cmd_buf_inherit_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
	cmd_buf_inherit_info.pNext = NULL;
	cmd_buf_inherit_info.renderPass = VK_NULL_HANDLE;
	cmd_buf_inherit_info.subpass = 0;
	cmd_buf_inherit_info.framebuffer = VK_NULL_HANDLE;
	cmd_buf_inherit_info.occlusionQueryEnable = VK_FALSE;
	cmd_buf_inherit_info.queryFlags = 0;
	cmd_buf_inherit_info.pipelineStatistics = 0;

	VkCommandBufferBeginInfo cmdBufInfo = {};
	cmdBufInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	cmdBufInfo.pNext = NULL;
	cmdBufInfo.flags = 0;
	cmdBufInfo.pInheritanceInfo = &cmd_buf_inherit_info;

	result = vkBeginCommandBuffer(cmdBuf, &cmdBufInfo);
}

void vk_buffer::endCommandBuffer(VkCommandBuffer cmdBuf)
{
	VkResult result;
	result = vkEndCommandBuffer(cmdBuf);
}

void vk_buffer::submitCommandBuffer(const VkQueue& queue,
	const VkCommandBuffer* cmdBufList,
	const VkSubmitInfo* in_submit_info,
	const VkFence& fence)
{
	VkResult result;
	if (in_submit_info)
	{
		vkQueueSubmit(queue, 1, in_submit_info, fence);
		result = vkQueueWaitIdle(queue);
	}

	VkSubmitInfo submit_info{};
	submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submit_info.pNext = NULL;
	submit_info.waitSemaphoreCount = 0;
	submit_info.pWaitSemaphores = NULL;
	submit_info.pWaitDstStageMask = NULL;
	submit_info.commandBufferCount = (uint32_t)sizeof(cmdBufList) / sizeof(VkCommandBuffer);
	submit_info.pCommandBuffers = cmdBufList;
	submit_info.signalSemaphoreCount = 0;
	submit_info.pSignalSemaphores = NULL;

	result = vkQueueSubmit(queue, 1, &submit_info, fence);

	result = vkQueueWaitIdle(queue);
}