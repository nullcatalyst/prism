#include "prism/graphics/wgpu/context.hpp"

#include "prism/common/platform.hpp"
#include "prism/graphics/common/webgpu.hpp"

namespace prism::graphics::inline wgpu {

void Context::enable_debug() {
#if defined(PRISM_BACKEND_WGPU)
    wgpuSetLogLevel(WGPULogLevel_Debug);
    wgpuSetLogCallback([](auto level, auto* msg,
                          void* user_data) { ::prism::common::log_message("[[WGPU]] ", msg); },
                       nullptr);
#endif
}

Context::Context(WGPUInstance instance, WGPUSurface surface, uint32_t surface_width,
                 uint32_t surface_height)
    : _instance{instance}, _surface{surface} {
    _adapter    = Adapter{common::request_adapter(_instance, _surface)};
    _device     = Device{common::create_device(_adapter)};
    _swap_chain = SwapChain{
        common::create_swap_chain(_device, _surface, _adapter, surface_width, surface_height)};
    _queue = Queue{common::get_queue(_device)};

    _surface_format = static_cast<TextureFormat>(wgpuSurfaceGetPreferredFormat(_surface, _adapter));
}

void Context::resize(const uint32_t surface_width, const uint32_t surface_height) {
    _swap_chain = SwapChain{
        common::create_swap_chain(_device, _surface, _adapter, surface_width, surface_height)};
}

BindGroupLayout Context::create_bind_group_layout(
    const BindGroupLayoutDescriptor& bind_group_layout_desc) {
    return BindGroupLayout{common::create_bind_group_layout(
        _device, reinterpret_cast<const WGPUBindGroupLayoutDescriptor&>(bind_group_layout_desc))};
}

ShaderModule Context::create_shader_module(const char* source) {
    return ShaderModule{common::create_shader_module(_device, source)};
}

PipelineLayout Context::create_pipeline_layout(
    const PipelineLayoutDescriptor& pipeline_layout_desc) {
    return PipelineLayout{common::create_pipeline_layout(
        _device, reinterpret_cast<const WGPUPipelineLayoutDescriptor&>(pipeline_layout_desc))};
}

RenderPipeline Context::create_render_pipeline(
    const RenderPipelineDescriptor& render_pipeline_desc) {
    return RenderPipeline{common::create_render_pipeline(
        _device, reinterpret_cast<const WGPURenderPipelineDescriptor&>(render_pipeline_desc))};
}

BindGroup Context::create_bind_group(const BindGroupDescriptor& bind_group_desc) {
    return BindGroup{common::create_bind_group(
        _device, reinterpret_cast<const WGPUBindGroupDescriptor&>(bind_group_desc))};
}

Buffer Context::create_buffer(const BufferUsage usage, const uint64_t buffer_size, const void* data,
                              const uint64_t data_size, const uint64_t data_offset_into_buffer) {
    return Buffer{common::create_buffer(_device, static_cast<WGPUBufferUsageFlags>(usage),
                                        buffer_size, data, data_size, data_offset_into_buffer)};
}

void Context::update_buffer(const Buffer& buffer, const void* data, const uint64_t data_size,
                            const uint64_t data_offset_into_buffer) {
    common::update_buffer(_device, _queue, buffer, data, data_size, data_offset_into_buffer);
}

Texture Context::create_texture_2d(const TextureUsage usage, const TextureFormat format,
                                   const uint32_t width, const uint32_t height) {
    return Texture{common::create_texture_2d(_device, static_cast<WGPUTextureUsageFlags>(usage),
                                             static_cast<WGPUTextureFormat>(format), width,
                                             height)};
}

void Context::update_texture_2d(const Texture& texture, const uint32_t width, const uint32_t height,
                                const void* data, const uint64_t data_size) {
    common::update_texture_2d(_device, _queue, texture, width, height, data, data_size);
}

TextureView Context::create_texture_view_2d(const Texture& texture, const TextureFormat format) {
    return TextureView{
        common::create_texture_view_2d(_device, texture, static_cast<WGPUTextureFormat>(format))};
}

Sampler Context::create_sampler(AddressMode address_mode, FilterMode min_filter,
                                FilterMode mag_filter, FilterMode mipmap_filter) {
    return Sampler{common::create_sampler(_device, static_cast<WGPUAddressMode>(address_mode),
                                          static_cast<WGPUFilterMode>(min_filter),
                                          static_cast<WGPUFilterMode>(mag_filter),
                                          static_cast<WGPUFilterMode>(mipmap_filter))};
}

Sampler Context::create_sampler_comparison(CompareFunction compare, AddressMode address_mode,
                                           FilterMode min_filter, FilterMode mag_filter,
                                           FilterMode mipmap_filter) {
    return Sampler{common::create_sampler_comparison(
        _device, static_cast<WGPUAddressMode>(address_mode),
        static_cast<WGPUFilterMode>(min_filter), static_cast<WGPUFilterMode>(mag_filter),
        static_cast<WGPUFilterMode>(mipmap_filter), static_cast<WGPUCompareFunction>(compare))};
}

void Context::start_frame() { _encoder = common::start_frame(_device); }

void Context::present_frame() {
    common::present_frame(_device, _swap_chain, _encoder, _queue);
    _encoder.UNSAFE_release_without_dtor();
}

TextureView Context::swap_chain_view() {
    return TextureView{common::swap_chain_view(_device, _swap_chain)};
}

RenderPassEncoder Context::begin_render_pass(const RenderPassDescriptor& render_pass_desc,
                                             uint32_t width, uint32_t height) {
    return RenderPassEncoder{common::begin_render_pass(
        _device, _encoder, reinterpret_cast<const WGPURenderPassDescriptor&>(render_pass_desc),
        width, height)};
}

void Context::end_render_pass(const RenderPassEncoder& render_pass) {
    common::end_render_pass(_device, render_pass);
    const_cast<RenderPassEncoder&>(render_pass).UNSAFE_release_without_dtor();
}

void Context::set_pipeline(const RenderPassEncoder& render_pass, const RenderPipeline& pipeline) {
    common::set_pipeline(_device, render_pass, pipeline);
}

void Context::set_bind_group(const RenderPassEncoder& render_pass, const uint32_t slot,
                             const BindGroup& bind_group) {
    common::set_bind_group(_device, render_pass, slot, bind_group);
}

void Context::set_buffer(const RenderPassEncoder& render_pass, const uint32_t slot,
                         const Buffer& buffer, const uint64_t offset, const uint64_t size) {
    common::set_buffer(_device, render_pass, slot, buffer, offset, size);
}

void Context::set_index_u16_buffer(const RenderPassEncoder& render_pass, const Buffer& buffer,
                                   const uint64_t offset, const uint64_t size) {
    common::set_index_u16_buffer(_device, render_pass, buffer, offset, size);
}

void Context::set_index_u32_buffer(const RenderPassEncoder& render_pass, const Buffer& buffer,
                                   const uint64_t offset, const uint64_t size) {
    common::set_index_u32_buffer(_device, render_pass, buffer, offset, size);
}

void Context::draw(const RenderPassEncoder& render_pass, const uint32_t vertex_count,
                   const uint32_t instance_count, const uint32_t first_vertex,
                   const uint32_t first_instance) {
    common::draw(_device, render_pass, vertex_count, instance_count, first_vertex, first_instance);
}

void Context::draw_indexed(const RenderPassEncoder& render_pass, const uint32_t index_count,
                           const uint32_t instance_count, const uint32_t first_index,
                           const int32_t base_vertex, const uint32_t first_instance) {
    common::draw_indexed(_device, render_pass, index_count, instance_count, first_index,
                         base_vertex, first_instance);
}

void Context::draw_indirect(const RenderPassEncoder& render_pass, const Buffer& indirect_buffer,
                            const uint64_t indirect_offset) {
    common::draw_indirect(_device, render_pass, indirect_buffer, indirect_offset);
}

void Context::draw_indexed_indirect(const RenderPassEncoder& render_pass,
                                    const Buffer& indirect_buffer, const uint64_t indirect_offset) {
    common::draw_indexed_indirect(_device, render_pass, indirect_buffer, indirect_offset);
}

void Context::draw_multi_indirect(const RenderPassEncoder& render_pass,
                                  const Buffer& indirect_buffer, const uint64_t indirect_offset,
                                  const uint32_t indirect_count) {
    // common::draw_multi_indirect(_device, render_pass, indirect_buffer, indirect_offset, count);

    // PRISM_DEBUG_SCOPE_START(device);
    wgpuRenderPassEncoderMultiDrawIndirect(render_pass, indirect_buffer, indirect_offset,
                                           indirect_count);
    // PRISM_DEBUG_SCOPE_END(device, "drawing multi indirect");
}

void Context::draw_multi_indexed_indirect(const RenderPassEncoder& render_pass,
                                          const Buffer&            indirect_buffer,
                                          const uint64_t           indirect_offset,
                                          const uint32_t           indirect_count) {
    // common::draw_indirect_indexed_multi(_device, render_pass, indirect_buffer, indirect_offset,
    // count);

    // PRISM_DEBUG_SCOPE_START(device);
    wgpuRenderPassEncoderMultiDrawIndexedIndirect(render_pass, indirect_buffer, indirect_offset,
                                                  indirect_count);
    // PRISM_DEBUG_SCOPE_END(device, "drawing multi indexed indirect");
}

}  // namespace prism::graphics::inline wgpu
