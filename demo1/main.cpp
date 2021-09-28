#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include "vk_core.h"
#include "vk_render.h"
#include "vk_swap_chain.h"
#include "vk_drawable.h"

int main()
{
	vk_context ctx;
	vk_core core(ctx);
	vk_render render(&core);
	vk_drawable draw(&render);
	draw.prepare();
	while (1)
	{
		render.render();
	}

	return 0;
}