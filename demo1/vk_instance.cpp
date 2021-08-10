#include "vk_instance.h"
#include "vk_context.h"
#include "GLFW/glfw3.h"
#include <stdexcept>


vk_instance::vk_instance(vk_context* context) :
	_context(context)
{
	if (_context == nullptr)
		return;

	_led = &_context->_led;

	init();
}

VkResult vk_instance::init()
{

	VkApplicationInfo app_info{};
	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pApplicationName = "Hello Triangle";
	app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.pEngineName = "No Engine";
	app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo create_info{};
	create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	create_info.pApplicationInfo = &app_info;
	create_info.ppEnabledExtensionNames = glfwGetRequiredInstanceExtensions(&create_info.enabledExtensionCount);
	create_info.enabledLayerCount = 0;

	if (vkCreateInstance(&create_info, nullptr, &_instance) != VK_SUCCESS) {
		throw std::runtime_error("failed to create instance!");
	}
}