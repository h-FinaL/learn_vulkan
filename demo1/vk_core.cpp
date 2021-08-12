#include "vk_core.h"

VkInstance vk_core::create_instance()
{
	VkApplicationInfo app_info{};
	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pApplicationName = _context->_app_name.c_str();
	app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.pEngineName = "No Engine";
	app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo create_info{};
	create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	create_info.pApplicationInfo = &app_info;
	create_info.ppEnabledExtensionNames = glfwGetRequiredInstanceExtensions(&create_info.enabledExtensionCount);
	create_info.enabledLayerCount = 0;

	if (vkCreateInstance(&create_info, nullptr, &_instance) != VK_SUCCESS) {
		throw std::runtime_error("failed to create instance!");
	}
}

VkPhysicalDevice vk_core::create_gpu()
{
	uint32_t count = 0;
	vkEnumeratePhysicalDevices(_instance, &count, nullptr);

	if (count == 0)
	{
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}
	std::vector<VkPhysicalDevice> gpus;
	gpus.resize(count);
	vkEnumeratePhysicalDevices(_instance, &count, gpus.data());

	return gpus[_context->_chooes_device];
}

VkDevice vk_core::create_device()
{
	VkPhysicalDeviceFeatures required_features{};
	required_features.multiDrawIndirect = _context->_device_features.multiDrawIndirect;
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

	VkDevice device;
	vkCreateDevice(_gpu, &device_create, nullptr, &device);

	return device;
}

VkQueue vk_core::create_que()
{
	VkQueue que{ VK_NULL_HANDLE };

	return que;
}


VkBuffer vk_core::create_buffer()
{
	VkBufferCreateInfo buf_create{};
	buf_create.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	buf_create.pNext = nullptr;
	buf_create.flags = 0;
	buf_create.size = 1024 * 1024;
	buf_create.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
	buf_create.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	buf_create.queueFamilyIndexCount = 0;
	buf_create.pQueueFamilyIndices = nullptr;

	VkBuffer buffer;
	vkCreateBuffer(_device, &buf_create, nullptr, &buffer);

	return buffer;
}

VkCommandPool vk_core::create_pool()
{
	VkCommandPoolCreateInfo info{};
	info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	info.queueFamilyIndex = 0;
	
	VkCommandPool pool;
	vkCreateCommandPool(_device, &info, nullptr, &pool);

	return pool;
}