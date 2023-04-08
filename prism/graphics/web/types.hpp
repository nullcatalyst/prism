#pragma once

#include "prism/common/debug.hpp"
#include "prism/common/log.hpp"
#include "prism/common/shared.hpp"
#include "prism/js/gpu.hpp"
#include "prism/js/object.hpp"
#include "webgpu-headers/webgpu.h"

namespace prism::graphics::inline web {

template <typename T, typename Dtor>
class WebGpuObject
    : public common::Shared<std::pair<js::detail::ObjectId, js::detail::ObjectId>, Dtor> {
    using Parent = common::Shared<std::pair<js::detail::ObjectId, js::detail::ObjectId>, Dtor>;

  public:
    constexpr WebGpuObject() = default;
    constexpr WebGpuObject(js::detail::ObjectId ctx, js::detail::ObjectId self)
        : Parent{std::make_pair(ctx, self)} {}

    [[nodiscard]] constexpr js::detail::ObjectId obj_id() const { return Parent::get().second; }

    [[nodiscard]] constexpr operator T() const {
        return reinterpret_cast<T>(static_cast<uintptr_t>(obj_id()));
    }
};

#define GPU_TYPE_REF($type, $dtor)                                                      \
    struct $type##_dtor {                                                               \
        static void call(std::pair<js::detail::ObjectId, js::detail::ObjectId> value) { \
            $dtor(value.first, value.second);                                           \
        }                                                                               \
    };                                                                                  \
    using $type = WebGpuObject<WGPU##$type, $type##_dtor>

GPU_TYPE_REF(RenderPassEncoder, js::detail::gpu_release_render_pass);
GPU_TYPE_REF(BindGroupLayout, js::detail::gpu_release_bind_group_layout);
GPU_TYPE_REF(BindGroup, js::detail::gpu_release_bind_group);
GPU_TYPE_REF(ShaderModule, js::detail::gpu_release_shader_module);
GPU_TYPE_REF(PipelineLayout, js::detail::gpu_release_pipeline_layout);
GPU_TYPE_REF(RenderPipeline, js::detail::gpu_release_pipeline);
GPU_TYPE_REF(Buffer, js::detail::gpu_release_buffer);
GPU_TYPE_REF(Texture, js::detail::gpu_release_texture);
GPU_TYPE_REF(TextureView, js::detail::gpu_release_texture_view);
GPU_TYPE_REF(Sampler, js::detail::gpu_release_sampler);

}  // namespace prism::graphics::inline web
