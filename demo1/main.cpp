#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include "vulkan_app.h"
#include "vk_context.h"


int main()
{
	//vulkan_app app;
	//try
	//{
	//	app.run();
	//}
	//catch (const std::exception& e)
	//{
	//	std::cerr << e.what() << std::endl;
	//	return EXIT_FAILURE;
	//}
	vk_context context;
	for (int i = 0; i <  context._layer_props.size(); i++)
	{
		std::cout << context._layer_props[i].layerName << std::endl;
		for (int j = 0; j < context._instance_extensions[i].size(); j++)
		{
			std::cout << "---->" << context._instance_extensions[i][j].extensionName << std::endl;
		}
	}

	return 0;
}