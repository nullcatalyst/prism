#pragma once

#include "webgpu-headers/webgpu.h"

// static_assert(sizeof(prism::graphics::common::ChainedStruct) == sizeof(WGPUChainedStruct));
// static_assert(offsetof(prism::graphics::common::ChainedStruct, next) ==
//               offsetof(WGPUChainedStruct, next));
// static_assert(offsetof(prism::graphics::common::ChainedStruct, sType) ==
//               offsetof(WGPUChainedStruct, sType));

// static_assert(sizeof(prism::graphics::common::Chainable) == sizeof(WGPUChainable));
// static_assert(offsetof(prism::graphics::common::Chainable, next_in_chain) ==
//               offsetof(WGPUChainable, nextInChain));

// static_assert(sizeof(prism::graphics::common::Labelable) == sizeof(WGPULabelable));
// static_assert(offsetof(prism::graphics::common::Labelable, label) ==
//               offsetof(WGPULabelable, label));

// static_assert(sizeof(prism::graphics::common::BufferBindingLayout) ==
//               sizeof(WGPUBufferBindingLayout));
// static_assert(offsetof(prism::graphics::common::BufferBindingLayout, next_in_chain) ==
//               offsetof(WGPUBufferBindingLayout, nextInChain));
// static_assert(offsetof(prism::graphics::common::BufferBindingLayout, type) ==
//               offsetof(WGPUBufferBindingLayout, type));
// static_assert(offsetof(prism::graphics::common::BufferBindingLayout, has_dynamic_offset) ==
//               offsetof(WGPUBufferBindingLayout, hasDynamicOffset));
// static_assert(offsetof(prism::graphics::common::BufferBindingLayout, min_binding_size) ==
//               offsetof(WGPUBufferBindingLayout, minBindingSize));

// static_assert(sizeof(prism::graphics::common::SamplerBindingLayout) ==
//               sizeof(WGPUSamplerBindingLayout));
// static_assert(offsetof(prism::graphics::common::SamplerBindingLayout, next_in_chain) ==
//               offsetof(WGPUSamplerBindingLayout, nextInChain));
// static_assert(offsetof(prism::graphics::common::SamplerBindingLayout, type) ==
//               offsetof(WGPUSamplerBindingLayout, type));

// static_assert(sizeof(prism::graphics::common::TextureBindingLayout) ==
//               sizeof(WGPUTextureBindingLayout));
// static_assert(offsetof(prism::graphics::common::TextureBindingLayout, next_in_chain) ==
//               offsetof(WGPUTextureBindingLayout, nextInChain));
// static_assert(offsetof(prism::graphics::common::TextureBindingLayout, sample_type) ==
//               offsetof(WGPUTextureBindingLayout, sampleType));
// static_assert(offsetof(prism::graphics::common::TextureBindingLayout, view_dimension) ==
//               offsetof(WGPUTextureBindingLayout, viewDimension));
// static_assert(offsetof(prism::graphics::common::TextureBindingLayout, multisampled) ==
//               offsetof(WGPUTextureBindingLayout, multisampled));

// static_assert(sizeof(prism::graphics::common::StorageTextureBindingLayout) ==
//               sizeof(WGPUStorageTextureBindingLayout));
// static_assert(offsetof(prism::graphics::common::StorageTextureBindingLayout, next_in_chain) ==
//               offsetof(WGPUStorageTextureBindingLayout, nextInChain));
// static_assert(offsetof(prism::graphics::common::StorageTextureBindingLayout, access) ==
//               offsetof(WGPUStorageTextureBindingLayout, access));
// static_assert(offsetof(prism::graphics::common::StorageTextureBindingLayout, format) ==
//               offsetof(WGPUStorageTextureBindingLayout, format));
// static_assert(offsetof(prism::graphics::common::StorageTextureBindingLayout, view_dimension) ==
//               offsetof(WGPUStorageTextureBindingLayout, viewDimension));

// static_assert(sizeof(prism::graphics::common::BindGroupLayoutEntry) ==
//               sizeof(WGPUBindGroupLayoutEntry));
// static_assert(offsetof(prism::graphics::common::BindGroupLayoutEntry, next_in_chain) ==
//               offsetof(WGPUBindGroupLayoutEntry, nextInChain));
// static_assert(offsetof(prism::graphics::common::BindGroupLayoutEntry, binding) ==
//               offsetof(WGPUBindGroupLayoutEntry, binding));
// static_assert(offsetof(prism::graphics::common::BindGroupLayoutEntry, visibility) ==
//               offsetof(WGPUBindGroupLayoutEntry, visibility));
// static_assert(offsetof(prism::graphics::common::BindGroupLayoutEntry, buffer) ==
//               offsetof(WGPUBindGroupLayoutEntry, buffer));
// static_assert(offsetof(prism::graphics::common::BindGroupLayoutEntry, sampler) ==
//               offsetof(WGPUBindGroupLayoutEntry, sampler));
// static_assert(offsetof(prism::graphics::common::BindGroupLayoutEntry, texture) ==
//               offsetof(WGPUBindGroupLayoutEntry, texture));
// static_assert(offsetof(prism::graphics::common::BindGroupLayoutEntry, storage_texture) ==
//               offsetof(WGPUBindGroupLayoutEntry, storageTexture));

// static_assert(sizeof(prism::graphics::common::BindGroupLayoutDescriptor) ==
//               sizeof(WGPUBindGroupLayoutDescriptor));
// static_assert(offsetof(prism::graphics::common::BindGroupLayoutDescriptor, next_in_chain) ==
//               offsetof(WGPUBindGroupLayoutDescriptor, nextInChain));
// static_assert(offsetof(prism::graphics::common::BindGroupLayoutDescriptor, label) ==
//               offsetof(WGPUBindGroupLayoutDescriptor, label));
// static_assert(offsetof(prism::graphics::common::BindGroupLayoutDescriptor, entry_count) ==
//               offsetof(WGPUBindGroupLayoutDescriptor, entryCount));
// static_assert(offsetof(prism::graphics::common::BindGroupLayoutDescriptor, entries) ==
//               offsetof(WGPUBindGroupLayoutDescriptor, entries));

// static_assert(sizeof(prism::graphics::common::BindGroupEntry) == sizeof(WGPUBindGroupEntry));
// static_assert(offsetof(prism::graphics::common::BindGroupEntry, next_in_chain) ==
//               offsetof(WGPUBindGroupEntry, nextInChain));
// static_assert(offsetof(prism::graphics::common::BindGroupEntry, binding) ==
//               offsetof(WGPUBindGroupEntry, binding));
// static_assert(offsetof(prism::graphics::common::BindGroupEntry, buffer) ==
//               offsetof(WGPUBindGroupEntry, buffer));
// static_assert(offsetof(prism::graphics::common::BindGroupEntry, sampler) ==
//               offsetof(WGPUBindGroupEntry, sampler));
// static_assert(offsetof(prism::graphics::common::BindGroupEntry, texture_view) ==
//               offsetof(WGPUBindGroupEntry, textureView));

// static_assert(sizeof(prism::graphics::common::BindGroupDescriptor) ==
//               sizeof(WGPUBindGroupDescriptor));
// static_assert(offsetof(prism::graphics::common::BindGroupDescriptor, next_in_chain) ==
//               offsetof(WGPUBindGroupDescriptor, nextInChain));
// static_assert(offsetof(prism::graphics::common::BindGroupDescriptor, label) ==
//               offsetof(WGPUBindGroupDescriptor, label));
// static_assert(offsetof(prism::graphics::common::BindGroupDescriptor, layout) ==
//               offsetof(WGPUBindGroupDescriptor, layout));
// static_assert(offsetof(prism::graphics::common::BindGroupDescriptor, entry_count) ==
//               offsetof(WGPUBindGroupDescriptor, entryCount));
// static_assert(offsetof(prism::graphics::common::BindGroupDescriptor, entries) ==
//               offsetof(WGPUBindGroupDescriptor, entries));

// static_assert(sizeof(prism::graphics::common::PipelineLayoutDescriptor) ==
//               sizeof(WGPUPipelineLayoutDescriptor));
// static_assert(offsetof(prism::graphics::common::PipelineLayoutDescriptor, next_in_chain) ==
//               offsetof(WGPUPipelineLayoutDescriptor, nextInChain));
// static_assert(offsetof(prism::graphics::common::PipelineLayoutDescriptor, label) ==
//               offsetof(WGPUPipelineLayoutDescriptor, label));
// static_assert(offsetof(prism::graphics::common::PipelineLayoutDescriptor,
//                        bind_group_layout_count) ==
//               offsetof(WGPUPipelineLayoutDescriptor, bindGroupLayoutCount));
// static_assert(offsetof(prism::graphics::common::PipelineLayoutDescriptor, bind_group_layouts) ==
//               offsetof(WGPUPipelineLayoutDescriptor, bindGroupLayouts));
