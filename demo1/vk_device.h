#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>
#include <stdexcept>

class vk_device
{
public:
	vk_device(const vk_device&) = delete;
	void operator=(const vk_device&) = delete;

	vk_device() = default;

	vk_device(vk_device&& device) noexcept;
	~vk_device() { destroy_device(); }

	void destroy_device();
	void init(vk_device& device);
	void init(VkInstance instance);

	VkPhysicalDevice get_device() { return _gpu; }


private:
	void init_attribute(VkPhysicalDevice physical_device);

private:
	VkPhysicalDevice _gpu{ VK_NULL_HANDLE }; //物理设备

	VkPhysicalDeviceProperties _props{};  //设备属性
	std::vector<VkQueueFamilyProperties> _que_family_props;  //队列族信息
	VkPhysicalDeviceFeatures _supported_features{};  //物理设备特性

	VkDevice _device{ VK_NULL_HANDLE };  //逻辑设备
	VkQueue _que{ VK_NULL_HANDLE };  //队列对象
	VkBuffer _buffer{ VK_NULL_HANDLE };  //设备缓存

	//所有设备
	std::vector<vk_device> _all_deviecs;
};