#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <stdexcept>
#include <vector>
#include <iostream>

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

	vulkan_app(vulkan_app&) = delete;
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

		VkApplicationInfo app_info{};
		init_app_info(app_info);

		VkInstanceCreateInfo create_info{};
		init_create_info(create_info, app_info);

		if (vkCreateInstance(&create_info, nullptr, &instance) != VK_SUCCESS) {
			throw std::runtime_error("failed to create instance!");
		}

		init_extensions();
	}

	void init_app_info(VkApplicationInfo& app_info)
	{
		app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		app_info.pApplicationName = "Hello Triangle";
		app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		app_info.pEngineName = "No Engine";
		app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		app_info.apiVersion = VK_API_VERSION_1_0;
	}

	void init_create_info(VkInstanceCreateInfo& create_info, VkApplicationInfo& app_info)
	{
		create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		create_info.pApplicationInfo = &app_info;

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		create_info.enabledExtensionCount = glfwExtensionCount;
		create_info.ppEnabledExtensionNames = glfwExtensions;
		create_info.enabledLayerCount = 0;
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

	VkInstance instance;
	std::vector<VkExtensionProperties> extensions;
};