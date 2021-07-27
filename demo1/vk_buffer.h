#pragma once

#include <vulkan/vulkan.h>

class vk_buffer
{
public:
	static void allocCommandBuffer(const VkDevice* device, 
		const VkCommandPool cmdPool, 
		VkCommandBuffer* cmdBuf,
		const VkCommandBufferAllocateInfo*
		commandBufferInfo = NULL);

	static void beginCommandBuffer(VkCommandBuffer cmdBuf, 
		VkCommandBufferBeginInfo* inCmdBufInfo = NULL);

	static void endCommandBuffer(VkCommandBuffer cmdBuf);

	static void submitCommandBuffer(const VkQueue& queue, 
		const VkCommandBuffer* cmdBufList,
		const VkSubmitInfo* submitInfo = NULL,
		const VkFence& fence = VK_NULL_HANDLE);


private:

};

