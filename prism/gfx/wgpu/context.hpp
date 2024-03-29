#pragma once

#include <span>

#include "prism/gfx/enums.hpp"
#include "prism/gfx/types.hpp"
#include "prism/gfx/wgpu/types.hpp"

namespace prism::gfx::inline wgpu {

class Context final {
    Instance       _instance   = nullptr;
    Surface        _surface    = nullptr;
    Adapter        _adapter    = nullptr;
    Device         _device     = nullptr;
    SwapChain      _swap_chain = nullptr;
    Queue          _queue      = nullptr;
    CommandEncoder _encoder    = nullptr;

    TextureFormat _surface_format      = TextureFormat::Undefined;
    uint32_t      _surface_width       = 0;
    uint32_t      _surface_height      = 0;
    float         _surface_pixel_ratio = 1.0f;

  public:
    static void enable_debug();

    constexpr Context() = default;
    Context(const WGPUInstance instance, const WGPUSurface surface, const uint32_t surface_width,
            const uint32_t surface_height, const PresentMode present_mode,
            const float surface_pixel_ratio = 1.0f);

    Context(const Context& other)            = delete;
    Context& operator=(const Context& other) = delete;
    Context(Context&& other)                 = default;
    Context& operator=(Context&& other)      = default;

    ~Context() = default;

    [[nodiscard]] constexpr TextureFormat surface_format() const noexcept {
        return _surface_format;
    }
    [[nodiscard]] constexpr uint32_t surface_width() const noexcept { return _surface_width; }
    [[nodiscard]] constexpr uint32_t surface_height() const noexcept { return _surface_height; }
    [[nodiscard]] constexpr float    surface_pixel_ratio() const noexcept {
        return _surface_pixel_ratio;
    }

    /**
     * Invalidate and recreate the swap chain.
     *
     * @param surface_width The width of the renderable surface area.
     * @param surface_height The height of the renderable surface area.
     * @param present_mode The present mode to use for the swap chain. Typically you want to use
     * `Fifo` for vsync, and `Mailbox` otherwise. `Immediate` can technically be faster (with the
     * caveat that it can result in screen tearing), but with modern variable refresh rate displays,
     * `Immediate` is no longer recommended.
     * @param surface_pixel_ratio The pixel ratio of the surface. This is not actually used when
     * recreating the swap chain, it is merely cached because it is a useful value for the user
     * rendering anything to have. Use `0.0f` to reuse the previous pixel ratio, as this is probably
     * the most common case.
     */
    void recreate_swap_chain(const uint32_t surface_width, const uint32_t surface_height,
                             const PresentMode present_mode,
                             const float       surface_pixel_ratio = 0.0f);

    ////////////////////////////////
    // Initialization functions

    BindGroupLayout create_bind_group_layout(
        const BindGroupLayoutDescriptor& bind_group_layout_desc);
    BindGroup       create_bind_group(const BindGroupDescriptor& bind_group_desc);
    ShaderModule    create_shader_module(const char* source);
    PipelineLayout  create_pipeline_layout(const PipelineLayoutDescriptor& pipeline_layout_desc);
    ComputePipeline create_compute_pipeline(const ComputePipelineDescriptor& compute_pipeline_desc);
    RenderPipeline  create_render_pipeline(const RenderPipelineDescriptor& render_pipeline_desc);

    Buffer create_buffer(const BufferUsage usage, const uint64_t buffer_size,
                         const void* data = nullptr, const uint64_t data_size = 0,
                         const uint64_t data_offset_into_buffer = 0);
    void   update_buffer(const Buffer& buffer, const void* data, const uint64_t data_size,
                         const uint64_t data_offset_into_buffer = 0);

    Texture create_texture_2d(const TextureUsage usage, const TextureFormat format,
                              const uint32_t width, const uint32_t height);
    void    update_texture_2d(const Texture& texture, const uint32_t width, const uint32_t height,
                              const void* data, const uint64_t data_size);
    TextureView create_texture_view_2d(const Texture& texture, const TextureFormat format);

    Sampler create_sampler(AddressMode address_mode  = AddressMode::ClampToEdge,
                           FilterMode  min_filter    = FilterMode::Nearest,
                           FilterMode  mag_filter    = FilterMode::Nearest,
                           FilterMode  mipmap_filter = FilterMode::Nearest);
    Sampler create_sampler_comparison(CompareFunction compare_function = CompareFunction::Always,
                                      AddressMode     address_mode     = AddressMode::ClampToEdge,
                                      FilterMode      min_filter       = FilterMode::Nearest,
                                      FilterMode      mag_filter       = FilterMode::Nearest,
                                      FilterMode      mipmap_filter    = FilterMode::Nearest);

    ////////////////////////////////
    // Command functions

    void        start_frame();
    void        present_frame();
    TextureView swap_chain_view();

    // Compute pass

    ComputePassEncoder begin_compute_pass(const ComputePassDescriptor& compute_pass_desc);
    void               end_compute_pass(const ComputePassEncoder& compute_pass);

    void set_pipeline(const ComputePassEncoder& compute_pass, const ComputePipeline& pipeline);
    void set_bind_group(const ComputePassEncoder& compute_pass, const uint32_t index,
                        const BindGroup& bind_group);

    void dispatch(const ComputePassEncoder& compute_pass, const uint32_t x, const uint32_t y = 1,
                  const uint32_t z = 1);

    // Render pass

    RenderPassEncoder begin_render_pass(const RenderPassDescriptor& render_pass_desc,
                                        const uint32_t x, const uint32_t y, const uint32_t width,
                                        const uint32_t height);
    void              end_render_pass(const RenderPassEncoder& render_pass);

    void set_pipeline(const RenderPassEncoder& render_pass, const RenderPipeline& pipeline);
    void set_bind_group(const RenderPassEncoder& render_pass, const uint32_t index,
                        const BindGroup& bind_group);
    void set_buffer(const RenderPassEncoder& render_pass, const uint32_t slot, const Buffer& buffer,
                    const uint64_t offset = 0, const uint64_t size = WGPU_WHOLE_SIZE);
    void set_index_u16_buffer(const RenderPassEncoder& render_pass, const Buffer& buffer,
                              const uint64_t offset = 0, const uint64_t size = WGPU_WHOLE_SIZE);
    void set_index_u32_buffer(const RenderPassEncoder& render_pass, const Buffer& buffer,
                              const uint64_t offset = 0, const uint64_t size = WGPU_WHOLE_SIZE);

    void draw(const RenderPassEncoder& render_pass, const uint32_t vertex_count,
              const uint32_t instance_count = 1, const uint32_t first_vertex = 0,
              const uint32_t first_instance = 0);
    void draw_indexed(const RenderPassEncoder& render_pass, const uint32_t index_count,
                      const uint32_t instance_count = 1, const uint32_t first_index = 0,
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
};

}  // namespace prism::gfx::inline wgpu
