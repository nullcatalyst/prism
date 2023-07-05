#pragma once

#if defined(PRISM_BACKEND_WGPU)
#include "prism/gfx/wgpu/context.hpp"
#elif defined(PRISM_BACKEND_WEB)
#include "prism/gfx/web/context.hpp"
#else
#error "No GPU graphics backend defined"
#endif

#if __cplusplus >= 202002L && __has_include(<concepts>)

#include <concepts>

namespace prism::gfx::internal {

template <typename T>
concept Context = requires(T ctx) {
    { ctx.surface_format() } -> std::same_as<TextureFormat>;
    {
        ctx.create_bind_group_layout(std::declval<const BindGroupLayoutDescriptor&>())
    } -> std::same_as<BindGroupLayout>;
    { ctx.create_shader_module(std::declval<const char*>()) } -> std::same_as<ShaderModule>;
    {
        ctx.create_pipeline_layout(std::declval<const PipelineLayoutDescriptor&>())
    } -> std::same_as<PipelineLayout>;
    {
        ctx.create_render_pipeline(std::declval<const RenderPipelineDescriptor&>())
    } -> std::same_as<RenderPipeline>;
    {
        ctx.create_bind_group(std::declval<const BindGroupDescriptor&>())
    } -> std::same_as<BindGroup>;
    {
        ctx.create_buffer(std::declval<BufferUsage>(), std::declval<uint64_t>(),
                          std::declval<void*>(), std::declval<uint64_t>(), std::declval<uint64_t>())
    } -> std::same_as<Buffer>;
    {
        ctx.update_buffer(std::declval<const Buffer&>(), std::declval<void*>(),
                          std::declval<uint64_t>(), std::declval<uint64_t>())
    };
    {
        ctx.create_texture_2d(std::declval<TextureUsage>(), std::declval<TextureFormat>(),
                              std::declval<uint32_t>(), std::declval<uint32_t>())
    } -> std::same_as<Texture>;
    {
        ctx.update_texture_2d(std::declval<const Texture&>(), std::declval<uint32_t>(),
                              std::declval<uint32_t>(), std::declval<const void*>(),
                              std::declval<uint64_t>())
    };
    {
        ctx.create_texture_view_2d(std::declval<const Texture&>(), std::declval<TextureFormat>())
    } -> std::same_as<TextureView>;
    {
        ctx.create_sampler(std::declval<AddressMode>(), std::declval<FilterMode>(),
                           std::declval<FilterMode>(), std::declval<FilterMode>())
    } -> std::same_as<Sampler>;
    { ctx.swap_chain_view() } -> std::same_as<TextureView>;
    {
        ctx.begin_render_pass(std::declval<const RenderPassDescriptor&>())
    } -> std::same_as<RenderPassEncoder>;
    {
        ctx.begin_render_pass(std::declval<const RenderPassDescriptor&>(), std::declval<uint32_t>(),
                              std::declval<uint32_t>(), std::declval<uint32_t>(),
                              std::declval<uint32_t>())
    } -> std::same_as<RenderPassEncoder>;
    { ctx.end_render_pass(std::declval<const RenderPassEncoder&>()) };
    {
        ctx.set_pipeline(std::declval<const RenderPassEncoder&>(),
                         std::declval<const RenderPipeline&>())
    };
    {
        ctx.set_bind_group(std::declval<const RenderPassEncoder&>(), std::declval<uint32_t>(),
                           std::declval<const BindGroup&>())
    };
    {
        ctx.set_buffer(std::declval<const RenderPassEncoder&>(), std::declval<uint32_t>(),
                       std::declval<const Buffer&>())
    };
    {
        ctx.set_index_u16_buffer(std::declval<const RenderPassEncoder&>(),
                                 std::declval<const Buffer&>())
    };
    {
        ctx.set_index_u32_buffer(std::declval<const RenderPassEncoder&>(),
                                 std::declval<const Buffer&>())
    };
    {
        ctx.draw(std::declval<const RenderPassEncoder&>(), std::declval<uint32_t>(),
                 std::declval<uint32_t>())
    };
    {
        ctx.draw_indexed(std::declval<const RenderPassEncoder&>(), std::declval<uint32_t>(),
                         std::declval<uint32_t>())
    };

    { ctx.start_frame() };
    { ctx.present_frame() };
};

static_assert(Context<::prism::gfx::Context>);

}  // namespace prism::gfx::internal

#endif

namespace prism {
namespace gfx {}  // namespace gfx
using namespace ::prism::gfx;
}  // namespace prism
