#pragma once

#include "webgpu-headers/webgpu.h"

// static_assert(sizeof(prism::gfx::common::ChainedStruct) == sizeof(WGPUChainedStruct));
// static_assert(offsetof(prism::gfx::common::ChainedStruct, next) ==
//               offsetof(WGPUChainedStruct, next));
// static_assert(offsetof(prism::gfx::common::ChainedStruct, sType) ==
//               offsetof(WGPUChainedStruct, sType));

// static_assert(sizeof(prism::gfx::common::Chainable) == sizeof(WGPUChainable));
// static_assert(offsetof(prism::gfx::common::Chainable, next_in_chain) ==
//               offsetof(WGPUChainable, nextInChain));

// static_assert(sizeof(prism::gfx::common::Labelable) == sizeof(WGPULabelable));
// static_assert(offsetof(prism::gfx::common::Labelable, label) ==
//               offsetof(WGPULabelable, label));

// static_assert(sizeof(prism::gfx::common::BufferBindingLayout) ==
//               sizeof(WGPUBufferBindingLayout));
// static_assert(offsetof(prism::gfx::common::BufferBindingLayout, next_in_chain) ==
//               offsetof(WGPUBufferBindingLayout, nextInChain));
// static_assert(offsetof(prism::gfx::common::BufferBindingLayout, type) ==
//               offsetof(WGPUBufferBindingLayout, type));
// static_assert(offsetof(prism::gfx::common::BufferBindingLayout, has_dynamic_offset) ==
//               offsetof(WGPUBufferBindingLayout, hasDynamicOffset));
// static_assert(offsetof(prism::gfx::common::BufferBindingLayout, min_binding_size) ==
//               offsetof(WGPUBufferBindingLayout, minBindingSize));

// static_assert(sizeof(prism::gfx::common::SamplerBindingLayout) ==
//               sizeof(WGPUSamplerBindingLayout));
// static_assert(offsetof(prism::gfx::common::SamplerBindingLayout, next_in_chain) ==
//               offsetof(WGPUSamplerBindingLayout, nextInChain));
// static_assert(offsetof(prism::gfx::common::SamplerBindingLayout, type) ==
//               offsetof(WGPUSamplerBindingLayout, type));

// static_assert(sizeof(prism::gfx::common::TextureBindingLayout) ==
//               sizeof(WGPUTextureBindingLayout));
// static_assert(offsetof(prism::gfx::common::TextureBindingLayout, next_in_chain) ==
//               offsetof(WGPUTextureBindingLayout, nextInChain));
// static_assert(offsetof(prism::gfx::common::TextureBindingLayout, sample_type) ==
//               offsetof(WGPUTextureBindingLayout, sampleType));
// static_assert(offsetof(prism::gfx::common::TextureBindingLayout, view_dimension) ==
//               offsetof(WGPUTextureBindingLayout, viewDimension));
// static_assert(offsetof(prism::gfx::common::TextureBindingLayout, multisampled) ==
//               offsetof(WGPUTextureBindingLayout, multisampled));

// static_assert(sizeof(prism::gfx::common::StorageTextureBindingLayout) ==
//               sizeof(WGPUStorageTextureBindingLayout));
// static_assert(offsetof(prism::gfx::common::StorageTextureBindingLayout, next_in_chain) ==
//               offsetof(WGPUStorageTextureBindingLayout, nextInChain));
// static_assert(offsetof(prism::gfx::common::StorageTextureBindingLayout, access) ==
//               offsetof(WGPUStorageTextureBindingLayout, access));
// static_assert(offsetof(prism::gfx::common::StorageTextureBindingLayout, format) ==
//               offsetof(WGPUStorageTextureBindingLayout, format));
// static_assert(offsetof(prism::gfx::common::StorageTextureBindingLayout, view_dimension) ==
//               offsetof(WGPUStorageTextureBindingLayout, viewDimension));

// static_assert(sizeof(prism::gfx::common::BindGroupLayoutEntry) ==
//               sizeof(WGPUBindGroupLayoutEntry));
// static_assert(offsetof(prism::gfx::common::BindGroupLayoutEntry, next_in_chain) ==
//               offsetof(WGPUBindGroupLayoutEntry, nextInChain));
// static_assert(offsetof(prism::gfx::common::BindGroupLayoutEntry, binding) ==
//               offsetof(WGPUBindGroupLayoutEntry, binding));
// static_assert(offsetof(prism::gfx::common::BindGroupLayoutEntry, visibility) ==
//               offsetof(WGPUBindGroupLayoutEntry, visibility));
// static_assert(offsetof(prism::gfx::common::BindGroupLayoutEntry, buffer) ==
//               offsetof(WGPUBindGroupLayoutEntry, buffer));
// static_assert(offsetof(prism::gfx::common::BindGroupLayoutEntry, sampler) ==
//               offsetof(WGPUBindGroupLayoutEntry, sampler));
// static_assert(offsetof(prism::gfx::common::BindGroupLayoutEntry, texture) ==
//               offsetof(WGPUBindGroupLayoutEntry, texture));
// static_assert(offsetof(prism::gfx::common::BindGroupLayoutEntry, storage_texture) ==
//               offsetof(WGPUBindGroupLayoutEntry, storageTexture));

// static_assert(sizeof(prism::gfx::common::BindGroupLayoutDescriptor) ==
//               sizeof(WGPUBindGroupLayoutDescriptor));
// static_assert(offsetof(prism::gfx::common::BindGroupLayoutDescriptor, next_in_chain) ==
//               offsetof(WGPUBindGroupLayoutDescriptor, nextInChain));
// static_assert(offsetof(prism::gfx::common::BindGroupLayoutDescriptor, label) ==
//               offsetof(WGPUBindGroupLayoutDescriptor, label));
// static_assert(offsetof(prism::gfx::common::BindGroupLayoutDescriptor, entry_count) ==
//               offsetof(WGPUBindGroupLayoutDescriptor, entryCount));
// static_assert(offsetof(prism::gfx::common::BindGroupLayoutDescriptor, entries) ==
//               offsetof(WGPUBindGroupLayoutDescriptor, entries));

// static_assert(sizeof(prism::gfx::common::BindGroupEntry) == sizeof(WGPUBindGroupEntry));
// static_assert(offsetof(prism::gfx::common::BindGroupEntry, next_in_chain) ==
//               offsetof(WGPUBindGroupEntry, nextInChain));
// static_assert(offsetof(prism::gfx::common::BindGroupEntry, binding) ==
//               offsetof(WGPUBindGroupEntry, binding));
// static_assert(offsetof(prism::gfx::common::BindGroupEntry, buffer) ==
//               offsetof(WGPUBindGroupEntry, buffer));
// static_assert(offsetof(prism::gfx::common::BindGroupEntry, sampler) ==
//               offsetof(WGPUBindGroupEntry, sampler));
// static_assert(offsetof(prism::gfx::common::BindGroupEntry, texture_view) ==
//               offsetof(WGPUBindGroupEntry, textureView));

// static_assert(sizeof(prism::gfx::common::BindGroupDescriptor) ==
//               sizeof(WGPUBindGroupDescriptor));
// static_assert(offsetof(prism::gfx::common::BindGroupDescriptor, next_in_chain) ==
//               offsetof(WGPUBindGroupDescriptor, nextInChain));
// static_assert(offsetof(prism::gfx::common::BindGroupDescriptor, label) ==
//               offsetof(WGPUBindGroupDescriptor, label));
// static_assert(offsetof(prism::gfx::common::BindGroupDescriptor, layout) ==
//               offsetof(WGPUBindGroupDescriptor, layout));
// static_assert(offsetof(prism::gfx::common::BindGroupDescriptor, entry_count) ==
//               offsetof(WGPUBindGroupDescriptor, entryCount));
// static_assert(offsetof(prism::gfx::common::BindGroupDescriptor, entries) ==
//               offsetof(WGPUBindGroupDescriptor, entries));

// static_assert(sizeof(prism::gfx::common::PipelineLayoutDescriptor) ==
//               sizeof(WGPUPipelineLayoutDescriptor));
// static_assert(offsetof(prism::gfx::common::PipelineLayoutDescriptor, next_in_chain) ==
//               offsetof(WGPUPipelineLayoutDescriptor, nextInChain));
// static_assert(offsetof(prism::gfx::common::PipelineLayoutDescriptor, label) ==
//               offsetof(WGPUPipelineLayoutDescriptor, label));
// static_assert(offsetof(prism::gfx::common::PipelineLayoutDescriptor,
//                        bind_group_layout_count) ==
//               offsetof(WGPUPipelineLayoutDescriptor, bindGroupLayoutCount));
// static_assert(offsetof(prism::gfx::common::PipelineLayoutDescriptor, bind_group_layouts) ==
//               offsetof(WGPUPipelineLayoutDescriptor, bindGroupLayouts));
