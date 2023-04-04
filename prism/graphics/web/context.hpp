#pragma once

#include <span>

#include "base/wasm/dom/dom.hpp"
#include "prism/graphics/web/types.hpp"

namespace prism::graphics::inline web {

class Context final {
    base::wasm::Object _context;

    uint32_t      _width          = 0;
    uint32_t      _height         = 0;
    float         _pixel_ratio    = 1.0f;
    TextureFormat _surface_format = WGPUTextureFormat_Undefined;

  public:
    Context() = default;
    Context(base::wasm::dom::HtmlCanvasElement canvas);

    Context(const Context& other)            = delete;
    Context& operator=(const Context& other) = delete;

    Context(Context&& other)            = default;
    Context& operator=(Context&& other) = default;

    ~Context() = default;

    void resize(const uint32_t width, const uint32_t height, const float pixel_ratio = 1.0f) {
        _width       = width;
        _height      = height;
        _pixel_ratio = pixel_ratio;
    }

    [[nodiscard]] constexpr uint32_t      width() const noexcept { return _width; }
    [[nodiscard]] constexpr uint32_t      height() const noexcept { return _height; }
    [[nodiscard]] constexpr float         pixel_ratio() const noexcept { return _pixel_ratio; }
    [[nodiscard]] constexpr TextureFormat surface_format() const noexcept {
        return _surface_format;
    }

    BindGroupLayout create_bind_group_layout(const desc::BindGroupLayout& layout_desc);
    ShaderModule    create_shader_module(const char* source);
    PipelineLayout  create_pipeline_layout(const desc::PipelineLayout& layout_desc);
    RenderPipeline  create_render_pipeline(const desc::RenderPipeline& pipeline_desc);
    // ComputePipeline create_compute_pipeline(const desc::ComputePipeline& pipeline_desc);
    BindGroup create_bind_group(const desc::BindGroup& bind_group_desc);
    Buffer    create_buffer(const uint32_t usage, const uint64_t data_size);
    template <typename T>
    Buffer create_buffer(const uint32_t usage, const std::span<const T> data) {
        return create_buffer_with_data(usage, data.data(), data.size_bytes());
    }
    Buffer create_buffer_with_data(const uint32_t usage, const void* data,
                                   const uint64_t data_size);
    Buffer create_buffer_with_partial_data(const uint32_t usage, const uint64_t full_size,
                                           const uint64_t offset, const void* data,
                                           const uint64_t data_size);
    void   update_buffer(const Buffer& buffer, const uint64_t offset, const void* data,
                         const uint64_t data_size);
    template <typename T>
    void update_buffer(const Buffer& buffer, const uint64_t offset, const std::span<const T> data) {
        update_buffer(buffer, offset, data.data(), data.size_bytes());
    }
    Texture create_texture_2d(const uint32_t usage, const WGPUTextureFormat format,
                              const uint32_t width, const uint32_t height);
    void    update_texture_2d(const Texture& texture, const uint32_t width, const uint32_t height,
                              const void* data, const uint64_t data_size);
    TextureView create_texture_view_2d(const Texture& texture, const TextureFormat format);
    Sampler     create_sampler(WGPUAddressMode address_mode, WGPUFilterMode min_filter,
                               WGPUFilterMode mag_filter, WGPUFilterMode mipmap_filter);
    Sampler     create_sampler_comparison(WGPUAddressMode address_mode, WGPUFilterMode min_filter,
                                          WGPUFilterMode mag_filter, WGPUFilterMode mipmap_filter,
                                          WGPUCompareFunction compare);

    TextureView swap_chain_view();

    RenderPassEncoder begin_render_pass(const desc::RenderPass& render_pass_desc, uint32_t width,
                                        uint32_t height);
    void              end_render_pass(const RenderPassEncoder& render_pass);
    void set_pipeline(const RenderPassEncoder& render_pass, const RenderPipeline& pipeline);
    void set_bind_group(const RenderPassEncoder& render_pass, const uint32_t index,
                        const BindGroup& bind_group);
    void set_buffer(const RenderPassEncoder& render_pass, const uint32_t slot,
                    const Buffer& buffer);
    void set_buffer_with_offset(const RenderPassEncoder& render_pass, const uint32_t slot,
                                const Buffer& buffer, const uint64_t offset,
                                const uint64_t length = WGPU_WHOLE_SIZE);
    void set_index_u16_buffer(const RenderPassEncoder& render_pass, const Buffer& buffer);
    void set_index_u16_buffer_with_offset(const RenderPassEncoder& render_pass,
                                          const Buffer& buffer, const uint64_t offset,
                                          const uint64_t length = WGPU_WHOLE_SIZE);
    void set_index_u32_buffer(const RenderPassEncoder& render_pass, const Buffer& buffer);
    void set_index_u32_buffer_with_offset(const RenderPassEncoder& render_pass,
                                          const Buffer& buffer, const uint64_t offset,
                                          const uint64_t length = WGPU_WHOLE_SIZE);
    void draw(const RenderPassEncoder& render_pass, const uint32_t vertex_count,
              const uint32_t instance_count, const uint32_t first_vertex = 0,
              const uint32_t first_instance = 0);
    void draw_indexed(const RenderPassEncoder& render_pass, const uint32_t index_count,
                      const uint32_t instance_count, const uint32_t first_index = 0,
                      const int32_t base_vertex = 0, const uint32_t first_instance = 0);
    void draw_indirect(const RenderPassEncoder& render_pass, const Buffer& indirect_buffer,
                       const uint64_t indirect_offset = 0);
    void draw_indexed_indirect(const RenderPassEncoder& render_pass, const Buffer& indirect_buffer,
                               const uint64_t indirect_offset = 0);
    void draw_multi_indirect(const RenderPassEncoder& render_pass, const Buffer& indirect_buffer,
                             const uint64_t indirect_offset = 0, const uint32_t indirect_count = 1);
    void draw_multi_indexed_indirect(const RenderPassEncoder& render_pass,
                                     const Buffer&            indirect_buffer,
                                     const uint64_t           indirect_offset = 0,
                                     const uint32_t           indirect_count  = 1);

    void start_frame();
    void present_frame();
};

}  // namespace prism::graphics::inline web
