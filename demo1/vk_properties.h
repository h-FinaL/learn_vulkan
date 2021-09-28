#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>

class vk_device_properties
{
public:
	static std::vector< vk_device_properties> all_device_properties(VkInstance instance) {}

	VkPhysicalDeviceProperties& properties() { return _properties; }

	VkPhysicalDeviceFeatures& features() { return _features; }

	std::vector<VkQueueFamilyProperties>& queue_family_properties() { return _queue_family_properties; }

private:
	vk_device_properties(VkPhysicalDevice gpu);

	//设备属性
	VkPhysicalDeviceProperties _properties{};
	//物理设备特性
	VkPhysicalDeviceFeatures _features{};
	//队列族信息
	std::vector<VkQueueFamilyProperties> _queue_family_properties;
	//扩展信息
	std::vector<VkExtensionProperties> _extensions;
};

class vk_properties
{
public:
    vk_properties(){}
    ~vk_properties(){}

private:

	struct layer_extension
	{
		std::vector<layer_extension>& layer_extensions(VkInstance instance) {}

		VkLayerProperties _available_layers;
		std::vector<VkExtensionProperties> _instance_extension;
		std::vector<VkExtensionProperties> _device_extension;
	};

	//可用的验证层
	std::vector<VkLayerProperties> _available_layers;
	std::vector<VkExtensionProperties> _instance_extension;
	std::vector<VkExtensionProperties> _device_extension;

	//设备属性
	VkPhysicalDeviceProperties _device_properties{};
	//物理设备特性
	VkPhysicalDeviceFeatures _device_features{};
	//队列族信息
	std::vector<VkQueueFamilyProperties> _device_que_family_props;
	//物理设备内存信息
	VkPhysicalDeviceMemoryProperties _memory_props;

};