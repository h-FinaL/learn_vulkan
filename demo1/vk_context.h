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

	//Ӧ������
	std::string _app_name{ "vulkan" };
	//���
	int _width{ 0 };
	//����
	int _height{ 0 };

	//�Ƿ�����չ
	bool _open_extension{ false };

	//�����չ
	typedef std::vector<std::vector<VkExtensionProperties>> extensions;

	std::vector<VkLayerProperties> _layer_props;
	extensions _instance_extensions;

	struct device_properties
	{
		VkPhysicalDeviceProperties _properties{};  //�豸����
		VkPhysicalDeviceFeatures _supported_features{};  //�����豸����
		std::vector<VkQueueFamilyProperties> _que_family_props;  //��������Ϣ
		extensions _extension;
	};
	std::vector<device_properties> _device_properties;
};

