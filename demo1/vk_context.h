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

struct device_props
{
	device_props(VkPhysicalDevice gpu);
	//�豸����
	VkPhysicalDeviceProperties _properties{};
	//�����豸����
	VkPhysicalDeviceFeatures _features{};
	//��������Ϣ
	std::vector<VkQueueFamilyProperties> _que_family_props;
};

struct ld_props
{
	ld_props(VkLayerProperties props, VkInstance instance, VkPhysicalDevice gpu);

	VkLayerProperties _props;
	std::vector<VkExtensionProperties> _instance_extension;
	std::vector<VkExtensionProperties> _device_extension;
};

class vk_context
{

public:

	vk_allocator _allocator;
	vk_led _led;
	vk_instance _instance{ this };
	vk_device _device{ this };

	vk_context();

private:
	//������ʱʵ��
	VkInstance create_temp_instance();
	//��ȡ��ʱ�����豸
	std::vector<VkPhysicalDevice> create_temp_physical_devices(VkInstance instance);
	//��ȡ���еĲ�
	void available_layers();
	//��ȡ����ʵ��֧�ֵ���չ
	void all_instance_extension();

public:
	//����ʵ������
	std::vector<device_props> _device_props;
	//������֤�����չ����
	std::vector<ld_props> _ld_props;

	//�豸����
	VkPhysicalDeviceProperties _device_properties{};
	//�����豸����
	VkPhysicalDeviceFeatures _device_features{};
	//��������Ϣ
	std::vector<VkQueueFamilyProperties> _device_que_family_props;
	//ѡ�������豸
	int _chooes_device = 0;

	//���õ���֤��
	std::vector<VkLayerProperties> _available_layers;
	//���õ���֤��
	std::vector<const char*> _validation_layers;
	//�Ƿ�������֤��
	bool enable_validation_layers{ false };


	//Ӧ������
	std::string _app_name{ "vulkan" };
	//���
	int _width{ 0 };
	//����
	int _height{ 0 };
};

