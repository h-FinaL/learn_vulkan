#pragma once
#include <cstdint>

#include <vulkan/vulkan_core.h>

class vk_shader
{
public:
	// Constructor
	vk_shader(VkDevice device) : _device(device){}

	// Destructor
	~vk_shader() {}

	// Use .spv and build shader module
	void build_shader_module_with_SPV(uint32_t* vertShaderText, size_t vertexSPVSize, uint32_t* fragShaderText, size_t fragmentSPVSize);

	// Kill the shader when not required
	void destroy_shaders();

private:
	VkPipelineShaderStageCreateInfo shaderStages[2];
	VkDevice _device{VK_NULL_HANDLE};
};

