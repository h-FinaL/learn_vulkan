#pragma once

#include "vk_drawable.h"
#include "vk_shader.h"
#include <vulkan/vulkan_core.h>

class vk_pipeline
{
public:
	//������ˮ�߻�����󣬱�����ˮ�߶���
	void create_pipeline_cache();

	// ���ش�������ˮ�߶�������Ҫ����һ���ɻ��ƶ���
	// ��ȡ���������������Ϣ
	// ����֮�⻹����ɫ���ļ����Լ�һ�����������������Ƿ�֧�����
	// �Լ�����Ķ��������Ƿ���Ч
	bool create_pipeline(vk_drawable* draw, 
		VkPipeline* pipeline, 
		vk_shader* shader, 
		VkBool32 include_depth,
		VkBool32 include_vi = true);

	void destroy_pipeline_cache();
};

