#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>

#include <string>
#include <vector>

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
	//�����豸�ڴ���Ϣ
	VkPhysicalDeviceMemoryProperties _memory_props;
	//ѡ�������豸
	int _chooes_device = 0;

	//���õ���֤��
	std::vector<VkLayerProperties> _available_layers;
	//���õ���֤��
	std::vector<const char*> _validation_layers{
		"VK_LAYER_KHRONOS_validation",
		"VK_LAYER_LUNARG_api_dump"
	};
	std::vector<const char*> _instance_extension_names{
		VK_KHR_SURFACE_EXTENSION_NAME,
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
		VK_EXT_DEBUG_REPORT_EXTENSION_NAME
	};
	std::vector<const char*> _device_extension_names{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};
	//�Ƿ�������֤��
	bool enable_validation_layers{ false };


	//Ӧ������
	std::string _app_name{ "vulkan" };
	//���
	int _width{ 0 };
	//����
	int _height{ 0 };
};

