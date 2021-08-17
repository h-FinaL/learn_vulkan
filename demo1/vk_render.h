#pragma once

#include <Windows.h>
#include <vulkan/vulkan.h>
#include "vk_core.h"
#include "vk_buffer.h"
#include "vk_swap_chain.h"

#define NUM_SAMPLES VK_SAMPLE_COUNT_1_BIT

class vk_render
{
public:
	vk_render(vk_core* core);

	void initialize();

	bool render();

	void create_presentation_window(int& height, int& weight);
	void set_image_layout(VkImage image, 
		VkImageAspectFlags aspectMask, 
		VkImageLayout oldImageLayout, 
		VkImageLayout newImageLayout, 
		VkAccessFlagBits srcAccessMask,
		const VkCommandBuffer& cmdBuf);

	//! Windows procedure method for handling events.
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void create_command_pool();
	void build_swap_chain_and_depth_image();
	void buildSwapChainAndDepthImage();
	void createDepthImage();

	int get_width() { return _width; }
	int get_height() { return _height; }
	HINSTANCE get_hinstance() { return _connection; }
	HWND get_hwnd() { return _window; }


private:
	HINSTANCE _connection;

	char _name[80];
	HWND _window;

	struct
	{
		VkFormat _format;
		VkImage _image;
		VkDeviceMemory _mem;
		VkImageView _view;
	}Depth;

	VkCommandBuffer _cmd_depth_image;
	VkCommandPool _cmd_pool;
	int _width{ 0 };
	int _height{ 0 };

	vk_core* _core{ nullptr }; 
	vk_swap_chain _swap_chain;
	vk_buffer _buffer;
};

