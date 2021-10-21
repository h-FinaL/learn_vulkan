#include "vk_pipeline.h"

#include <vulkan/vulkan.h>

void vk_pipeline::create_pipeline_cache()
{
}

bool vk_pipeline::create_pipeline(vk_drawable* draw,
    VkPipeline* pipeline, 
    vk_shader* shader, 
    VkBool32 include_depth,
    VkBool32 include_vi)
{
    const int VK_DYNAMIC_STATE_RANGE_SIZE = 2;
    VkDynamicState dynamic_state_enables[VK_DYNAMIC_STATE_RANGE_SIZE];
    memset(dynamic_state_enables, 0, sizeof(dynamic_state_enables));

    //动态状态信息
    VkPipelineDynamicStateCreateInfo info;
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    info.pNext = nullptr;
    info.pDynamicStates = dynamic_state_enables;
    info.dynamicStateCount = 0;
    dynamic_state_enables[info.dynamicStateCount++] = VK_DYNAMIC_STATE_VIEWPORT;
    dynamic_state_enables[info.dynamicStateCount++] = VK_DYNAMIC_STATE_SCISSOR;

    //顶点输入状态
    VkPipelineVertexInputStateCreateInfo vertex_info;
    vertex_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertex_info.pNext = nullptr;
    vertex_info.flags = 0;
    vertex_info.vertexBindingDescriptionCount = 1;
    vertex_info.pVertexBindingDescriptions = &draw->viIpBind;
    vertex_info.vertexAttributeDescriptionCount = 2;
    vertex_info.pVertexAttributeDescriptions = draw->viIpAttrb;

    //输入装配状态
    VkPipelineInputAssemblyStateCreateInfo input_info;
    input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    input_info.pNext = nullptr;
    input_info.flags = 0;
    input_info.primitiveRestartEnable = VK_FALSE;
    input_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

    //光栅化状态
    VkPipelineRasterizationStateCreateInfo resterization_info;
    resterization_info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    resterization_info.pNext = nullptr;
    resterization_info.flags = 0;
    resterization_info.polygonMode = VK_POLYGON_MODE_FILL;
    resterization_info.cullMode = VK_CULL_MODE_BACK_BIT;
    resterization_info.frontFace = VK_FRONT_FACE_CLOCKWISE;
    resterization_info.depthClampEnable = include_depth;
    resterization_info.rasterizerDiscardEnable = VK_FALSE;
    resterization_info.depthBiasEnable = VK_FALSE;
    resterization_info.depthBiasConstantFactor = 0;
    resterization_info.depthBiasClamp = 0;
    resterization_info.depthBiasSlopeFactor = 0;
    resterization_info.lineWidth = 1.0f;

    //颜色融混状态
    VkPipelineColorBlendAttachmentState color_info[1]{};
    color_info[0].colorWriteMask = 0xf;
    color_info[0].blendEnable = VK_FALSE;
    //定义颜色和alpha融混操作符
    color_info[0].alphaBlendOp = VK_BLEND_OP_ADD;
    color_info[0].colorBlendOp = VK_BLEND_OP_ADD;
    //设置源和目标颜色/alpha融混参数
    color_info[0].srcColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    color_info[0].dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    color_info[0].srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    color_info[0].dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;

    VkPipelineColorBlendStateCreateInfo blend_info;
    blend_info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    blend_info.flags = 0;
    blend_info.pNext = nullptr;
    blend_info.attachmentCount = 1;
    blend_info.pAttachments = color_info;
    blend_info.logicOpEnable = VK_FALSE;
    blend_info.blendConstants[0] = 1.0f;
    blend_info.blendConstants[1] = 1.0f;
    blend_info.blendConstants[2] = 1.0f;
    blend_info.blendConstants[3] = 1.0f;


    //视口状态
    VkPipelineViewportStateCreateInfo view_info{};
    view_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    view_info.pNext = nullptr;
    view_info.flags = 0;
    view_info.viewportCount = 1;
    view_info.scissorCount = 1;
    view_info.pScissors = nullptr;
    view_info.pViewports = nullptr;

    //深度状态和模板状态
    VkPipelineDepthStencilStateCreateInfo ds_info;
    ds_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    ds_info.pNext = nullptr;
    ds_info.flags = 0;
    ds_info.depthTestEnable = include_depth;
    ds_info.depthWriteEnable = include_depth;
    ds_info.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
    ds_info.depthBoundsTestEnable = VK_FALSE;
    ds_info.stencilTestEnable = VK_FALSE;
    ds_info.back.failOp = VK_STENCIL_OP_KEEP;
    ds_info.back.passOp = VK_STENCIL_OP_KEEP;
    ds_info.back.compareOp = VK_COMPARE_OP_ALWAYS;
    ds_info.back.compareMask = 0;
    ds_info.back.reference = 0;
    ds_info.back.depthFailOp = VK_STENCIL_OP_KEEP;
    ds_info.back.writeMask = 0;
    ds_info.minDepthBounds = 0;
    ds_info.maxDepthBounds = 0;
    ds_info.stencilTestEnable = VK_FALSE;
    ds_info.front = ds_info.back;

    //多重采样状态
    VkPipelineMultisampleStateCreateInfo mul_info;
    mul_info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    mul_info.pNext = nullptr;
    mul_info.flags = 0;
    mul_info.rasterizationSamples = NUM_SAMPLES;

    return false;
}

void vk_pipeline::destroy_pipeline_cache()
{
}