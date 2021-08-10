#pragma once

#include <Windows.h>
#include <vulkan/vulkan.h>
#include "vk_context.h"

class vk_swap_chain;
class vk_render
{
public:
	vk_render(vk_context* context) : _context(context) {}

	void initialize();

	bool render();

	void create_presentation_window(int& height, int& weight);

	//! Windows procedure method for handling events.
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void create_command_pool();
	void build_swap_chain_and_depth_image();
	void buildSwapChainAndDepthImage();

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

	vk_context* _context{ nullptr };
};

