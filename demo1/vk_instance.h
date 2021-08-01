#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "vk_led.h"

class vk_context;
class vk_instance
{
public:
	vk_instance(vk_instance&) = delete;
	vk_instance operator=(vk_instance&) = delete;

	vk_instance(vk_context* context);

	VkInstance get_instance() { return _instance; }

private:
	VkResult init();

private:
	VkInstance _instance{ VK_NULL_HANDLE };

	vk_context* _context{ nullptr };
	vk_led* _led{ nullptr };
};

