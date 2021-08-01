#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>
#include <stdexcept>
#include "vk_context.h"

class vk_device
{
public:
	vk_device(const vk_device&) = delete;
	void operator=(const vk_device&) = delete;

	vk_device(vk_context* context);
	~vk_device();

	VkPhysicalDevice get_device() { return _gpu; }


private:
	void init();
	void init_attribute(VkPhysicalDevice physical_device);

private:
	VkPhysicalDevice _gpu{ VK_NULL_HANDLE }; //�����豸

	VkPhysicalDeviceProperties _props{};  //�豸����
	std::vector<VkQueueFamilyProperties> _que_family_props;  //��������Ϣ
	VkPhysicalDeviceFeatures _supported_features{};  //�����豸����

	VkDevice _device{ VK_NULL_HANDLE };  //�߼��豸
	VkQueue _que{ VK_NULL_HANDLE };  //���ж���
	VkBuffer _buffer{ VK_NULL_HANDLE };  //�豸����

	vk_context* _context;
};