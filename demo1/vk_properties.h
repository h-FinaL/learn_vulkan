#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>

class vk_device_properties
{
public:
	static std::vector< vk_device_properties> all_device_properties(VkInstance instance) {}

	VkPhysicalDeviceProperties& properties() { return _properties; }

	VkPhysicalDeviceFeatures& features() { return _features; }

	std::vector<VkQueueFamilyProperties>& queue_family_properties() { return _queue_family_properties; }

private:
	vk_device_properties(VkPhysicalDevice gpu);

	//�豸����
	VkPhysicalDeviceProperties _properties{};
	//�����豸����
	VkPhysicalDeviceFeatures _features{};
	//��������Ϣ
	std::vector<VkQueueFamilyProperties> _queue_family_properties;
	//��չ��Ϣ
	std::vector<VkExtensionProperties> _extensions;
};

class vk_properties
{
public:
    vk_properties(){}
    ~vk_properties(){}

private:

	struct layer_extension
	{
		std::vector<layer_extension>& layer_extensions(VkInstance instance) {}

		VkLayerProperties _available_layers;
		std::vector<VkExtensionProperties> _instance_extension;
		std::vector<VkExtensionProperties> _device_extension;
	};

	//���õ���֤��
	std::vector<VkLayerProperties> _available_layers;
	std::vector<VkExtensionProperties> _instance_extension;
	std::vector<VkExtensionProperties> _device_extension;

	//�豸����
	VkPhysicalDeviceProperties _device_properties{};
	//�����豸����
	VkPhysicalDeviceFeatures _device_features{};
	//��������Ϣ
	std::vector<VkQueueFamilyProperties> _device_que_family_props;
	//�����豸�ڴ���Ϣ
	VkPhysicalDeviceMemoryProperties _memory_props;

};