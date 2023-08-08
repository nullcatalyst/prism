#pragma once

#include "webgpu-headers/webgpu.h"

// This header exists entirely to validate that the structs in the prism::gfx namespace match the
// structs in by the WGPU C headers. Duplicating the structs into C++ allows us to introduce sane
// defaults to properties of the struct, making it easier to use by not requiring the user to set
// every field every time.

#define ASSERT_STRUCT_SIZE_EQ($type) \
    static_assert(sizeof(::prism::gfx::$type) == sizeof(WGPU##$type))
#define ASSERT_STRUCT_MEMBER_EQ($type, $member)                                               \
    static_assert(offsetof(::prism::gfx::$type, $member) == offsetof(WGPU##$type, $member) && \
                  sizeof(std::declval<prism::gfx::$type>().$member) ==                        \
                      sizeof(std::declval<WGPU##$type>().$member))
#define ASSERT_RENAMED_STRUCT_MEMBER_EQ($type, $member, $wgpu_member)                              \
    static_assert(offsetof(::prism::gfx::$type, $member) == offsetof(WGPU##$type, $wgpu_member) && \
                  sizeof(std::declval<prism::gfx::$type>().$member) ==                             \
                      sizeof(std::declval<WGPU##$type>().$wgpu_member))

ASSERT_STRUCT_SIZE_EQ(ChainedStruct);
ASSERT_STRUCT_MEMBER_EQ(ChainedStruct, next);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(ChainedStruct, s_type, sType);

ASSERT_STRUCT_SIZE_EQ(BufferBindingLayout);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(BufferBindingLayout, next_in_chain, nextInChain);
ASSERT_STRUCT_MEMBER_EQ(BufferBindingLayout, type);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(BufferBindingLayout, has_dynamic_offset, hasDynamicOffset);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(BufferBindingLayout, min_binding_size, minBindingSize);

ASSERT_STRUCT_SIZE_EQ(SamplerBindingLayout);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(SamplerBindingLayout, next_in_chain, nextInChain);
ASSERT_STRUCT_MEMBER_EQ(SamplerBindingLayout, type);

ASSERT_STRUCT_SIZE_EQ(TextureBindingLayout);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(TextureBindingLayout, next_in_chain, nextInChain);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(TextureBindingLayout, sample_type, sampleType);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(TextureBindingLayout, view_dimension, viewDimension);
ASSERT_STRUCT_MEMBER_EQ(TextureBindingLayout, multisampled);

ASSERT_STRUCT_SIZE_EQ(StorageTextureBindingLayout);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(StorageTextureBindingLayout, next_in_chain, nextInChain);
ASSERT_STRUCT_MEMBER_EQ(StorageTextureBindingLayout, access);
ASSERT_STRUCT_MEMBER_EQ(StorageTextureBindingLayout, format);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(StorageTextureBindingLayout, view_dimension, viewDimension);

ASSERT_STRUCT_SIZE_EQ(BindGroupLayoutEntry);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(BindGroupLayoutEntry, next_in_chain, nextInChain);
ASSERT_STRUCT_MEMBER_EQ(BindGroupLayoutEntry, binding);
ASSERT_STRUCT_MEMBER_EQ(BindGroupLayoutEntry, visibility);
ASSERT_STRUCT_MEMBER_EQ(BindGroupLayoutEntry, buffer);
ASSERT_STRUCT_MEMBER_EQ(BindGroupLayoutEntry, sampler);
ASSERT_STRUCT_MEMBER_EQ(BindGroupLayoutEntry, texture);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(BindGroupLayoutEntry, storage_texture, storageTexture);

ASSERT_STRUCT_SIZE_EQ(BindGroupLayoutDescriptor);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(BindGroupLayoutDescriptor, next_in_chain, nextInChain);
ASSERT_STRUCT_MEMBER_EQ(BindGroupLayoutDescriptor, label);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(BindGroupLayoutDescriptor, entry_count, entryCount);
ASSERT_STRUCT_MEMBER_EQ(BindGroupLayoutDescriptor, entries);

ASSERT_STRUCT_SIZE_EQ(BindGroupEntry);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(BindGroupEntry, next_in_chain, nextInChain);
ASSERT_STRUCT_MEMBER_EQ(BindGroupEntry, binding);
ASSERT_STRUCT_MEMBER_EQ(BindGroupEntry, buffer);
ASSERT_STRUCT_MEMBER_EQ(BindGroupEntry, sampler);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(BindGroupEntry, texture_view, textureView);

ASSERT_STRUCT_SIZE_EQ(BindGroupDescriptor);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(BindGroupDescriptor, next_in_chain, nextInChain);
ASSERT_STRUCT_MEMBER_EQ(BindGroupDescriptor, label);
ASSERT_STRUCT_MEMBER_EQ(BindGroupDescriptor, layout);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(BindGroupDescriptor, entry_count, entryCount);
ASSERT_STRUCT_MEMBER_EQ(BindGroupDescriptor, entries);

ASSERT_STRUCT_SIZE_EQ(PipelineLayoutDescriptor);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(PipelineLayoutDescriptor, next_in_chain, nextInChain);
ASSERT_STRUCT_MEMBER_EQ(PipelineLayoutDescriptor, label);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(PipelineLayoutDescriptor, bind_group_layout_count,
                                bindGroupLayoutCount);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(PipelineLayoutDescriptor, bind_group_layouts, bindGroupLayouts);

ASSERT_STRUCT_SIZE_EQ(ConstantEntry);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(ConstantEntry, next_in_chain, nextInChain);
ASSERT_STRUCT_MEMBER_EQ(ConstantEntry, key);
ASSERT_STRUCT_MEMBER_EQ(ConstantEntry, value);

ASSERT_STRUCT_SIZE_EQ(ProgrammableStageDescriptor);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(ProgrammableStageDescriptor, next_in_chain, nextInChain);
ASSERT_STRUCT_MEMBER_EQ(ProgrammableStageDescriptor, module);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(ProgrammableStageDescriptor, entry_point, entryPoint);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(ProgrammableStageDescriptor, constant_count, constantCount);
ASSERT_STRUCT_MEMBER_EQ(ProgrammableStageDescriptor, constants);

ASSERT_STRUCT_SIZE_EQ(ComputePipelineDescriptor);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(ComputePipelineDescriptor, next_in_chain, nextInChain);
ASSERT_STRUCT_MEMBER_EQ(ComputePipelineDescriptor, label);
ASSERT_STRUCT_MEMBER_EQ(ComputePipelineDescriptor, layout);
ASSERT_STRUCT_MEMBER_EQ(ComputePipelineDescriptor, compute);

ASSERT_STRUCT_SIZE_EQ(ComputePassTimestampWrite);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(ComputePassTimestampWrite, query_set, querySet);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(ComputePassTimestampWrite, query_index, queryIndex);
ASSERT_STRUCT_MEMBER_EQ(ComputePassTimestampWrite, location);

ASSERT_STRUCT_SIZE_EQ(ComputePassDescriptor);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(ComputePassDescriptor, next_in_chain, nextInChain);
ASSERT_STRUCT_MEMBER_EQ(ComputePassDescriptor, label);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(ComputePassDescriptor, timestamp_write_count, timestampWriteCount);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(ComputePassDescriptor, timestamp_writes, timestampWrites);

ASSERT_STRUCT_SIZE_EQ(VertexAttribute);
ASSERT_STRUCT_MEMBER_EQ(VertexAttribute, format);
ASSERT_STRUCT_MEMBER_EQ(VertexAttribute, offset);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(VertexAttribute, shader_location, shaderLocation);

ASSERT_STRUCT_SIZE_EQ(VertexBufferLayout);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(VertexBufferLayout, array_stride, arrayStride);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(VertexBufferLayout, step_mode, stepMode);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(VertexBufferLayout, attribute_count, attributeCount);
ASSERT_STRUCT_MEMBER_EQ(VertexBufferLayout, attributes);

ASSERT_STRUCT_SIZE_EQ(VertexState);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(VertexState, next_in_chain, nextInChain);
ASSERT_STRUCT_MEMBER_EQ(VertexState, module);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(VertexState, entry_point, entryPoint);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(VertexState, constant_count, constantCount);
ASSERT_STRUCT_MEMBER_EQ(VertexState, constants);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(VertexState, buffer_count, bufferCount);
ASSERT_STRUCT_MEMBER_EQ(VertexState, buffers);

ASSERT_STRUCT_SIZE_EQ(PrimitiveState);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(PrimitiveState, next_in_chain, nextInChain);
ASSERT_STRUCT_MEMBER_EQ(PrimitiveState, topology);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(PrimitiveState, strip_index_format, stripIndexFormat);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(PrimitiveState, front_face, frontFace);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(PrimitiveState, cull_mode, cullMode);

ASSERT_STRUCT_SIZE_EQ(StencilFaceState);
ASSERT_STRUCT_MEMBER_EQ(StencilFaceState, compare);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(StencilFaceState, fail_op, failOp);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(StencilFaceState, depth_fail_op, depthFailOp);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(StencilFaceState, pass_op, passOp);

ASSERT_STRUCT_SIZE_EQ(DepthStencilState);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(DepthStencilState, next_in_chain, nextInChain);
ASSERT_STRUCT_MEMBER_EQ(DepthStencilState, format);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(DepthStencilState, depth_write_enabled, depthWriteEnabled);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(DepthStencilState, depth_compare, depthCompare);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(DepthStencilState, stencil_front, stencilFront);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(DepthStencilState, stencil_back, stencilBack);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(DepthStencilState, stencil_read_mask, stencilReadMask);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(DepthStencilState, stencil_write_mask, stencilWriteMask);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(DepthStencilState, depth_bias, depthBias);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(DepthStencilState, depth_bias_slope_scale, depthBiasSlopeScale);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(DepthStencilState, depth_bias_clamp, depthBiasClamp);

ASSERT_STRUCT_SIZE_EQ(MultisampleState);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(MultisampleState, next_in_chain, nextInChain);
ASSERT_STRUCT_MEMBER_EQ(MultisampleState, count);
ASSERT_STRUCT_MEMBER_EQ(MultisampleState, mask);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(MultisampleState, alpha_to_coverage_enabled,
                                alphaToCoverageEnabled);

ASSERT_STRUCT_SIZE_EQ(BlendComponent);
ASSERT_STRUCT_MEMBER_EQ(BlendComponent, operation);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(BlendComponent, src_factor, srcFactor);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(BlendComponent, dst_factor, dstFactor);

ASSERT_STRUCT_SIZE_EQ(BlendState);
ASSERT_STRUCT_MEMBER_EQ(BlendState, color);
ASSERT_STRUCT_MEMBER_EQ(BlendState, alpha);

ASSERT_STRUCT_SIZE_EQ(ColorTargetState);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(ColorTargetState, next_in_chain, nextInChain);
ASSERT_STRUCT_MEMBER_EQ(ColorTargetState, format);
ASSERT_STRUCT_MEMBER_EQ(ColorTargetState, blend);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(ColorTargetState, write_mask, writeMask);

ASSERT_STRUCT_SIZE_EQ(FragmentState);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(FragmentState, next_in_chain, nextInChain);
ASSERT_STRUCT_MEMBER_EQ(FragmentState, module);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(FragmentState, entry_point, entryPoint);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(FragmentState, constant_count, constantCount);
ASSERT_STRUCT_MEMBER_EQ(FragmentState, constants);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(FragmentState, target_count, targetCount);
ASSERT_STRUCT_MEMBER_EQ(FragmentState, targets);

ASSERT_STRUCT_SIZE_EQ(RenderPipelineDescriptor);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(RenderPipelineDescriptor, next_in_chain, nextInChain);
ASSERT_STRUCT_MEMBER_EQ(RenderPipelineDescriptor, label);
ASSERT_STRUCT_MEMBER_EQ(RenderPipelineDescriptor, layout);
ASSERT_STRUCT_MEMBER_EQ(RenderPipelineDescriptor, vertex);
ASSERT_STRUCT_MEMBER_EQ(RenderPipelineDescriptor, primitive);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(RenderPipelineDescriptor, depth_stencil, depthStencil);
ASSERT_STRUCT_MEMBER_EQ(RenderPipelineDescriptor, multisample);
ASSERT_STRUCT_MEMBER_EQ(RenderPipelineDescriptor, fragment);

ASSERT_STRUCT_SIZE_EQ(Color);
ASSERT_STRUCT_MEMBER_EQ(Color, r);
ASSERT_STRUCT_MEMBER_EQ(Color, g);
ASSERT_STRUCT_MEMBER_EQ(Color, b);
ASSERT_STRUCT_MEMBER_EQ(Color, a);

ASSERT_STRUCT_SIZE_EQ(RenderPassColorAttachment);
ASSERT_STRUCT_MEMBER_EQ(RenderPassColorAttachment, view);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(RenderPassColorAttachment, resolve_target, resolveTarget);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(RenderPassColorAttachment, load_op, loadOp);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(RenderPassColorAttachment, store_op, storeOp);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(RenderPassColorAttachment, clear_value, clearValue);

ASSERT_STRUCT_SIZE_EQ(RenderPassDepthStencilAttachment);
ASSERT_STRUCT_MEMBER_EQ(RenderPassDepthStencilAttachment, view);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(RenderPassDepthStencilAttachment, depth_load_op, depthLoadOp);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(RenderPassDepthStencilAttachment, depth_store_op, depthStoreOp);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(RenderPassDepthStencilAttachment, depth_clear_value,
                                depthClearValue);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(RenderPassDepthStencilAttachment, depth_read_only, depthReadOnly);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(RenderPassDepthStencilAttachment, stencil_load_op, stencilLoadOp);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(RenderPassDepthStencilAttachment, stencil_store_op, stencilStoreOp);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(RenderPassDepthStencilAttachment, stencil_clear_value,
                                stencilClearValue);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(RenderPassDepthStencilAttachment, stencil_read_only,
                                stencilReadOnly);

ASSERT_STRUCT_SIZE_EQ(RenderPassTimestampWrite);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(RenderPassTimestampWrite, query_set, querySet);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(RenderPassTimestampWrite, query_index, queryIndex);
ASSERT_STRUCT_MEMBER_EQ(RenderPassTimestampWrite, location);

ASSERT_STRUCT_SIZE_EQ(RenderPassDescriptor);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(RenderPassDescriptor, next_in_chain, nextInChain);
ASSERT_STRUCT_MEMBER_EQ(RenderPassDescriptor, label);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(RenderPassDescriptor, color_attachment_count, colorAttachmentCount);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(RenderPassDescriptor, color_attachments, colorAttachments);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(RenderPassDescriptor, depth_stencil_attachment,
                                depthStencilAttachment);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(RenderPassDescriptor, occlusion_query_set, occlusionQuerySet);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(RenderPassDescriptor, timestamp_write_count, timestampWriteCount);
ASSERT_RENAMED_STRUCT_MEMBER_EQ(RenderPassDescriptor, timestamp_writes, timestampWrites);
