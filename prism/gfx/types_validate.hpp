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
