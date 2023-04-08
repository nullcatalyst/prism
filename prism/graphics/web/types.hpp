#pragma once

#include "prism/common/debug.hpp"
#include "prism/common/log.hpp"
#include "prism/common/shared.hpp"
#include "prism/js/gpu.hpp"
#include "prism/js/object.hpp"
#include "webgpu-headers/webgpu.h"

namespace prism::graphics::inline web {

template <typename T, typename Dtor>
class WebGpuObject : public common::Shared<std::pair<js::ObjectId, js::ObjectId>, Dtor> {
    using Parent = common::Shared<std::pair<js::ObjectId, js::ObjectId>, Dtor>;

  public:
    constexpr WebGpuObject() = default;
    constexpr WebGpuObject(js::ObjectId ctx, js::ObjectId self)
        : Parent{std::make_pair(ctx, self)} {}

    [[nodiscard]] constexpr js::ObjectId obj_id() const { return Parent::get().second; }

    [[nodiscard]] constexpr operator T() const {
        return reinterpret_cast<T>(static_cast<uintptr_t>(obj_id()));
    }
};

#define GPU_TYPE_REF($type, $dtor)                                      \
    struct $type##_dtor {                                               \
        static void call(std::pair<js::ObjectId, js::ObjectId> value) { \
            $dtor(value.first, value.second);                           \
        }                                                               \
    };                                                                  \
    using $type = WebGpuObject<WGPU##$type, gpu_##$type##_dtor>

GPU_TYPE_REF(RenderPassEncoder, gpu_release_render_pass);
GPU_TYPE_REF(BindGroupLayout, gpu_release_bind_group_layout);
GPU_TYPE_REF(BindGroup, gpu_release_bind_group);
GPU_TYPE_REF(ShaderModule, gpu_release_shader_module);
GPU_TYPE_REF(PipelineLayout, gpu_release_pipeline_layout);
GPU_TYPE_REF(RenderPipeline, gpu_release_pipeline);
GPU_TYPE_REF(Buffer, gpu_release_buffer);
GPU_TYPE_REF(Texture, gpu_release_texture);
GPU_TYPE_REF(TextureView, gpu_release_texture_view);
GPU_TYPE_REF(Sampler, gpu_release_sampler);

}  // namespace prism::graphics::inline web
