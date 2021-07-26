#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "vk_layer_extension.h"

class vk_instance
{
public:
	VkResult create_instance(std::vector<const char*>& layers,
		std::vector<const char* >& extensions,
		const char* applicationName);

private:
	VkInstance _instance;
	vk_layer_extension _layer_extension;
};

