#pragma once

#include <vulkan/vulkan_core.h>
#include "vk_context.h"

class vk_core
{
public:
	vk_core(vk_context& context) :
		_context(context)
	{}

	vk_context _context;

	//实例
	VkInstance _instance{ VK_NULL_HANDLE }; 
	//物理设备
	VkPhysicalDevice _gpu{ VK_NULL_HANDLE };
	//逻辑设备
	VkDevice _device{ VK_NULL_HANDLE };
	//队列对象
	VkQueue _que{ VK_NULL_HANDLE };
	//设备缓存
	VkBuffer _buffer{ VK_NULL_HANDLE };
};