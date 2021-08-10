#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>
#include <stdexcept>

class vk_context;
class vk_device
{
public:
	vk_device(const vk_device&) = delete;
	void operator=(const vk_device&) = delete;

	vk_device(vk_context* context);
	~vk_device();

	VkDevice get_device() { return _device; }
	VkPhysicalDevice get_gpu() { return _gpu; }
	uint32_t get_queue_index() { return _graphics_queue_with_present_index; }
	VkQueue get_queue() { return _que; }

	void set_queue_index(uint32_t index) { _graphics_queue_with_present_index = index; }

private:
	void init();
	void init_attribute(VkPhysicalDevice physical_device);

private:
	VkPhysicalDevice _gpu{ VK_NULL_HANDLE }; //�����豸

	VkPhysicalDeviceProperties _props{};  //�豸����
	std::vector<VkQueueFamilyProperties> _que_family_props;  //��������Ϣ
	VkPhysicalDeviceFeatures _supported_features{};  //�����豸����

	VkDevice _device{ VK_NULL_HANDLE };  //�߼��豸
	VkQueue _que{ VK_NULL_HANDLE };  //���ж���
	VkBuffer _buffer{ VK_NULL_HANDLE };  //�豸����

	uint32_t _graphics_queue_with_present_index;

	vk_context* _context;
};