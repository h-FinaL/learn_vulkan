#pragma once

#include "vk_drawable.h"
#include "vk_shader.h"
#include <vulkan/vulkan_core.h>

class vk_pipeline
{
public:
	//创建流水线缓存对象，保存流水线对象
	void create_pipeline_cache();

	// 返回创建的流水线对象，它需要输入一个可绘制对象
	// 获取顶点输入的属性信息
	// 除此之外还有着色器文件，以及一个布尔变量负责检查是否支持深度
	// 以及输入的顶点数据是否有效
	bool create_pipeline(vk_drawable* draw, 
		VkPipeline* pipeline, 
		vk_shader* shader, 
		VkBool32 include_depth,
		VkBool32 include_vi = true);

	void destroy_pipeline_cache();
};

