#include "vk_shader.h"

#include <vector>

void vk_shader::build_shader_module_with_SPV(uint32_t* vertShaderText, size_t vertexSPVSize, uint32_t* fragShaderText, size_t fragmentSPVSize)
{
	VkResult  result;

	// Fill in the control structure to push the necessary
	// details of the shader.
	shaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shaderStages[0].pNext = NULL;
	shaderStages[0].pSpecializationInfo = NULL;
	shaderStages[0].flags = 0;
	shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
	shaderStages[0].pName = "main";

	VkShaderModuleCreateInfo moduleCreateInfo;
	moduleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	moduleCreateInfo.pNext = NULL;
	moduleCreateInfo.flags = 0;
	moduleCreateInfo.codeSize = vertexSPVSize;
	moduleCreateInfo.pCode = vertShaderText;
	result = vkCreateShaderModule(_device, &moduleCreateInfo, NULL, &shaderStages[0].module);
	//assert(result == VK_SUCCESS);

	std::vector<unsigned int> fragSPV;
	shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shaderStages[1].pNext = NULL;
	shaderStages[1].pSpecializationInfo = NULL;
	shaderStages[1].flags = 0;
	shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	shaderStages[1].pName = "main";

	moduleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	moduleCreateInfo.pNext = NULL;
	moduleCreateInfo.flags = 0;
	moduleCreateInfo.codeSize = fragmentSPVSize;
	moduleCreateInfo.pCode = fragShaderText;
	result = vkCreateShaderModule(_device, &moduleCreateInfo, NULL, &shaderStages[1].module);
	//assert(result == VK_SUCCESS);
}

void vk_shader::destroy_shaders()
{
	vkDestroyShaderModule(_device, shaderStages[0].module, NULL);
	vkDestroyShaderModule(_device, shaderStages[1].module, NULL);
}
