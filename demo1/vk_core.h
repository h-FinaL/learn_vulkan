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

	//ʵ��
	VkInstance _instance{ VK_NULL_HANDLE }; 
	//�����豸
	VkPhysicalDevice _gpu{ VK_NULL_HANDLE };
	//�߼��豸
	VkDevice _device{ VK_NULL_HANDLE };
	//���ж���
	VkQueue _que{ VK_NULL_HANDLE };
	//�豸����
	VkBuffer _buffer{ VK_NULL_HANDLE };
};