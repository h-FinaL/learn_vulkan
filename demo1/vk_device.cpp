#include "vk_device.h"


vk_device::vk_device(vk_device&& device) noexcept
{
	_gpu = device._gpu;
	_props = device._props;
	_que_family_props = std::move(device._que_family_props);
	_supported_features = device._supported_features;
	_device = device._device;
	_buffer = device._buffer;

	device._device = VK_NULL_HANDLE;
	device._buffer = VK_NULL_HANDLE;
}

void vk_device::destroy_device()
{
	if (_device != nullptr)
	{
		vkDeviceWaitIdle(_device);
		vkDestroyDevice(_device, nullptr);
	}
}

void vk_device::init(vk_device& device)
{

	_gpu = device._gpu;
	_props = device._props;
	_que_family_props = device._que_family_props;
	_supported_features = device._supported_features;

	VkPhysicalDeviceFeatures required_features{};
	required_features.multiDrawIndirect = _supported_features.multiDrawIndirect;
	required_features.tessellationShader = VK_TRUE;
	required_features.geometryShader = VK_TRUE;

	VkDeviceQueueCreateInfo que_create{};
	que_create.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	que_create.pNext = nullptr;
	que_create.flags = 0;
	que_create.queueFamilyIndex = 0;
	que_create.queueCount = 1;
	que_create.pQueuePriorities = nullptr;

	VkDeviceCreateInfo device_create{};
	device_create.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	device_create.pNext = nullptr;
	device_create.flags = 0;
	device_create.queueCreateInfoCount = 1;
	device_create.pQueueCreateInfos = &que_create;
	device_create.enabledLayerCount = 0;
	device_create.ppEnabledLayerNames = nullptr;
	device_create.enabledExtensionCount = 0;
	device_create.ppEnabledExtensionNames = nullptr;
	device_create.pEnabledFeatures = nullptr;

	device_create.pEnabledFeatures = &required_features;
	vkCreateDevice(_gpu, &device_create, nullptr, &_device);


	VkBufferCreateInfo buf_create{};
	buf_create.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	buf_create.pNext = nullptr;
	buf_create.flags = 0;
	buf_create.size = 1024 * 1024;
	buf_create.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
	buf_create.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	buf_create.queueFamilyIndexCount = 0;
	buf_create.pQueueFamilyIndices = nullptr;
	vkCreateBuffer(_device, &buf_create, nullptr, &_buffer);

	device.destroy_device();
}

void vk_device::init(VkInstance instance)
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
		_all_deviecs[i].init_attribute(physical_devices[i]);
	}

	init(_all_deviecs[0]);
}

void vk_device::init_attribute(VkPhysicalDevice gpu)
{
	_gpu = gpu;
	vkGetPhysicalDeviceProperties(gpu, &_props);

	uint32_t count = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(gpu, &count, nullptr);
	_que_family_props.resize(count);
	vkGetPhysicalDeviceQueueFamilyProperties(gpu, &count, _que_family_props.data());

	vkGetPhysicalDeviceFeatures(gpu, &_supported_features);
}
