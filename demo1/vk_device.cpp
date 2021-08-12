#include "vk_device.h"
#include "vk_instance.h"
#include "vk_context.h"

vk_device::vk_device(vk_context* context) :
	_context(context)
{
	init();
}


vk_device::~vk_device() 
{
	vkDeviceWaitIdle(_device);
	vkDestroyDevice(_device, nullptr);
}

void vk_device::init()
{
	vk_instance* instance = &_context->_instance;

	uint32_t count = 0;
	vkEnumeratePhysicalDevices(instance->get_instance(), &count, nullptr);

	if (count == 0)
	{
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}

	std::vector<VkPhysicalDevice> gpus;
	gpus.resize(count);
	vkEnumeratePhysicalDevices(instance->get_instance(), &count, gpus.data());

	//_all_deviecs.resize(count);

	//for (int i = 0; i < count; i++)
	//{
	//	_all_deviecs[i].init_attribute(physical_devices[i]);
	//}

	//init(_all_deviecs[0]);

	init_attribute(gpus[0]);

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

	//vkGetDeviceQueue(_device, _graphics_queue_with_present_index, 0, &_que);
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
