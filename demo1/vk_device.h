#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>
#include <stdexcept>

class vk_device
{
public:
	vk_device() {}
	~vk_device() 
	{
		for (auto& device : _devices)
		{
			vkDeviceWaitIdle(device._logical_device);
			vkDestroyDevice(device._logical_device, nullptr);
		}
	}

	void init(VkInstance instance)
	{
		uint32_t count = 0;
		vkEnumeratePhysicalDevices(instance, &count, nullptr);

		if (count == 0)
		{
			throw std::runtime_error("failed to find GPUs with Vulkan support!");
		}

		std::vector<VkPhysicalDevice> physical_devices(count);
		vkEnumeratePhysicalDevices(instance, &count, physical_devices.data());

		init_device_create_info();

		_devices.resize(count);

		int i = 0;
		for (auto& physical_device : physical_devices)
		{
			_devices[i]._physical_device = physical_device;
			vkGetPhysicalDeviceProperties(physical_device, &_devices[i]._propertie);

			_devices[i]._family_properties = init_family_properties(physical_device);
			vkGetPhysicalDeviceFeatures(physical_device, &_devices[i]._supported_features);

			VkPhysicalDeviceFeatures required_features;
			required_features.multiDrawIndirect = _devices[i]._supported_features.multiDrawIndirect;
			required_features.tessellationShader = VK_TRUE;
			required_features.geometryShader = VK_TRUE;
			_device_create_info.pEnabledFeatures = &required_features;

			vkCreateDevice(physical_device, &_device_create_info, nullptr, &_devices[i]._logical_device);

			vkCreateBuffer(_devices[i]._logical_device, &_buffer_create_info, nullptr, &_devices[i]._buffer);

			i++;
		}
	}

	std::vector<VkQueueFamilyProperties> init_family_properties(VkPhysicalDevice physical_device)
	{
		std::vector<VkQueueFamilyProperties> family_properties;

		uint32_t count = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &count, nullptr);

		family_properties.resize(count);
		vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &count, family_properties.data());

		return family_properties;
	}

	void init_device_create_info()
	{
		init_device_queue_create_info();

		_device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		_device_create_info.pNext = nullptr;
		_device_create_info.flags = 0;
		_device_create_info.queueCreateInfoCount = 1;
		_device_create_info.pQueueCreateInfos = &_device_queue_create_info;
		_device_create_info.enabledLayerCount = 0;
		_device_create_info.ppEnabledExtensionNames = 0;
		_device_create_info.pEnabledFeatures = nullptr;
	}

	void init_device_queue_create_info()
	{
		_device_queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		_device_queue_create_info.pNext = nullptr;
		_device_queue_create_info.flags = 0;
		_device_queue_create_info.queueFamilyIndex = 0;
		_device_queue_create_info.queueCount = 1;
		_device_queue_create_info.pQueuePriorities = nullptr;
	}

	void init_buffer_create_info()
	{
		_buffer_create_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		_buffer_create_info.pNext = nullptr;
		_buffer_create_info.flags = 0;
		_buffer_create_info.size = 1024 * 1024;
		_buffer_create_info.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
		_buffer_create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		_buffer_create_info.queueFamilyIndexCount = 0;
		_buffer_create_info.pQueueFamilyIndices = nullptr;
	}

private:
	struct info
	{
		VkPhysicalDevice _physical_device = VK_NULL_HANDLE;
		VkDevice _logical_device = VK_NULL_HANDLE;
		VkPhysicalDeviceProperties _propertie{};
		std::vector<VkQueueFamilyProperties> _family_properties;
		VkPhysicalDeviceFeatures _supported_features;
		VkBuffer _buffer = VK_NULL_HANDLE;
	};

	std::vector<info> _devices;
	VkDeviceQueueCreateInfo _device_queue_create_info{};
	VkDeviceCreateInfo _device_create_info{};
	VkBufferCreateInfo _buffer_create_info{};
};