#pragma once

#include <cstdint>

#include "prism/wasm/import.hpp"

namespace prism::js {

namespace detail {

WASM_IMPORT("gpu", "getPixelRatio") float gpu_get_pixel_ratio();
WASM_IMPORT("gpu", "getSurfaceFormat") uint32_t gpu_get_surface_format(uint32_t ctx_obj);

WASM_IMPORT("gpu", "createContext")
uint32_t gpu_create_context(uint32_t canvas);

WASM_IMPORT("gpu", "resizeContext")
uint32_t gpu_resize_context(uint32_t canvas, uint32_t width, uint32_t height);

WASM_IMPORT("gpu", "createBindGroupLayout")
uint32_t gpu_create_bind_group_layout(uint32_t ctx_obj, uint32_t bind_group_layout_desc_obj);
WASM_IMPORT("gpu", "createBindGroup")
uint32_t gpu_create_bind_group(uint32_t ctx_obj, uint32_t bind_group_desc_obj);
WASM_IMPORT("gpu", "createShaderModule")
uint32_t gpu_create_shader_module(uint32_t ctx_obj, const char* source);
WASM_IMPORT("gpu", "createPipelineLayout")
uint32_t gpu_create_pipeline_layout(uint32_t ctx_obj, uint32_t pipeline_layout_obj);
WASM_IMPORT("gpu", "createRenderPipeline")
uint32_t gpu_create_render_pipeline(uint32_t ctx_obj, uint32_t render_pipeline_desc_obj);
WASM_IMPORT("gpu", "createBuffer")
uint32_t gpu_create_buffer(uint32_t ctx_obj, uint32_t usage, size_t buffer_size, const void* data,
                           size_t data_size, size_t data_offset_into_buffer);
WASM_IMPORT("gpu", "updateBuffer")
uint32_t gpu_update_buffer(uint32_t ctx_obj, uint32_t buffer_obj, const void* data,
                           size_t data_size, size_t data_offset_into_buffer);
WASM_IMPORT("gpu", "createTexture2d")
uint32_t gpu_create_texture_2d(uint32_t ctx_obj, uint32_t usage, const char* format, uint32_t width,
                               uint32_t height);
WASM_IMPORT("gpu", "updateTexture2d")
uint32_t gpu_update_texture_2d(uint32_t ctx_obj, uint32_t texture_obj, uint32_t width,
                               uint32_t height, const void* ptr, size_t size);
WASM_IMPORT("gpu", "createTextureView2d")
uint32_t gpu_create_texture_view_2d(uint32_t ctx_obj, uint32_t usage, const char* format);
WASM_IMPORT("gpu", "createSampler")
uint32_t gpu_create_sampler(uint32_t ctx_obj, const char* address_mode, const char* min_filter,
                            const char* mag_filter, const char* mipmap_filter);
WASM_IMPORT("gpu", "createSamplerComparison")
uint32_t gpu_create_sampler_comparison(uint32_t ctx_obj, const char* compare_function,
                                       const char* address_mode, const char* min_filter,
                                       const char* mag_filter, const char* mipmap_filter);

WASM_IMPORT("gpu", "getSwapChainView")
uint32_t gpu_get_swap_chain_view(uint32_t ctx_obj);
WASM_IMPORT("gpu", "startFrame")
void gpu_start_frame(uint32_t ctx_obj);
WASM_IMPORT("gpu", "presentFrame")
void gpu_present_frame(uint32_t ctx_obj);

WASM_IMPORT("gpu", "beginRenderPass")
uint32_t gpu_begin_render_pass(uint32_t ctx_obj, uint32_t desc_obj, uint32_t x, uint32_t y,
                               uint32_t width, uint32_t height);
WASM_IMPORT("gpu", "endRenderPass")
void gpu_end_render_pass(uint32_t ctx_obj, uint32_t render_pass_obj);
WASM_IMPORT("gpu", "setPipeline")
void gpu_set_pipeline(uint32_t ctx_obj, uint32_t render_pass_obj, uint32_t pipeline_obj);
WASM_IMPORT("gpu", "setBindGroup")
void gpu_set_bind_group(uint32_t ctx_obj, uint32_t render_pass_obj, uint32_t slot,
                        uint32_t bind_group_obj);
WASM_IMPORT("gpu", "setBuffer")
void gpu_set_buffer(uint32_t ctx_obj, uint32_t render_pass_obj, uint32_t slot, uint32_t buffer_obj,
                    uint32_t offset, int32_t size);
WASM_IMPORT("gpu", "setIndexU16Buffer")
void gpu_set_index_u16_buffer(uint32_t ctx_obj, uint32_t render_pass_obj, uint32_t buffer_obj,
                              uint32_t offset, int32_t size);
WASM_IMPORT("gpu", "setIndexU32Buffer")
void gpu_set_index_u32_buffer(uint32_t ctx_obj, uint32_t render_pass_obj, uint32_t buffer_obj,
                              uint32_t offset, int32_t size);

WASM_IMPORT("gpu", "draw")
void gpu_draw(uint32_t ctx_obj, uint32_t render_pass_obj, uint32_t vertex_count,
              uint32_t instance_count, uint32_t first_vertex, const uint32_t first_instance);
WASM_IMPORT("gpu", "drawIndexed")
void gpu_draw_indexed(uint32_t ctx_obj, uint32_t render_pass_obj, uint32_t index_count,
                      uint32_t instance_count, uint32_t first_index, int32_t base_vertex,
                      uint32_t first_instance);
WASM_IMPORT("gpu", "drawIndirect")
void gpu_draw_indirect(uint32_t ctx_obj, uint32_t render_pass_obj, uint32_t indirect_buffer_obj,
                       uint32_t indirect_offset);
WASM_IMPORT("gpu", "drawIndexedIndirect")
void gpu_draw_indexed_indirect(uint32_t ctx_obj, uint32_t render_pass_obj,
                               uint32_t indirect_buffer_obj, uint32_t indirect_offset);

////////////////////////////////
// Object property setters
WASM_IMPORT("gpu", "setObjectBindGroupLayoutProperty")
void gpu_set_object_bind_group_layout_property(uint32_t ctx_obj, uint32_t obj, const char* name,
                                               uint32_t bind_group_layout_obj);
WASM_IMPORT("gpu", "setObjectBindGroupProperty")
void gpu_set_object_bind_group_property(uint32_t ctx_obj, uint32_t obj, const char* name,
                                        uint32_t bind_group_obj);
WASM_IMPORT("gpu", "setObjectShaderModuleProperty")
void gpu_set_object_shader_module_property(uint32_t ctx_obj, uint32_t obj, const char* name,
                                           uint32_t shader_module_obj);
WASM_IMPORT("gpu", "setObjectPipelineLayoutProperty")
void gpu_set_object_pipeline_layout_property(uint32_t ctx_obj, uint32_t obj, const char* name,
                                             uint32_t pipeline_layout_obj);
WASM_IMPORT("gpu", "setObjectPipelineProperty")
void gpu_set_object_pipeline_property(uint32_t ctx_obj, uint32_t obj, const char* name,
                                      uint32_t pipeline_obj);
WASM_IMPORT("gpu", "setObjectBufferProperty")
void gpu_set_object_buffer_property(uint32_t ctx_obj, uint32_t obj, const char* name,
                                    uint32_t buffer_obj);
WASM_IMPORT("gpu", "setObjectTextureProperty")
void gpu_set_object_texture_property(uint32_t ctx_obj, uint32_t obj, const char* name,
                                     uint32_t texture_obj);
WASM_IMPORT("gpu", "setObjectTextureViewProperty")
void gpu_set_object_texture_view_property(uint32_t ctx_obj, uint32_t obj, const char* name,
                                          uint32_t texture_view_obj);
WASM_IMPORT("gpu", "setObjectRenderPassProperty")
void gpu_set_object_render_pass_property(uint32_t ctx_obj, uint32_t obj, const char* name,
                                         uint32_t render_pass_obj);
WASM_IMPORT("gpu", "setObjectSamplerProperty")
void gpu_set_object_sampler_property(uint32_t ctx_obj, uint32_t obj, const char* name,
                                     uint32_t sampler_obj);

////////////////////////////////
// Releasers
WASM_IMPORT("gpu", "releaseBindGroupLayout")
void gpu_release_bind_group_layout(uint32_t ctx_obj, uint32_t bind_group_layout_obj);
WASM_IMPORT("gpu", "releaseBindGroup")
void gpu_release_bind_group(uint32_t ctx_obj, uint32_t bind_group_obj);
WASM_IMPORT("gpu", "releaseShaderModule")
void gpu_release_shader_module(uint32_t ctx_obj, uint32_t shader_module_obj);
WASM_IMPORT("gpu", "releasePipelineLayout")
void gpu_release_pipeline_layout(uint32_t ctx_obj, uint32_t pipeline_layout_obj);
WASM_IMPORT("gpu", "releasePipeline")
void gpu_release_pipeline(uint32_t ctx_obj, uint32_t pipeline_obj);
WASM_IMPORT("gpu", "releaseBuffer")
void gpu_release_buffer(uint32_t ctx_obj, uint32_t buffer_obj);
WASM_IMPORT("gpu", "releaseTexture")
void gpu_release_texture(uint32_t ctx_obj, uint32_t texture_obj);
WASM_IMPORT("gpu", "releaseTextureView")
void gpu_release_texture_view(uint32_t ctx_obj, uint32_t texture_view_obj);
WASM_IMPORT("gpu", "releaseRenderPass")
void gpu_release_render_pass(uint32_t ctx_obj, uint32_t render_pass_obj);
WASM_IMPORT("gpu", "releaseSampler")
void gpu_release_sampler(uint32_t ctx_obj, uint32_t sampler_obj);

}  // namespace detail

}  // namespace prism::js
