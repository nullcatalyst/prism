#pragma once

#include <iostream>
#include <memory>

#include "prism/common/debug.hpp"
#include "webgpu-headers/webgpu.h"
#include "wgpu/wgpu.h"

namespace prism::graphics::inline wgpu {

/**
 * This is a smart pointer that is used to wrap all the WebGPU types.
 *
 * It is a reference counted pointer that will automatically drop the value when the last reference
 * is released.
 *
 * A std::shared_ptr could have been used, but it has some overhead that we don't need. For example,
 * the reference count is stored in a separate block of memory, which means that the pointer to the
 * value is not contiguous with the reference count and needing more than a single pointer value per
 * reference.
 */
template <typename T, typename Dtor>
class Ptr {
    struct Impl {
        T*       value;
        uint32_t ref_count;
    };

    Impl* _impl = nullptr;

  public:
    constexpr Ptr() : _impl{nullptr} {}
    constexpr Ptr(std::nullptr_t) : _impl{nullptr} {}
    explicit Ptr(T* value) : _impl{value != nullptr ? new Impl{value, 1} : nullptr} {}
    Ptr(const Ptr& other) : _impl{other._impl} { _retain(); }
    constexpr Ptr(Ptr&& other) : _impl{other._impl} { other._impl = nullptr; }
    ~Ptr() { _release(); }

    Ptr& operator=(std::nullptr_t) {
        _release();
        return *this;
    }

    Ptr& operator=(T* value) {
        if (value == nullptr) {
            _release();
            return *this;
        }

        // This is the only copy, reuse the stored Impl to avoid a deallocation and allocation
        if (_impl != nullptr && _impl->ref_count == 1) {
            Dtor::call(_impl->value);
            _impl->value = value;
            return *this;
        }

        _release();
        _impl = new Impl{value, 1};
        return *this;
    }

    Ptr& operator=(const Ptr& other) {
        PRISM_DEBUG_ASSERT_CONDITION(this != &other);
        _release();
        _impl = other._impl;
        _retain();
        return *this;
    }

    Ptr& operator=(Ptr&& other) {
        PRISM_DEBUG_ASSERT_CONDITION(this != &other);
        _release();
        _impl       = other._impl;
        other._impl = nullptr;
        return *this;
    }

    constexpr operator T*() const { return _impl != nullptr ? _impl->value : nullptr; }

    void _already_released() { _impl = nullptr; }

  private:
    void _retain() {
        if (_impl == nullptr) [[unlikely]] {
            return;
        }
        ++_impl->ref_count;
    }

    void _release() {
        if (_impl == nullptr) [[unlikely]] {
            return;
        }

        --_impl->ref_count;
        if (_impl->ref_count == 0) {
            Dtor::call(_impl->value);
            delete _impl;
        }

        _impl = nullptr;
    }
};

#define GPU_TYPE_REF($type, $dtor)                            \
    struct $type##_dtor {                                     \
        static void call(WGPU##$type value) { $dtor(value); } \
    };                                                        \
    using $type = Ptr<WGPU##$type##Impl, $type##_dtor>

GPU_TYPE_REF(Instance, wgpuInstanceDrop);
GPU_TYPE_REF(Surface, wgpuSurfaceDrop);
GPU_TYPE_REF(Adapter, wgpuAdapterDrop);
GPU_TYPE_REF(Device, wgpuDeviceDrop);
GPU_TYPE_REF(SwapChain, wgpuSwapChainDrop);
GPU_TYPE_REF(Queue, (void));  // The queue is owned by the device, so we don't need to drop it.
GPU_TYPE_REF(CommandEncoder, wgpuCommandEncoderDrop);
GPU_TYPE_REF(RenderBundleEncoder, wgpuRenderBundleEncoderDrop);
GPU_TYPE_REF(RenderPassEncoder, wgpuRenderPassEncoderDrop);
GPU_TYPE_REF(BindGroupLayout, wgpuBindGroupLayoutDrop);
GPU_TYPE_REF(BindGroup, wgpuBindGroupDrop);
GPU_TYPE_REF(ShaderModule, wgpuShaderModuleDrop);
GPU_TYPE_REF(PipelineLayout, wgpuPipelineLayoutDrop);
GPU_TYPE_REF(RenderPipeline, wgpuRenderPipelineDrop);
GPU_TYPE_REF(ComputePipeline, wgpuComputePipelineDrop);
GPU_TYPE_REF(Buffer, wgpuBufferDrop);
GPU_TYPE_REF(Texture, wgpuTextureDrop);
GPU_TYPE_REF(TextureView, wgpuTextureViewDrop);
GPU_TYPE_REF(Sampler, wgpuSamplerDrop);

}  // namespace prism::graphics::inline wgpu
