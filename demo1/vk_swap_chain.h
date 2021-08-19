#pragma once

#include <vulkan/vulkan.h>
#include "vk_core.h"

class vk_render;

struct SwapChainBuffer {
	VkImage image;
	VkImageView view;
};


struct SwapChainPrivateVariables
{
	// Store the image surface capabilities
	VkSurfaceCapabilitiesKHR	surfCapabilities;

	// Stores the number of present mode support by the implementation
	uint32_t					presentModeCount;

	// Arrays for retrived present modes
	std::vector<VkPresentModeKHR> presentModes;

	// Size of the swap chain color images
	VkExtent2D					swapChainExtent;

	// Number of color images supported by the implementation
	uint32_t					desiredNumberOfSwapChainImages;

	VkSurfaceTransformFlagBitsKHR preTransform;

	// Stores present mode bitwise flag for the creation of swap chain
	VkPresentModeKHR			swapchainPresentMode;

	// The retrived drawing color swap chain images
	std::vector<VkImage>		swapchainImages;

	std::vector<VkSurfaceFormatKHR> surfFormats;
};

struct SwapChainPublicVariables
{
	// The logical platform dependent surface object
	VkSurfaceKHR surface;

	// Number of buffer image used for swap chain
	uint32_t swapchainImageCount;

	// Swap chain object
	VkSwapchainKHR swapChain;

	// List of color swap chain images
	std::vector<SwapChainBuffer> colorBuffer;

	// Semaphore for sync purpose
	VkSemaphore presentCompleteSemaphore;

	// Current drawing surface index in use
	uint32_t currentColorBuffer;

	// Format of the image 
	VkFormat format;
};

class vk_swap_chain
{
public:
	vk_swap_chain(vk_core* core, vk_render* render);
	~vk_swap_chain() {};

	void init_swap_chain();
	void createSwapChain(const VkCommandBuffer& cmd);

private:
	VkResult createSwapChainExtensions();
	void getSupportedFormats();
	VkResult createSurface();
	uint32_t getGraphicsQueueWithPresentationSupport() 
	{
		uint32_t queueCount = _core->_queue_count;
		VkPhysicalDevice gpu = _core->_gpu;
		std::vector<VkQueueFamilyProperties>& queueProps = _core->_context->_device_que_family_props;

		// Iterate over each queue and get presentation status for each.
		VkBool32* supportsPresent = (VkBool32*)malloc(queueCount * sizeof(VkBool32));
		for (uint32_t i = 0; i < queueCount; i++) {
			fpGetPhysicalDeviceSurfaceSupportKHR(gpu, i, scPublicVars.surface, &supportsPresent[i]);
		}

		// Search for a graphics queue and a present queue in the array of queue
		// families, try to find one that supports both
		uint32_t graphicsQueueNodeIndex = UINT32_MAX;
		uint32_t presentQueueNodeIndex = UINT32_MAX;
		for (uint32_t i = 0; i < queueCount; i++) {
			if ((queueProps[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0) {
				if (graphicsQueueNodeIndex == UINT32_MAX) {
					graphicsQueueNodeIndex = i;
				}

				if (supportsPresent[i] == VK_TRUE) {
					graphicsQueueNodeIndex = i;
					presentQueueNodeIndex = i;
					break;
				}
			}
		}

		if (presentQueueNodeIndex == UINT32_MAX) {
			// If didn't find a queue that supports both graphics and present, then
			// find a separate present queue.
			for (uint32_t i = 0; i < queueCount; ++i) {
				if (supportsPresent[i] == VK_TRUE) {
					presentQueueNodeIndex = i;
					break;
				}
			}
		}

		free(supportsPresent);

		// Generate error if could not find both a graphics and a present queue
		if (graphicsQueueNodeIndex == UINT32_MAX || presentQueueNodeIndex == UINT32_MAX) {
			return  UINT32_MAX;
		}

		return graphicsQueueNodeIndex;
	}

	void getSurfaceCapabilitiesAndPresentMode();
	void managePresentMode();
	void createSwapChainColorImages();
	void createColorImageView(const VkCommandBuffer& cmd);

	PFN_vkGetPhysicalDeviceSurfaceSupportKHR		fpGetPhysicalDeviceSurfaceSupportKHR;
	PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR	fpGetPhysicalDeviceSurfaceCapabilitiesKHR;
	PFN_vkGetPhysicalDeviceSurfaceFormatsKHR		fpGetPhysicalDeviceSurfaceFormatsKHR;
	PFN_vkGetPhysicalDeviceSurfacePresentModesKHR	fpGetPhysicalDeviceSurfacePresentModesKHR;
	PFN_vkQueuePresentKHR		fpQueuePresentKHR;
	PFN_vkAcquireNextImageKHR	fpAcquireNextImageKHR;
	PFN_vkDestroySurfaceKHR							fpDestroySurfaceKHR;

	// Layer Extensions Debugging
	PFN_vkCreateSwapchainKHR	fpCreateSwapchainKHR;
	PFN_vkDestroySwapchainKHR	fpDestroySwapchainKHR;
	PFN_vkGetSwapchainImagesKHR fpGetSwapchainImagesKHR;

	SwapChainPublicVariables	scPublicVars;
	SwapChainPrivateVariables	scPrivateVars;
	vk_render* _renderer;	// parent
	vk_core* _core;
};

