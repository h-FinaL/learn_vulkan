#include "vk_led.h"

#include <iostream>
#include <string>

const char* layer_name_str[] = {
	"VK_LAUER_GOOGLE_unique_objects",
	"VK_LAUER_LUNARG_api_dump",
	"VK_LAUER_LUNARG_core_validation",
	"VK_LAUER_LUNARG_image",
	"VK_LAUER_LUNARG_object_tracker",
	"VK_LAUER_LUNARG_parameter_validation",
	"VK_LAUER_LUNARG_swapchain",
	"VK_LAUER_GOOGLE_threading",
	"VK_LAUER_LUNARG_standard_validation"
};


vk_led::vk_led() 
{
	uint32_t instance_layer_cout;
	vkEnumerateInstanceLayerProperties(&instance_layer_cout, nullptr);

	std::vector<VkLayerProperties> properties;
	properties.resize(instance_layer_cout);
	vkEnumerateInstanceLayerProperties(&instance_layer_cout, properties.data());
}

std::vector<vk_layer_properties> vk_led::get_instance_layer_properties()
{
	std::vector<vk_layer_properties> layer_properties_list;

	uint32_t instance_layer_cout;
	vkEnumerateInstanceLayerProperties(&instance_layer_cout, nullptr);

	std::vector<VkLayerProperties> properties;
	properties.resize(instance_layer_cout);
	vkEnumerateInstanceLayerProperties(&instance_layer_cout, properties.data());

	for (auto& global_layer_prop : properties)
	{
		printf("\n%s\n\t|\n\t|--[Layer Name]--> %s\n", global_layer_prop.description, global_layer_prop.layerName);

		vk_layer_properties layer_props;
		layer_props.properties = global_layer_prop;

		get_extension_properties(layer_props);

		layer_properties_list.push_back(layer_props);

		for (auto j : layer_props.extensions)
		{
			printf("\t\t|\n\t\t|--[Layer Extension]-->%s\n", j.extensionName);
		}
	}

	return layer_properties_list;
}


VkResult vk_led::get_extension_properties(vk_layer_properties& layer_pros, VkPhysicalDevice gpu)
{
	uint32_t extension_count;
	VkResult result;
	char* layer_name = layer_pros.properties.layerName;

	do
	{
		if (gpu)
		{
			result = vkEnumerateDeviceExtensionProperties(gpu, layer_name, &extension_count, nullptr);
		}
		else
		{
			result = vkEnumerateInstanceExtensionProperties(layer_name, &extension_count, nullptr);
		}

		if (result || extension_count == 0)
			continue;

		layer_pros.extensions.resize(extension_count);

		if (gpu)
		{
			result = vkEnumerateDeviceExtensionProperties(gpu, layer_name, &extension_count, layer_pros.extensions.data());
		}
		else
		{
			result = vkEnumerateInstanceExtensionProperties(layer_name, &extension_count, layer_pros.extensions.data());
		}

	} while (result == VK_INCOMPLETE);

	return result;
}

bool vk_led::are_layers_supported(std::vector<vk_layer_name>& layer_name)
{
	uint32_t check_cout = layer_name.size();
	uint32_t layer_cout = _layer_property_list.size();

	std::vector<const char*> un_support_layer_names;

	for (auto& name : layer_name)
	{
		for (uint32_t j = 0; j < layer_cout; j++)
		{
			if (!strcmp(layer_name_str[name], _layer_property_list[j].properties.layerName))
			{
				un_support_layer_names.push_back(layer_name_str[name]);
			}
			else
			{

			}
		}
	}

	return false;
}


VKAPI_ATTR VkBool32 VKAPI_CALL
vk_led::debugFunction(VkFlags msgFlags, VkDebugReportObjectTypeEXT objType,
	uint64_t srcObject, size_t location, int32_t msgCode,
	const char* layerPrefix, const char* msg, void* userData) {

	if (msgFlags & VK_DEBUG_REPORT_ERROR_BIT_EXT) {
		std::cout << "[VK_DEBUG_REPORT] ERROR: [" << layerPrefix << "] Code" << msgCode << ":" << msg << std::endl;
	}
	else if (msgFlags & VK_DEBUG_REPORT_WARNING_BIT_EXT) {
		std::cout << "[VK_DEBUG_REPORT] WARNING: [" << layerPrefix << "] Code" << msgCode << ":" << msg << std::endl;
	}
	else if (msgFlags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT) {
		std::cout << "[VK_DEBUG_REPORT] INFORMATION: [" << layerPrefix << "] Code" << msgCode << ":" << msg << std::endl;
	}
	else if (msgFlags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT) {
		std::cout << "[VK_DEBUG_REPORT] PERFORMANCE: [" << layerPrefix << "] Code" << msgCode << ":" << msg << std::endl;
	}
	else if (msgFlags & VK_DEBUG_REPORT_DEBUG_BIT_EXT) {
		std::cout << "[VK_DEBUG_REPORT] DEBUG: [" << layerPrefix << "] Code" << msgCode << ":" << msg << std::endl;
	}
	else {
		return VK_FALSE;
	}

	fflush(stdout);
	return VK_TRUE;
}

VkResult vk_led::create_debug_report_callback()
{

	VkInstance instance = VK_NULL_HANDLE;

	_dbg_create_debug_report_callback = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
	if (!_dbg_create_debug_report_callback) {
		std::cout << "Error: GetInstanceProcAddr unable to locate vkCreateDebugReportCallbackEXT function." << std::endl;
		return VK_ERROR_INITIALIZATION_FAILED;
	}
	std::cout << "GetInstanceProcAddr loaded dbgCreateDebugReportCallback function\n";

	// Get vkDestroyDebugReportCallbackEXT API
	_dbg_destroy_debug_report_callback = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
	if (!_dbg_destroy_debug_report_callback) {
		std::cout << "Error: GetInstanceProcAddr unable to locate vkDestroyDebugReportCallbackEXT function." << std::endl;
		return VK_ERROR_INITIALIZATION_FAILED;
	}
	std::cout << "GetInstanceProcAddr loaded dbgDestroyDebugReportCallback function\n";

	_dbg_report_create_fnfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
	_dbg_report_create_fnfo.pfnCallback = debugFunction;
	_dbg_report_create_fnfo.pUserData = NULL;
	_dbg_report_create_fnfo.pNext = NULL;
	_dbg_report_create_fnfo.flags = VK_DEBUG_REPORT_WARNING_BIT_EXT |
		VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
		VK_DEBUG_REPORT_ERROR_BIT_EXT |
		VK_DEBUG_REPORT_DEBUG_BIT_EXT;
}

void vk_led::destroyDebugReportCallback()
{
}