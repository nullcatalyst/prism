#pragma once

#include <cstdint>
#include <string>

#include "webgpu-headers/webgpu.h"

namespace prism::graphics::common {

std::string   adapter_info_string(WGPUAdapter adapter);
WGPUAdapter   request_adapter(WGPUInstance instance, WGPUSurface surface);
WGPUDevice    create_device(WGPUAdapter adapter);
WGPUSwapChain create_swap_chain(WGPUDevice device, WGPUSurface surface, WGPUAdapter adapter,
                                const uint32_t width, const uint32_t height);
WGPUQueue     get_queue(WGPUDevice device);

WGPUBindGroupLayout create_bind_group_layout(WGPUDevice                           device,
                                             const WGPUBindGroupLayoutDescriptor& layout_desc);
WGPUBindGroup create_bind_group(WGPUDevice device, const WGPUBindGroupDescriptor& bind_group_desc);
WGPUShaderModule   create_shader_module(WGPUDevice device, const char* source);
WGPUPipelineLayout create_pipeline_layout(WGPUDevice                          device,
                                          const WGPUPipelineLayoutDescriptor& layout_desc);
WGPURenderPipeline create_render_pipeline(WGPUDevice                          device,
                                          const WGPURenderPipelineDescriptor& pipeline_desc);

WGPUBuffer create_buffer(WGPUDevice device, const WGPUBufferUsageFlags usage,
                         const uint64_t buffer_size, const void* data = nullptr,
                         const uint64_t data_size = 0, const uint64_t data_offset_into_buffer = 0);
void       update_buffer(WGPUDevice device, WGPUQueue queue, WGPUBuffer buffer, const void* data,
                         const uint64_t data_size, const uint64_t data_offset_into_buffer = 0);

WGPUTexture     create_texture_2d(WGPUDevice device, const WGPUTextureUsageFlags usage,
                                  const WGPUTextureFormat format, const uint32_t width,
                                  const uint32_t height);
void            update_texture_2d(WGPUDevice device, WGPUQueue queue, WGPUTexture texture,
                                  const uint32_t width, const uint32_t height, const void* data,
                                  const uint64_t data_size);
WGPUTextureView create_texture_view_2d(WGPUDevice device, WGPUTexture texture,
                                       const WGPUTextureFormat format);
WGPUSampler     create_sampler(WGPUDevice device, const WGPUAddressMode address_mode,
                               const WGPUFilterMode min_filter, const WGPUFilterMode mag_filter,
                               const WGPUFilterMode mipmap_filter);
WGPUSampler     create_sampler_comparison(WGPUDevice device, const WGPUAddressMode address_mode,
                                          const WGPUFilterMode      min_filter,
                                          const WGPUFilterMode      mag_filter,
                                          const WGPUFilterMode      mipmap_filter,
                                          const WGPUCompareFunction compare);

WGPUTextureView swap_chain_view(WGPUDevice device, WGPUSwapChain swap_chain);

WGPURenderBundleEncoder begin_render_bundle(
    WGPUDevice device, const WGPURenderBundleEncoderDescriptor& render_bundle_encoder_desc);
WGPURenderBundle end_render_bundle(WGPUDevice              device,
                                   WGPURenderBundleEncoder render_bundle_encoder);
void             set_pipeline(WGPUDevice device, WGPURenderBundleEncoder render_bundle_encoder,
                              WGPURenderPipeline pipeline);
void             set_bind_group(WGPUDevice device, WGPURenderBundleEncoder render_bundle_encoder,
                                const uint32_t slot, WGPUBindGroup bind_group);
void             set_buffer(WGPUDevice device, WGPURenderBundleEncoder render_bundle_encoder,
                            const uint32_t slot, WGPUBuffer buffer, const uint64_t offset, const uint64_t size);
void set_index_u16_buffer(WGPUDevice device, WGPURenderBundleEncoder render_bundle_encoder,
                          WGPUBuffer buffer, const uint64_t offset, const uint64_t size);
void set_index_u32_buffer(WGPUDevice device, WGPURenderBundleEncoder render_bundle_encoder,
                          WGPUBuffer buffer, const uint64_t offset, const uint64_t size);
void draw(WGPUDevice device, WGPURenderBundleEncoder render_bundle_encoder,
          const uint32_t vertex_count, const uint32_t instance_count,
          const uint32_t first_vertex = 0, const uint32_t first_instance = 0);
void draw_indexed(WGPUDevice device, WGPURenderBundleEncoder render_bundle_encoder,
                  const uint32_t index_count, const uint32_t instance_count,
                  const uint32_t first_index = 0, const int32_t base_vertex = 0,
                  const uint32_t first_instance = 0);
void draw_indirect(WGPUDevice device, WGPURenderBundleEncoder render_bundle_encoder,
                   WGPUBuffer indirect_buffer, const uint64_t indirect_offset = 0);
void draw_indexed_indirect(WGPUDevice device, WGPURenderBundleEncoder render_bundle_encoder,
                           WGPUBuffer indirect_buffer, const uint64_t indirect_offset = 0);

WGPURenderPassEncoder begin_render_pass(WGPUDevice device, WGPUCommandEncoder encoder,
                                        const WGPURenderPassDescriptor& render_pass_desc,
                                        const uint32_t width, const uint32_t height);
void                  end_render_pass(WGPUDevice device, WGPURenderPassEncoder render_pass);
void                  execute_render_bundle(WGPUDevice device, WGPURenderPassEncoder render_pass,
                                            WGPURenderBundle render_bundle);
void                  set_pipeline(WGPUDevice device, WGPURenderPassEncoder render_pass,
                                   WGPURenderPipeline pipeline);
void set_bind_group(WGPUDevice device, WGPURenderPassEncoder render_pass, const uint32_t slot,
                    WGPUBindGroup bind_group);
void set_buffer(WGPUDevice device, WGPURenderPassEncoder render_pass, const uint32_t slot,
                WGPUBuffer buffer, const uint64_t offset, const uint64_t size);
void set_index_u16_buffer(WGPUDevice device, WGPURenderPassEncoder render_pass, WGPUBuffer buffer,
                          const uint64_t offset, const uint64_t size);
void set_index_u32_buffer(WGPUDevice device, WGPURenderPassEncoder render_pass, WGPUBuffer buffer,
                          const uint64_t offset, const uint64_t size);
void draw(WGPUDevice device, WGPURenderPassEncoder render_pass, const uint32_t vertex_count,
          const uint32_t instance_count, const uint32_t first_vertex = 0,
          const uint32_t first_instance = 0);
void draw_indexed(WGPUDevice device, WGPURenderPassEncoder render_pass, const uint32_t index_count,
                  const uint32_t instance_count, const uint32_t first_index = 0,
                  const int32_t base_vertex = 0, const uint32_t first_instance = 0);
void draw_indirect(WGPUDevice device, WGPURenderPassEncoder render_pass, WGPUBuffer indirect_buffer,
                   const uint64_t indirect_offset = 0);
void draw_indexed_indirect(WGPUDevice device, WGPURenderPassEncoder render_pass,
                           WGPUBuffer indirect_buffer, const uint64_t indirect_offset = 0);

WGPUCommandEncoder start_frame(WGPUDevice device);
void present_frame(WGPUDevice device, WGPUSwapChain swap_chain, WGPUCommandEncoder encoder,
                   WGPUQueue queue);

}  // namespace prism::graphics::common
