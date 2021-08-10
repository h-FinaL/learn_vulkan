#pragma once

#include <vulkan/vulkan.h>
#include "vk_render.h"
#include "vk_context.h"


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
	vk_swap_chain() {};
	~vk_swap_chain() {};

	void inti_swap_chain();
	void createSwapChain(const VkCommandBuffer& cmd);

private:
	VkResult createSwapChainExtensions();
	void getSupportedFormats();
	VkResult createSurface();
	uint32_t getGraphicsQueueWithPresentationSupport() { return 0; };

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
	vk_device* _device;
	vk_context* _context;
};

