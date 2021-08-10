#pragma once

#include <vulkan/vulkan.h>
#include <vector>

enum vk_layer_name
{
	VK_LAUER_GOOGLE_unique_objects,
	VK_LAUER_LUNARG_api_dump,
	VK_LAUER_LUNARG_core_validation,
	VK_LAUER_LUNARG_image,
	VK_LAUER_LUNARG_object_tracker,
	VK_LAUER_LUNARG_parameter_validation,
	VK_LAUER_LUNARG_swapchain,
	VK_LAUER_GOOGLE_threading,
	VK_LAUER_LUNARG_standard_validation,
};

struct vk_layer_properties
{
	VkLayerProperties properties{};
	std::vector<VkExtensionProperties> extensions;
};

class vk_led
{
public:
	vk_led();
	~vk_led() {};

	std::vector<vk_layer_properties> get_instance_layer_properties();

	VkResult get_extension_properties(vk_layer_properties& layer_pros, VkPhysicalDevice gpu = nullptr);

	VkResult get_device_extension_properties(VkPhysicalDevice* gpu) {}

	bool are_layers_supported(std::vector<vk_layer_name>& vk_layers);

	VkLayerProperties properties{};
	std::vector<VkExtensionProperties> extensions;

	std::vector<vk_layer_properties> _layer_property_list;

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugFunction(VkFlags msgFlags,
		VkDebugReportObjectTypeEXT objType,
		uint64_t srcObject,
		size_t location,
		int32_t msgCode,
		const char* layerPrefix,
		const char* msg,
		void* userData);

	VkResult create_debug_report_callback();
	void	destroyDebugReportCallback();

	PFN_vkCreateDebugReportCallbackEXT _dbg_create_debug_report_callback;
	PFN_vkDestroyDebugReportCallbackEXT _dbg_destroy_debug_report_callback;
	VkDebugReportCallbackCreateInfoEXT _dbg_report_create_fnfo = {};

	VkDebugReportCallbackEXT _debug_report_callback;
	VkDebugReportCallbackCreateInfoEXT _dbg_report_create_callback{};
};