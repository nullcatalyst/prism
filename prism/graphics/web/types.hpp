#pragma once

#include "base/memory/shared.hpp"
#include "base/wasm/object/object.hpp"
#include "prism/common/debug.hpp"
#include "prism/graphics/web/js_api.hpp"
#include "webgpu-headers/webgpu.h"

namespace prism::graphics::inline web {

////////////////////////////////////////////////////////////////////////////////
// Enums

using TextureFormat = WGPUTextureFormat;

////////////////////////////////////////////////////////////////////////////////
// Descriptors

namespace desc {

#define GPU_TYPE_DESC($type) using $type = WGPU##$type##Descriptor

GPU_TYPE_DESC(BindGroupLayout);
GPU_TYPE_DESC(BindGroup);

GPU_TYPE_DESC(PipelineLayout);
GPU_TYPE_DESC(ShaderModule);
GPU_TYPE_DESC(RenderPipeline);
GPU_TYPE_DESC(Buffer);
GPU_TYPE_DESC(RenderPass);
GPU_TYPE_DESC(Texture);

#undef GPU_TYPE_DESC

#define GPU_TYPE_DESC($type) using $type = WGPU##$type

GPU_TYPE_DESC(BindGroupLayoutEntry);
GPU_TYPE_DESC(BufferBindingLayout);
GPU_TYPE_DESC(SamplerBindingLayout);
GPU_TYPE_DESC(TextureBindingLayout);
GPU_TYPE_DESC(StorageTextureBindingLayout);

GPU_TYPE_DESC(RenderPassColorAttachment);
GPU_TYPE_DESC(BlendState);
GPU_TYPE_DESC(ColorTargetState);
GPU_TYPE_DESC(FragmentState);
GPU_TYPE_DESC(VertexState);
GPU_TYPE_DESC(PrimitiveState);
GPU_TYPE_DESC(MultisampleState);
GPU_TYPE_DESC(Color);

#undef GPU_TYPE_DESC

struct DrawIndirectCommand {
    uint32_t vertexCount;
    uint32_t instanceCount;
    uint32_t firstVertex;
    uint32_t firstInstance;
};

struct DrawIndexedIndirectCommand {
    uint32_t indexCount;
    uint32_t instanceCount;
    uint32_t firstIndex;
    int32_t  baseVertex;
    uint32_t firstInstance;
};

}  // namespace desc

////////////////////////////////////////////////////////////////////////////////
// Opaque types

template <typename T, typename Dtor>
class WebGpuObject
    : public base::memory::Shared<std::pair<base::wasm::ObjectId, base::wasm::ObjectId>, Dtor> {
  public:
    constexpr WebGpuObject() = default;
    constexpr WebGpuObject(base::wasm::ObjectId ctx, base::wasm::ObjectId self)
        : base::memory::Shared<std::pair<base::wasm::ObjectId, base::wasm::ObjectId>, Dtor>{
              std::make_pair(ctx, self)} {}

    [[nodiscard]] constexpr base::wasm::ObjectId obj_id() const {
        return base::memory::Shared<std::pair<base::wasm::ObjectId, base::wasm::ObjectId>,
                                    Dtor>::_get()
            .second;
    }

    [[nodiscard]] constexpr operator T() const {
        return reinterpret_cast<T>(static_cast<uintptr_t>(obj_id()));
    }
};

#define GPU_TYPE_REF($type, $dtor)                                                      \
    struct _gpu_##$type##_dtor {                                                        \
        static void call(std::pair<base::wasm::ObjectId, base::wasm::ObjectId> value) { \
            $dtor(value.first, value.second);                                           \
        }                                                                               \
    };                                                                                  \
    using $type = WebGpuObject<WGPU##$type, _gpu_##$type##_dtor>

// These commented out types are hidden within the implementation and don't need to be defined
// here GPU_TYPE_REF(Instance, NOOP); GPU_TYPE_REF(Surface, NOOP); GPU_TYPE_REF(Adapter, NOOP);
// GPU_TYPE_REF(Device, _gpu_d);
// GPU_TYPE_REF(SwapChain, NOOP);
// GPU_TYPE_REF(Queue, NOOP);
// GPU_TYPE_REF(CommandEncoder, wgpuCommandEncoderDrop);
GPU_TYPE_REF(RenderPassEncoder, _gpu_release_render_pass);
GPU_TYPE_REF(BindGroupLayout, _gpu_release_bind_group_layout);
GPU_TYPE_REF(BindGroup, _gpu_release_bind_group);
GPU_TYPE_REF(ShaderModule, _gpu_release_shader_module);
GPU_TYPE_REF(PipelineLayout, _gpu_release_pipeline_layout);
GPU_TYPE_REF(RenderPipeline, _gpu_release_pipeline);
GPU_TYPE_REF(Buffer, _gpu_release_buffer);
GPU_TYPE_REF(Texture, _gpu_release_texture);
GPU_TYPE_REF(TextureView, _gpu_release_texture_view);
GPU_TYPE_REF(Sampler, _gpu_release_sampler);

#undef NOOP

}  // namespace prism::graphics::inline web
