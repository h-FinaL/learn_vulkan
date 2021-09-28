#include "vk_properties.h"


std::vector<vk_device_properties> vk_device_properties::all_device_properties(VkInstance instance)
{
	uint32_t count = 0;
	std::vector<VkPhysicalDevice> physical_devices;

	vkEnumeratePhysicalDevices(instance, &count, nullptr);
	physical_devices.resize(count);
	vkEnumeratePhysicalDevices(instance, &count, physical_devices.data());

	std::vector<vk_device_properties> device_properties;
	for (auto& gpu : physical_devices)
	{
		device_properties.emplace_back(gpu);
	}

	return std::move(device_properties);
}

vk_device_properties::vk_device_properties(VkPhysicalDevice gpu)
{
	vkGetPhysicalDeviceProperties(gpu, &_properties);
	vkGetPhysicalDeviceFeatures(gpu, &_features);

	uint32_t count = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(gpu, &count, nullptr);
	_queue_family_properties.resize(count);
	vkGetPhysicalDeviceQueueFamilyProperties(gpu, &count, _queue_family_properties.data());
}