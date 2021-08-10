#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <vulkan/vulkan.h>

#include "vk_allocator.h"
#include "vk_led.h"
#include "vk_instance.h"
#include "vk_device.h"

enum vk_layer
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

struct vk_context
{

public:
	//vk_context(const vk_context&) = delete;
	//void operator=(const vk_context&) = delete;

	//vk_allocator _allocator;
	//vk_led _led;
	//vk_instance _instance{ this };
	//vk_device _device{ this };

	//应用名称
	const char _app_name[32]{ "vulkan" };
	//宽度
	int _width{ 0 };
	//长度
	int _height{ 0 };

	//扩展
	vk_layer _extensions[16];
	int _extensions_num{ 0 };
};

