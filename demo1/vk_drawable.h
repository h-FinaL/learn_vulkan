#pragma once

#include <vulkan/vulkan.h>

#include "vk_core.h"
#include "vk_render.h"
#include "vk_buffer.h"

class vk_drawable
{
public:
	vk_drawable(vk_render* render) : _core(render->_core), _buffer(_core), _render(render) {}
	void create_vertex_buffer(const void* vertex_data, 
		uint32_t data_size, 
		uint32_t data_stride, 
		bool use_texture);

	//����Ⱦ֮ǰ����׼���ɻ��ƵĶ���
	//���䡢������¼����Ⱦָ��
	void prepare();
	//��Ⱦ�ɻ��ƶ���
	void render();

	void record_command_buffer(int current_image, VkCommandBuffer* cmd_draw);

	struct {
		VkBuffer buffer;
		VkDeviceMemory memory;
		VkDescriptorBufferInfo buffer_info;
	} vertex_buffer;

	VkVertexInputBindingDescription viIpBind;
	VkVertexInputAttributeDescription viIpAttrb[2];

	std::vector<VkCommandBuffer> _cmd_draws;
	vk_render* _render;

	vk_core* _core;
	vk_buffer _buffer;
};

