#pragma once

#include "prism/common/debug.hpp"
#include "prism/common/log.hpp"
#include "prism/common/shared.hpp"
#include "webgpu-headers/webgpu.h"
#include "wgpu/wgpu.h"

namespace prism::graphics::inline wgpu {

// Smart ptr types for WGPU objects.

#define PRISM_WGPU_TYPE_REF($type, $dtor)                     \
    struct $type##_dtor {                                     \
        static void call(WGPU##$type value) { $dtor(value); } \
    };                                                        \
    using $type = ::prism::common::Shared<WGPU##$type##Impl*, $type##_dtor>

PRISM_WGPU_TYPE_REF(Instance, wgpuInstanceDrop);
PRISM_WGPU_TYPE_REF(Surface, wgpuSurfaceDrop);
PRISM_WGPU_TYPE_REF(Adapter, wgpuAdapterDrop);
PRISM_WGPU_TYPE_REF(Device, wgpuDeviceDrop);
PRISM_WGPU_TYPE_REF(SwapChain, wgpuSwapChainDrop);
PRISM_WGPU_TYPE_REF(Queue,
                    (void));  // The queue is owned by the device, so we don't need to drop it.
PRISM_WGPU_TYPE_REF(CommandEncoder, wgpuCommandEncoderDrop);
PRISM_WGPU_TYPE_REF(RenderBundleEncoder, wgpuRenderBundleEncoderDrop);
PRISM_WGPU_TYPE_REF(RenderPassEncoder, wgpuRenderPassEncoderDrop);
PRISM_WGPU_TYPE_REF(BindGroupLayout, wgpuBindGroupLayoutDrop);
PRISM_WGPU_TYPE_REF(BindGroup, wgpuBindGroupDrop);
PRISM_WGPU_TYPE_REF(ShaderModule, wgpuShaderModuleDrop);
PRISM_WGPU_TYPE_REF(PipelineLayout, wgpuPipelineLayoutDrop);
PRISM_WGPU_TYPE_REF(RenderPipeline, wgpuRenderPipelineDrop);
PRISM_WGPU_TYPE_REF(ComputePipeline, wgpuComputePipelineDrop);
PRISM_WGPU_TYPE_REF(Buffer, wgpuBufferDrop);
PRISM_WGPU_TYPE_REF(Texture, wgpuTextureDrop);
PRISM_WGPU_TYPE_REF(TextureView, wgpuTextureViewDrop);
PRISM_WGPU_TYPE_REF(Sampler, wgpuSamplerDrop);

#undef PRISM_WGPU_TYPE_REF

}  // namespace prism::graphics::inline wgpu
