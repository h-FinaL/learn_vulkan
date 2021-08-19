#include "vk_context.h"

#include <vulkan/vulkan_core.h>


device_props::device_props(VkPhysicalDevice gpu)
{
	vkGetPhysicalDeviceProperties(gpu, &_properties);
	vkGetPhysicalDeviceFeatures(gpu, &_features);

	uint32_t count = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(gpu, &count, nullptr);
	_que_family_props.resize(count);
	vkGetPhysicalDeviceQueueFamilyProperties(gpu, &count, _que_family_props.data());
}

ld_props::ld_props(VkLayerProperties props, VkInstance instance, VkPhysicalDevice gpu) :
	_props(props)
{
	uint32_t count;
	vkEnumerateInstanceExtensionProperties(_props.layerName, &count, nullptr);
	_instance_extension.resize(count);
	vkEnumerateInstanceExtensionProperties(_props.layerName, &count, _instance_extension.data());

	vkEnumerateDeviceExtensionProperties(gpu, _props.layerName, &count, nullptr);
	_device_extension.resize(count);
	vkEnumerateDeviceExtensionProperties(gpu, _props.layerName, &count, _device_extension.data());
}

vk_context::vk_context()
{
	VkInstance _instance = create_temp_instance();
	std::vector<VkPhysicalDevice>  _gpus = create_temp_physical_devices(_instance);
	available_layers();

	for (auto& gpu : _gpus)
		_device_props.emplace_back(gpu);

	for (auto& layer : _available_layers)
		_ld_props.emplace_back(layer, _instance, _gpus[0]);

	_device_properties = _device_props[0]._properties;
	_device_que_family_props = _device_props[0]._que_family_props;

	vkDestroyInstance(_instance, nullptr);
}


VkInstance vk_context::create_temp_instance()
{
	VkApplicationInfo app_info{};
	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;

	VkInstanceCreateInfo create_info{};
	create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	create_info.pApplicationInfo = &app_info;

	VkInstance instance;
	vkCreateInstance(&create_info, nullptr, &instance);

	return instance;
}

std::vector<VkPhysicalDevice> vk_context::create_temp_physical_devices(VkInstance instance)
{
	uint32_t count = 0;
	vkEnumeratePhysicalDevices(instance, &count, nullptr);

	std::vector<VkPhysicalDevice> physical_devices;
	physical_devices.resize(count);
	vkEnumeratePhysicalDevices(instance, &count, physical_devices.data());
	vkGetPhysicalDeviceMemoryProperties(physical_devices[0], &_memory_props);

	return physical_devices;
}

void vk_context::available_layers()
{
	uint32_t count;
	vkEnumerateInstanceLayerProperties(&count, nullptr);
	_available_layers.resize(count);
	vkEnumerateInstanceLayerProperties(&count, _available_layers.data());
}

void vk_context::all_instance_extension()
{
	//for (auto& layer : _available_layers)
	//{
	//	_instance_extensions.push_back(std::vector<VkExtensionProperties>());
	//	auto& extension = _instance_extensions.back();
	//	uint32_t n;
	//	vkEnumerateInstanceExtensionProperties(layer.layerName, &n, nullptr);
	//	extension.resize(n);
	//	vkEnumerateInstanceExtensionProperties(layer.layerName, &n, extension.data());
	//}
}