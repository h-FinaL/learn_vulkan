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
	VkPhysicalDevice _gpu{ VK_NULL_HANDLE }; //物理设备

	VkPhysicalDeviceProperties _props{};  //设备属性
	std::vector<VkQueueFamilyProperties> _que_family_props;  //队列族信息
	VkPhysicalDeviceFeatures _supported_features{};  //物理设备特性

	VkDevice _device{ VK_NULL_HANDLE };  //逻辑设备
	VkQueue _que{ VK_NULL_HANDLE };  //队列对象
	VkBuffer _buffer{ VK_NULL_HANDLE };  //设备缓存

	vk_context* _context;
};