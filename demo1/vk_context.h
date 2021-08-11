#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <vulkan/vulkan.h>

#include <string>
#include <vector>

#include "vk_allocator.h"
#include "vk_led.h"
#include "vk_instance.h"
#include "vk_device.h"

struct layer_extension
{
	VkLayerProperties _property;
};

struct vk_context
{
public:
	//vk_context(const vk_context&) = delete;
	//void operator=(const vk_context&) = delete;

	vk_allocator _allocator;
	vk_led _led;
	vk_instance _instance{ this };
	vk_device _device{ this };

	vk_context();

	//应用名称
	std::string _app_name{ "vulkan" };
	//宽度
	int _width{ 0 };
	//长度
	int _height{ 0 };

	//是否开启扩展
	bool _open_extension{ false };

	//层和扩展
	typedef std::vector<std::vector<VkExtensionProperties>> extensions;

	std::vector<VkLayerProperties> _layer_props;
	extensions _instance_extensions;

	struct device_properties
	{
		VkPhysicalDeviceProperties _properties{};  //设备属性
		VkPhysicalDeviceFeatures _supported_features{};  //物理设备特性
		std::vector<VkQueueFamilyProperties> _que_family_props;  //队列族信息
		extensions _extension;
	};
	std::vector<device_properties> _device_properties;
};

