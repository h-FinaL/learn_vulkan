#include "vk_context.h"

#include <vulkan/vulkan_core.h>

vk_context::vk_context()
{
	VkApplicationInfo app_info{};
	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo create_info{};
	create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	create_info.pApplicationInfo = &app_info;

	VkInstance instance;
	vkCreateInstance(&create_info, nullptr, &instance);

	uint32_t count;
	vkEnumerateInstanceLayerProperties(&count, nullptr);
	_layer_props.resize(count);
	vkEnumerateInstanceLayerProperties(&count, _layer_props.data());

	//_instance_extensions.resize(count);

	vkEnumeratePhysicalDevices(instance, &count, nullptr);
	std::vector<VkPhysicalDevice> gpus;
	gpus.resize(count);
	vkEnumeratePhysicalDevices(instance, &count, gpus.data());

	for (auto& layer_prop : _layer_props)
	{
		_instance_extensions.push_back(std::vector< VkExtensionProperties>());
		auto& extension = _instance_extensions.back();
		uint32_t n;
		vkEnumerateInstanceExtensionProperties(layer_prop.layerName, &n, nullptr);
		extension.resize(n);
		vkEnumerateInstanceExtensionProperties(layer_prop.layerName, &n, extension.data());

	}


	vkDestroyInstance(instance, nullptr);
}