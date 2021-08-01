#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <vulkan/vulkan.h>

class vk_device;
class vk_instance;
class vk_led;
class vk_allocator;

class vk_context
{
friend class vk_device;
friend class vk_instance;
friend class vk_led;

public:
	vk_context(const vk_context&) = delete;
	void operator=(const vk_context&) = delete;

	vk_context()
	{
		
	}

private:
	vk_allocator* _allocator{ nullptr };
	vk_led* _led{ nullptr };
	vk_instance* _instance{ nullptr };
	vk_device* _gpu{ nullptr };

};

