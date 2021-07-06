#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <stdexcept>
#include <vector>
#include <iostream>

#include "vk_device.h"

class vulkan_app
{
public:
	vulkan_app() 
	{
		init();
	}
	~vulkan_app() 
	{
		cleanup();
	}

	vulkan_app(const vulkan_app&) = delete;
	void operator=(vulkan_app&) = delete;

	void run()
	{
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
		}
	}

private:
	void init() 
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		window = glfwCreateWindow(800, 600, "Vulkan", nullptr, nullptr);

		init_vulkan();
	}

	void init_vulkan()
	{
		create_instance();
		pickPhysicalDevice();
	}

	void pickPhysicalDevice() 
	{
		devices.init(instance);
	}

	void create_instance()
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

		if (vkCreateInstance(&create_info, nullptr, &instance) != VK_SUCCESS) {
			throw std::runtime_error("failed to create instance!");
		}

		init_extensions();
	}


	void init_extensions()
	{
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

		extensions.resize(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

		std::cout << "available extensions:\n";
		for (const auto& extension : extensions) {
			std::cout << '\t' << extension.extensionName << '\n';
		}
	}

	void cleanup() 
	{
		vkDestroyInstance(instance, nullptr);
		glfwDestroyWindow(window);
		glfwTerminate();
	}



private:

	uint32_t width = 800;
	uint32_t height = 600;
	GLFWwindow* window = nullptr;

	std::vector<VkExtensionProperties> extensions;

	VkInstance instance;
	vk_device devices;
};