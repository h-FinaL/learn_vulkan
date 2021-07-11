#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>
#include <stdexcept>

class vk_device
{
public:
	vk_device(const vk_device&) = delete;
	void operator=(const vk_device&) = delete;

	vk_device() {}
	vk_device(vk_device&& device) noexcept
	{
		_physical_device = device._physical_device;
		_propertie = device._propertie;
		_family_properties = std::move(device._family_properties);
		_supported_features = device._supported_features;
		_logical_device = device._logical_device;
		_buffer = device._buffer;

		device._logical_device = VK_NULL_HANDLE;
		device._buffer = VK_NULL_HANDLE;
	}

	~vk_device() 
	{
		destroy_device();
	}

	void destroy_device()
	{
		if (_logical_device != nullptr)
		{
			vkDeviceWaitIdle(_logical_device);
			vkDestroyDevice(_logical_device, nullptr);
		}
	}

	void init(vk_device& device)
	{

		_physical_device = device._physical_device;
		_propertie = device._propertie;
		_family_properties = device._family_properties;
		_supported_features = device._supported_features;

		VkPhysicalDeviceFeatures required_features{};
		required_features.multiDrawIndirect = _supported_features.multiDrawIndirect;
		required_features.tessellationShader = VK_TRUE;
		required_features.geometryShader = VK_TRUE;
		_device_create_info.pEnabledFeatures = &required_features;
		vkCreateDevice(_physical_device, &_device_create_info, nullptr, &_logical_device);
		vkCreateBuffer(_logical_device, &_buffer_create_info, nullptr, &_buffer);

		device.destroy_device();
	}

	void init(VkInstance instance)
	{
		uint32_t count = 0;
		vkEnumeratePhysicalDevices(instance, &count, nullptr);

		if (count == 0)
		{
			throw std::runtime_error("failed to find GPUs with Vulkan support!");
		}

		std::vector<VkPhysicalDevice> physical_devices;
		physical_devices.resize(count);
		vkEnumeratePhysicalDevices(instance, &count, physical_devices.data());

		_all_deviecs.resize(count);

		for (int i = 0; i < count; i++)
		{
			_all_deviecs[i].init_self(physical_devices[i]);
		}

		init(_all_deviecs[0]);
	}


private:
	void init_self(VkPhysicalDevice physical_device)
	{
		init_device_create_info();

		_physical_device = physical_device;
		vkGetPhysicalDeviceProperties(physical_device, &_propertie);

		_family_properties = init_family_properties(physical_device);
		vkGetPhysicalDeviceFeatures(physical_device, &_supported_features);
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
		_device_create_info.ppEnabledLayerNames = nullptr;
		_device_create_info.enabledExtensionCount = 0;
		_device_create_info.ppEnabledExtensionNames = nullptr;
		_device_create_info.pEnabledFeatures = nullptr;
	}

	void init_device_queue_create_info()
	{
		_device_queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
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
	VkDeviceQueueCreateInfo _device_queue_create_info{};
	VkDeviceCreateInfo _device_create_info{};
	VkBufferCreateInfo _buffer_create_info{};

	//物理设备
	VkPhysicalDevice _physical_device = VK_NULL_HANDLE;
	//逻辑设备
	VkDevice _logical_device = VK_NULL_HANDLE;
	//设备信息
	VkPhysicalDeviceProperties _propertie{};
	//队列族信息
	std::vector<VkQueueFamilyProperties> _family_properties;
	//物理设备特性
	VkPhysicalDeviceFeatures _supported_features;
	//设备缓存
	VkBuffer _buffer = VK_NULL_HANDLE;

	//所有设备
	std::vector<vk_device> _all_deviecs;
};