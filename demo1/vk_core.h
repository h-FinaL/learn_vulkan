#pragma once

#include <vulkan/vulkan_core.h>
#include "vk_context.h"

class vk_core
{
public:
	vk_core(vk_context& context) :
		_context(&context)
	{
		_instance = create_instance();
		_gpu = create_gpu();
		_device = create_device();
		_que = create_que();
		_buffer = create_buffer();
		_pool = create_pool();
	}

private:
	VkInstance create_instance();
	VkPhysicalDevice create_gpu();
	VkDevice create_device();
	VkQueue create_que();
	VkBuffer create_buffer();
	VkCommandPool create_pool();

public:
	vk_context* _context;

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
	//ָ���
	VkCommandPool _pool{ VK_NULL_HANDLE };
};