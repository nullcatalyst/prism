#pragma once

#include <iostream>
#include <memory>

#include "prism/common/debug.hpp"
#include "prism/common/log.hpp"
#include "prism/common/shared.hpp"
#include "webgpu-headers/webgpu.h"
#include "wgpu/wgpu.h"

namespace prism::common {

// TODO: Ideally the 2 copies / specializations of the Shared<> template would be merged, or better
// yet, removed entirely.

/**
 * A specialization specifically for the WGPUCommandEncoder object is required, because the
 * WGPUQueue object takes ownership of the WGPUCommandEncoder object after the frame is submitted.
 *
 * This specialization adds the custom UNSAFE_already_released() member function, allowing us to
 * avoid accidentally dropping the object in this case.
 */
template <typename Dtor>
    requires requires(WGPUCommandEncoderImpl* value) { Dtor::call(value); }
class Shared<WGPUCommandEncoderImpl*, Dtor> final {
    WGPUCommandEncoderImpl* _value;
    uint32_t*               _ref_count;

  public:
    constexpr Shared() : _value{nullptr}, _ref_count{0} {}
    constexpr Shared(const std::nullptr_t) : _value{nullptr}, _ref_count{0} {}
    constexpr Shared(WGPUCommandEncoderImpl* value) : _value{value}, _ref_count{nullptr} {
        if (_value != nullptr) {
            _ref_count = new uint32_t{1};
        }
    }
    constexpr Shared(const Shared& other) : _value{other._value}, _ref_count{other._ref_count} {
        retain();
    }
    constexpr Shared(Shared&& other) : _value{other._value}, _ref_count{other._ref_count} {
        other._value     = nullptr;
        other._ref_count = nullptr;
    }
    ~Shared() { release(); }

    Shared& operator=(const std::nullptr_t) {
        release();
        return *this;
    }

    Shared& operator=(const Shared& other) {
        release();
        _value     = other._value;
        _ref_count = other._ref_count;
        retain();
        return *this;
    }

    Shared& operator=(Shared&& other) {
        release();
        _value           = other._value;
        _ref_count       = other._ref_count;
        other._value     = nullptr;
        other._ref_count = nullptr;
        return *this;
    }

    constexpr operator WGPUCommandEncoderImpl*() const { return _value; }

    void UNSAFE_already_released() {
#if !defined(NDEBUG)
        if (_ref_count != nullptr && *_ref_count != 1) [[unlikely]] {
            ::prism::common::log_error("extra reference to CommandEncoder exists, leaking memory");
            std::abort();
        }
#endif
        delete _ref_count;
        _value     = nullptr;
        _ref_count = nullptr;
    }

  protected:
    void retain() {
        if (_ref_count == nullptr) [[unlikely]] {
            return;
        }
        ++(*_ref_count);
    }

    void release() {
        if (_ref_count == nullptr) [[unlikely]] {
            return;
        }

        --(*_ref_count);
        if (*_ref_count == 0) {
            Dtor::call(_value);
            delete _ref_count;
        }

        _value     = nullptr;
        _ref_count = nullptr;
    }
};

/**
 * A specialization specifically for the WGPURenderPassEncoder object is required, because the
 * WGPUQueue object takes ownership of the WGPURenderPassEncoder object after the frame is
 * submitted.
 *
 * This specialization adds the custom UNSAFE_already_released() member function, allowing us to
 * avoid accidentally dropping the object in this case.
 */
template <typename Dtor>
    requires requires(WGPURenderPassEncoderImpl* value) { Dtor::call(value); }
class Shared<WGPURenderPassEncoderImpl*, Dtor> final {
    WGPURenderPassEncoderImpl* _value;
    uint32_t*                  _ref_count;

  public:
    constexpr Shared() : _value{nullptr}, _ref_count{0} {}
    constexpr Shared(const std::nullptr_t) : _value{nullptr}, _ref_count{0} {}
    constexpr Shared(WGPURenderPassEncoderImpl* value) : _value{value}, _ref_count{nullptr} {
        if (_value != nullptr) {
            _ref_count = new uint32_t{1};
        }
    }
    constexpr Shared(const Shared& other) : _value{other._value}, _ref_count{other._ref_count} {
        retain();
    }
    constexpr Shared(Shared&& other) : _value{other._value}, _ref_count{other._ref_count} {
        other._value     = nullptr;
        other._ref_count = nullptr;
    }
    ~Shared() { release(); }

    Shared& operator=(const std::nullptr_t) {
        release();
        return *this;
    }

    Shared& operator=(const Shared& other) {
        release();
        _value     = other._value;
        _ref_count = other._ref_count;
        retain();
        return *this;
    }

    Shared& operator=(Shared&& other) {
        release();
        _value           = other._value;
        _ref_count       = other._ref_count;
        other._value     = nullptr;
        other._ref_count = nullptr;
        return *this;
    }

    constexpr operator WGPURenderPassEncoderImpl*() const { return _value; }

    void UNSAFE_already_released() {
#if !defined(NDEBUG)
        if (_ref_count != nullptr && *_ref_count != 1) [[unlikely]] {
            ::prism::common::log_error(
                "extra reference to RenderPassEncoder exists, leaking memory");
            std::abort();
        }
#endif
        delete _ref_count;
        _value     = nullptr;
        _ref_count = nullptr;
    }

  protected:
    void retain() {
        if (_ref_count == nullptr) [[unlikely]] {
            return;
        }
        ++(*_ref_count);
    }

    void release() {
        if (_ref_count == nullptr) [[unlikely]] {
            return;
        }

        --(*_ref_count);
        if (*_ref_count == 0) {
            Dtor::call(_value);
            delete _ref_count;
        }

        _value     = nullptr;
        _ref_count = nullptr;
    }
};

}  // namespace prism::common

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
