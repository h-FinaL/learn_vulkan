#include "vk_render.h"

#include <stdio.h>


void vk_render::initialize()
{

}

void vk_render::create_presentation_window(int& height, int& weight)
{
	_height = height;
	_width = weight;
	WNDCLASSEX  winInfo;

	memcpy(_name, "Swapchain presentation window", 30);
	memset(&winInfo, 0, sizeof(WNDCLASSEX));
	// Initialize the window class structure:
	winInfo.cbSize = sizeof(WNDCLASSEX);
	winInfo.style = CS_HREDRAW | CS_VREDRAW;
	winInfo.lpfnWndProc = WndProc;
	winInfo.cbClsExtra = 0;
	winInfo.cbWndExtra = 0;
	winInfo.hInstance = _connection; // hInstance
	winInfo.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winInfo.hCursor = LoadCursor(NULL, IDC_ARROW);
	winInfo.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winInfo.lpszMenuName = NULL;
	winInfo.lpszClassName = (LPCWSTR)_name;
	winInfo.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	// Register window class:
	if (!RegisterClassEx(&winInfo)) {
		// It didn't work, so try to give a useful error:
		printf("Unexpected error trying to start the application!\n");
		fflush(stdout);
		exit(1);
	}

	RECT wr = { 0, 0, _width, _height };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
	_window = CreateWindowEx(0,
		(LPCWSTR)_name,					// class name
		(LPCWSTR)_name,					// app name
		WS_OVERLAPPEDWINDOW |	// window style
		WS_VISIBLE |
		WS_SYSMENU,
		100, 100,				// x/y coords
		wr.right - wr.left,     // width
		wr.bottom - wr.top,     // height
		NULL,					// handle to parent
		NULL,					// handle to menu
		_connection,				// hInstance
		NULL);					// no extra parameters

	if (!_window) {
		// It didn't work, so try to give a useful error:
		printf("Cannot create a window in which to draw!\n");
		fflush(stdout);
		exit(1);
	}

	SetWindowLongPtr(_window, GWLP_USERDATA, (LONG_PTR)_context);
}

LRESULT CALLBACK vk_render::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return (DefWindowProc(hWnd, uMsg, wParam, lParam));
}

void vk_render::create_command_pool()
{
	vk_device* device = &_context->_device;
	VkCommandPoolCreateInfo info{};
	info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	info.queueFamilyIndex = device->get_queue_index();

	vkCreateCommandPool(device->get_device(), &info, nullptr, &_cmd_pool);
}

void vk_render::build_swap_chain_and_depth_image()
{
	vk_device* device = &_context->_device;

}

bool vk_render::render()
{
	MSG msg;   // message
	PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	if (msg.message == WM_QUIT) {
		return false;
	}
	TranslateMessage(&msg);
	DispatchMessage(&msg);
	RedrawWindow(_window, NULL, NULL, RDW_INTERNALPAINT);
	return true;
}

void vk_render::buildSwapChainAndDepthImage()
{
	// Get the appropriate queue to submit the command into
	_context->_device.get_queue();

	// Create swapchain and get the color image
	swapChainObj->createSwapChain(cmdDepthImage);

	// Create the depth image
	createDepthImage();
}