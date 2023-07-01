// These are the #includes that need to be included prior to this one in order for this file to
// compile without errors:

// #include <string>
// #include <type_traits>

// #include "absl/strings/str_format.h"
// #include "prism/common/debug.hpp"
// #include "prism/common/log.hpp"
// #include "webgpu-headers/webgpu.h"

namespace common {

namespace {

std::string _to_string(WGPUAdapterType value) {
    switch (value) {
        case WGPUAdapterType_DiscreteGPU:
            return "AdapterType::DiscreteGPU";
        case WGPUAdapterType_IntegratedGPU:
            return "AdapterType::IntegratedGPU";
        case WGPUAdapterType_CPU:
            return "AdapterType::CPU";
        case WGPUAdapterType_Unknown:
            return "AdapterType::Unknown";
        default:
            return absl::StrFormat(
                "AdapterType::%04x",
                static_cast<typename std::underlying_type<WGPUAdapterType>::type>(value));
    }
}

std::string _to_string(WGPUBackendType value) {
    switch (value) {
        case WGPUBackendType_Null:
            return "BackendType::Null";
        case WGPUBackendType_WebGPU:
            return "BackendType::WebGPU";
        case WGPUBackendType_D3D11:
            return "BackendType::D3D11";
        case WGPUBackendType_D3D12:
            return "BackendType::D3D12";
        case WGPUBackendType_Metal:
            return "BackendType::Metal";
        case WGPUBackendType_Vulkan:
            return "BackendType::Vulkan";
        case WGPUBackendType_OpenGL:
            return "BackendType::OpenGL";
        case WGPUBackendType_OpenGLES:
            return "BackendType::OpenGLES";
        default:
            return absl::StrFormat(
                "BackendType::%04x",
                static_cast<typename std::underlying_type<WGPUBackendType>::type>(value));
    }
}

}  // namespace

std::string adapter_info_string(WGPUAdapter adapter) {
    WGPUAdapterProperties adapter_properties = {};
    wgpuAdapterGetProperties(adapter, &adapter_properties);

    return absl::StrFormat(
        "Adapter: %s [vendor=0x%04x, device=0x%04x]\n    %s\n    %s\n    %s",
        adapter_properties.name, adapter_properties.vendorID, adapter_properties.deviceID,
        _to_string(adapter_properties.adapterType).c_str(),
        _to_string(adapter_properties.backendType).c_str(),
        adapter_properties.driverDescription != nullptr ? adapter_properties.driverDescription
                                                        : "<no description>");
}

WGPUAdapter request_adapter(WGPUInstance instance, WGPUSurface surface) {
    const WGPURequestAdapterOptions adapter_options = {
        .nextInChain       = nullptr,
        .compatibleSurface = surface,
#if defined(PRISM_PLATFORM_MACOS)
        // The high performance power preference doesn't appear to work on macos for some reason
        .powerPreference = WGPUPowerPreference_Undefined,
#else
        .powerPreference = WGPUPowerPreference_HighPerformance,
#endif
        .forceFallbackAdapter = false,
    };

    WGPUAdapter adapter = nullptr;
    wgpuInstanceRequestAdapter(
        instance, &adapter_options,
        [](WGPURequestAdapterStatus status, WGPUAdapter adapter, char const* message,
           void* user_data) {
            WGPUAdapter* returned_adapter = reinterpret_cast<WGPUAdapter*>(user_data);

            if (status == WGPURequestAdapterStatus_Success) {
                // Print the adaptor's properties, useful for debugging
                ::prism::common::log_message(common::adapter_info_string(adapter));

                *returned_adapter = adapter;
                return;
            }

            ::prism::common::log_fatal("Request adapter failed: ", message);
        },
        &adapter);
    PRISM_DEBUG_RESULT(adapter);
    return adapter;
}

WGPUDevice create_device(WGPUAdapter adapter) {
    // const WGPURequiredLimits limits = {
    //     .nextInChain = nullptr,
    //     .limits =
    //         {
    //             .minUniformBufferOffsetAlignment = 256,
    //             .minStorageBufferOffsetAlignment = 256,
    //         },
    // };

    const WGPUFeatureName required_features[] = {
#if defined(PRISM_BACKEND_WGPU)
        static_cast<WGPUFeatureName>(0x60000003),  // WGPUNativeFeature_MULTI_DRAW_INDIRECT,
#endif
    };

    const WGPUDeviceDescriptor device_desc{
        .nextInChain           = nullptr,
        .label                 = nullptr,
        .requiredFeaturesCount = std::size(required_features),
        .requiredFeatures      = required_features,
        .requiredLimits        = nullptr,  //&limits,
        .defaultQueue =
            {
                .nextInChain = nullptr,
                .label       = nullptr,
            },
    };
    WGPUDevice device = nullptr;
    wgpuAdapterRequestDevice(
        adapter, &device_desc,
        [](WGPURequestDeviceStatus status, WGPUDevice device, char const* message,
           void* user_data) {
            WGPUDevice* returned_device = reinterpret_cast<WGPUDevice*>(user_data);

            if (status == WGPURequestDeviceStatus_Success) {
                *returned_device = device;
                return;
            }

            ::prism::common::log_fatal("Request device failed: ", message);
        },
        &device);
    PRISM_DEBUG_RESULT(device);
    return device;
}

WGPUSwapChain create_swap_chain(WGPUDevice device, WGPUSurface surface, WGPUAdapter adapter,
                                const uint32_t width, const uint32_t height) {
    PRISM_DEBUG_RESULT(surface);
    PRISM_DEBUG_RESULT(adapter);
    PRISM_DEBUG_SCOPE_START(device);
    const WGPUSwapChainDescriptor desc{
        .nextInChain = nullptr,
        .label       = nullptr,
        .usage       = WGPUTextureUsage_RenderAttachment,
        .format      = wgpuSurfaceGetPreferredFormat(surface, adapter),
        .width       = width,
        .height      = height,
        // .presentMode = WGPUPresentMode_Fifo,
        .presentMode = WGPUPresentMode_Mailbox,
    };

    const WGPUSwapChain swap_chain = wgpuDeviceCreateSwapChain(device, surface, &desc);
    PRISM_DEBUG_SCOPE_END(device, "creating swap chain");
    PRISM_DEBUG_RESULT(swap_chain);
    return swap_chain;
}

WGPUQueue get_queue(WGPUDevice device) {
    PRISM_DEBUG_SCOPE_START(device);
    const WGPUQueue queue = wgpuDeviceGetQueue(device);
    PRISM_DEBUG_SCOPE_END(device, "getting device queue");
    PRISM_DEBUG_RESULT(queue);
    return queue;
}

////////////////////////////////
// Initialization functions

WGPUBindGroupLayout create_bind_group_layout(WGPUDevice                           device,
                                             const WGPUBindGroupLayoutDescriptor& layout_desc) {
    PRISM_DEBUG_SCOPE_START(device);
    const WGPUBindGroupLayout layout = wgpuDeviceCreateBindGroupLayout(device, &layout_desc);
    PRISM_DEBUG_SCOPE_END(device, "creating bind group layout");
    PRISM_DEBUG_RESULT(layout);
    return layout;
}

WGPUShaderModule create_shader_module(WGPUDevice device, const char* source) {
    const WGPUShaderModuleWGSLDescriptor wgsl_desc{
        .chain =
            WGPUChainedStruct{
                .next  = nullptr,
                .sType = WGPUSType_ShaderModuleWGSLDescriptor,
            },
        .code = source,
    };
    const WGPUShaderModuleDescriptor shader_desc {
        // clang-format off
        // For some reason clang-format is not happy with the following lines
        .nextInChain = &wgsl_desc.chain,
        .label = nullptr,
#if defined(PRISM_BACKEND_WGPU)
        .hintCount = 0,
        .hints = nullptr,
#endif  // defined(PRISM_BACKEND_WGPU)
        // clang-format on
    };

    PRISM_DEBUG_SCOPE_START(device);
    const WGPUShaderModule shader = wgpuDeviceCreateShaderModule(device, &shader_desc);
    PRISM_DEBUG_SCOPE_END(device, "creating shader module");
    PRISM_DEBUG_RESULT(shader);
    return shader;
}

WGPUPipelineLayout create_pipeline_layout(WGPUDevice                          device,
                                          const WGPUPipelineLayoutDescriptor& layout_desc) {
    PRISM_DEBUG_SCOPE_START(device);
    const WGPUPipelineLayout layout = wgpuDeviceCreatePipelineLayout(device, &layout_desc);
    PRISM_DEBUG_SCOPE_END(device, "creating pipeline layout");
    PRISM_DEBUG_RESULT(layout);
    return layout;
}

WGPURenderPipeline create_render_pipeline(WGPUDevice                          device,
                                          const WGPURenderPipelineDescriptor& pipeline_desc) {
    PRISM_DEBUG_SCOPE_START(device);
    const WGPURenderPipeline pipeline = wgpuDeviceCreateRenderPipeline(device, &pipeline_desc);
    PRISM_DEBUG_SCOPE_END(device, "creating render pipline");
    PRISM_DEBUG_RESULT(pipeline);
    return pipeline;
}

WGPUComputePipeline create_compute_pipeline(WGPUDevice                           device,
                                            const WGPUComputePipelineDescriptor& pipeline_desc) {
    PRISM_DEBUG_SCOPE_START(device);
    const WGPUComputePipeline pipeline = wgpuDeviceCreateComputePipeline(device, &pipeline_desc);
    PRISM_DEBUG_SCOPE_END(device, "creating compute pipline");
    PRISM_DEBUG_RESULT(pipeline);
    return pipeline;
}

WGPUBindGroup create_bind_group(WGPUDevice device, const WGPUBindGroupDescriptor& bind_group_desc) {
    PRISM_DEBUG_SCOPE_START(device);
    const WGPUBindGroup bind_group = wgpuDeviceCreateBindGroup(device, &bind_group_desc);
    PRISM_DEBUG_SCOPE_END(device, "creating bind group");
    PRISM_DEBUG_RESULT(bind_group);
    return bind_group;
}

WGPUBuffer create_buffer(WGPUDevice device, const WGPUBufferUsageFlags usage,
                         const uint64_t buffer_size, const void* data, const uint64_t data_size,
                         const uint64_t data_offset_into_buffer) {
    const auto                 mapped = data != nullptr && data_size > 0;
    const WGPUBufferDescriptor desc{
        .nextInChain      = nullptr,
        .label            = nullptr,
        .usage            = usage,
        .size             = buffer_size,
        .mappedAtCreation = mapped,
    };

    PRISM_DEBUG_SCOPE_START(device);
    const WGPUBuffer buffer = wgpuDeviceCreateBuffer(device, &desc);

    if (mapped) {
        void* write_ptr = wgpuBufferGetMappedRange(buffer, data_offset_into_buffer, data_size);
        memcpy(write_ptr, data, data_size);
        wgpuBufferUnmap(buffer);
    }

    PRISM_DEBUG_SCOPE_END(device, "creating buffer");
    PRISM_DEBUG_RESULT(buffer);
    return buffer;
}

void update_buffer(WGPUDevice device, WGPUQueue queue, WGPUBuffer buffer, const void* data,
                   const uint64_t data_size, const uint64_t data_offset_into_buffer) {
    PRISM_DEBUG_RESULT(queue);
    PRISM_DEBUG_SCOPE_START(device);
    wgpuQueueWriteBuffer(queue, buffer, data_offset_into_buffer, data, data_size);
    PRISM_DEBUG_SCOPE_END(device, "updating buffer");
}

WGPUTexture create_texture_2d(WGPUDevice device, const WGPUTextureUsageFlags usage,
                              const WGPUTextureFormat format, const uint32_t width,
                              const uint32_t height) {
    const WGPUTextureDescriptor texture_desc{
        .nextInChain     = nullptr,
        .label           = nullptr,
        .usage           = usage,
        .dimension       = WGPUTextureDimension_2D,
        .size            = WGPUExtent3D{width, height, 1},
        .format          = format,
        .mipLevelCount   = 1,
        .sampleCount     = 1,
        .viewFormatCount = 0,
        .viewFormats     = nullptr,
    };
    PRISM_DEBUG_SCOPE_START(device);
    const WGPUTexture texture = wgpuDeviceCreateTexture(device, &texture_desc);
    PRISM_DEBUG_SCOPE_END(device, "creating 2D texture");
    PRISM_DEBUG_RESULT(texture);
    return texture;
}

void update_texture_2d(WGPUDevice device, WGPUQueue queue, WGPUTexture texture,
                       const uint32_t width, const uint32_t height, const void* data,
                       const uint64_t data_size) {
    const WGPUImageCopyTexture image_copy_desc{
        .nextInChain = nullptr,
        .texture     = texture,
        .mipLevel    = 0,
        .origin      = WGPUOrigin3D{0, 0, 0},
        .aspect      = WGPUTextureAspect_All,
    };
    const WGPUTextureDataLayout data_layout_desc{
        .nextInChain  = nullptr,
        .offset       = 0,
        .bytesPerRow  = static_cast<uint32_t>(data_size / height),
        .rowsPerImage = height,
    };
    const WGPUExtent3D write_size_desc{width, height, 1};

    PRISM_DEBUG_RESULT(queue);
    PRISM_DEBUG_SCOPE_START(device);
    wgpuQueueWriteTexture(queue, &image_copy_desc, data, data_size, &data_layout_desc,
                          &write_size_desc);
    PRISM_DEBUG_SCOPE_END(device, "updating 2D texture");
}

WGPUTextureView create_texture_view_2d(WGPUDevice device, WGPUTexture texture,
                                       const WGPUTextureFormat format) {
    const WGPUTextureViewDescriptor view_desc{
        .nextInChain     = nullptr,
        .label           = nullptr,
        .format          = format,
        .dimension       = WGPUTextureViewDimension_2D,
        .baseMipLevel    = 0,
        .mipLevelCount   = 1,
        .baseArrayLayer  = 0,
        .arrayLayerCount = 1,
        .aspect          = WGPUTextureAspect_All,
    };
    PRISM_DEBUG_SCOPE_START(device);
    WGPUTextureView texture_view = wgpuTextureCreateView(texture, &view_desc);
    PRISM_DEBUG_SCOPE_END(device, "creating 2D texture view");
    PRISM_DEBUG_RESULT(texture_view);
    return texture_view;
}

WGPUSampler create_sampler(WGPUDevice device, const WGPUAddressMode address_mode,
                           const WGPUFilterMode min_filter, const WGPUFilterMode mag_filter,
                           const WGPUFilterMode mipmap_filter) {
    const WGPUSamplerDescriptor desc{
        .nextInChain   = nullptr,
        .label         = nullptr,
        .addressModeU  = address_mode,
        .addressModeV  = address_mode,
        .addressModeW  = address_mode,
        .magFilter     = mag_filter,
        .minFilter     = min_filter,
        .mipmapFilter  = static_cast<WGPUMipmapFilterMode>(mipmap_filter),
        .lodMinClamp   = 0.0f,
        .lodMaxClamp   = 0.0f,
        .compare       = WGPUCompareFunction_Undefined,
        .maxAnisotropy = 0,
    };
    PRISM_DEBUG_SCOPE_START(device);
    const WGPUSampler sampler = wgpuDeviceCreateSampler(device, &desc);
    PRISM_DEBUG_SCOPE_END(device, "creating sampler");
    PRISM_DEBUG_RESULT(sampler);
    return sampler;
}

WGPUSampler create_sampler_comparison(WGPUDevice device, const WGPUAddressMode address_mode,
                                      const WGPUFilterMode      min_filter,
                                      const WGPUFilterMode      mag_filter,
                                      const WGPUFilterMode      mipmap_filter,
                                      const WGPUCompareFunction compare) {
    const WGPUSamplerDescriptor desc{
        .nextInChain   = nullptr,
        .label         = nullptr,
        .addressModeU  = address_mode,
        .addressModeV  = address_mode,
        .addressModeW  = address_mode,
        .magFilter     = mag_filter,
        .minFilter     = min_filter,
        .mipmapFilter  = static_cast<WGPUMipmapFilterMode>(mipmap_filter),
        .lodMinClamp   = 0.0f,
        .lodMaxClamp   = 0.0f,
        .compare       = compare,
        .maxAnisotropy = 0,
    };
    PRISM_DEBUG_SCOPE_START(device);
    const WGPUSampler sampler = wgpuDeviceCreateSampler(device, &desc);
    PRISM_DEBUG_SCOPE_END(device, "creating sampler comparison");
    PRISM_DEBUG_RESULT(sampler);
    return sampler;
}

////////////////////////////////
// Command functions

WGPUCommandEncoder start_frame(WGPUDevice device) {
    const WGPUCommandEncoderDescriptor desc{
        .nextInChain = nullptr,
        .label       = nullptr,
    };
    PRISM_DEBUG_RESULT(device);
    const WGPUCommandEncoder encoder = wgpuDeviceCreateCommandEncoder(device, &desc);
    PRISM_DEBUG_RESULT(encoder);
    return encoder;
}

void present_frame(WGPUDevice device, WGPUSwapChain swap_chain, WGPUCommandEncoder encoder,
                   WGPUQueue queue) {
    const WGPUCommandBufferDescriptor desc{
        .nextInChain = nullptr,
        .label       = nullptr,
    };

    PRISM_DEBUG_RESULT(swap_chain);
    PRISM_DEBUG_RESULT(encoder);
    const WGPUCommandBuffer command_buffer = wgpuCommandEncoderFinish(encoder, &desc);
    wgpuQueueSubmit(queue, 1, &command_buffer);
    wgpuSwapChainPresent(swap_chain);
    // _encoder._already_released();
}

WGPUTextureView swap_chain_view(WGPUDevice device, WGPUSwapChain swap_chain) {
    PRISM_DEBUG_RESULT(swap_chain);
    PRISM_DEBUG_SCOPE_START(device);
    const WGPUTextureView texture_view = wgpuSwapChainGetCurrentTextureView(swap_chain);
    PRISM_DEBUG_SCOPE_END(device, "fetching swap chain view");
    PRISM_DEBUG_RESULT(texture_view);
    return texture_view;
}

WGPURenderBundleEncoder begin_render_bundle(
    WGPUDevice device, const WGPURenderBundleEncoderDescriptor& render_bundle_encoder_desc) {
    PRISM_DEBUG_SCOPE_START(device);
    const WGPURenderBundleEncoder render_bundle_encoder =
        wgpuDeviceCreateRenderBundleEncoder(device, &render_bundle_encoder_desc);
    PRISM_DEBUG_RESULT(render_bundle_encoder);
    PRISM_DEBUG_SCOPE_END(device, "starting render bundle");
    return render_bundle_encoder;
}

WGPURenderBundle end_render_bundle(WGPUDevice              device,
                                   WGPURenderBundleEncoder render_bundle_encoder) {
    PRISM_DEBUG_SCOPE_START(device);
    const WGPURenderBundleDescriptor render_bundle_desc{
        .nextInChain = nullptr,
        .label       = nullptr,
    };
    const WGPURenderBundle render_bundle =
        wgpuRenderBundleEncoderFinish(render_bundle_encoder, &render_bundle_desc);
    PRISM_DEBUG_RESULT(render_bundle);
    PRISM_DEBUG_SCOPE_END(device, "ending render bundle");
    return render_bundle;
}

void set_pipeline(WGPUDevice device, WGPURenderBundleEncoder render_bundle_encoder,
                  WGPURenderPipeline pipeline) {
    PRISM_DEBUG_SCOPE_START(device);
    wgpuRenderBundleEncoderSetPipeline(render_bundle_encoder, pipeline);
    PRISM_DEBUG_SCOPE_END(device, "setting pipeline");
}

void set_bind_group(WGPUDevice device, WGPURenderBundleEncoder render_bundle_encoder,
                    const uint32_t slot, WGPUBindGroup bind_group) {
    PRISM_DEBUG_SCOPE_START(device);
    wgpuRenderBundleEncoderSetBindGroup(render_bundle_encoder, slot, bind_group, 0, nullptr);
    PRISM_DEBUG_SCOPE_END(device, "setting bind group");
}

void set_buffer(WGPUDevice device, WGPURenderBundleEncoder render_bundle_encoder,
                const uint32_t slot, WGPUBuffer buffer, const uint64_t offset,
                const uint64_t size) {
    PRISM_DEBUG_SCOPE_START(device);
    wgpuRenderBundleEncoderSetVertexBuffer(render_bundle_encoder, slot, buffer, offset, size);
    PRISM_DEBUG_SCOPE_END(device, "setting buffer");
}

void set_index_u16_buffer(WGPUDevice device, WGPURenderBundleEncoder render_bundle_encoder,
                          WGPUBuffer buffer, const uint64_t offset, const uint64_t size) {
    PRISM_DEBUG_SCOPE_START(device);
    wgpuRenderBundleEncoderSetIndexBuffer(render_bundle_encoder, buffer, WGPUIndexFormat_Uint16,
                                          offset, size);
    PRISM_DEBUG_SCOPE_END(device, "setting index buffer");
}

void set_index_u32_buffer(WGPUDevice device, WGPURenderBundleEncoder render_bundle_encoder,
                          WGPUBuffer buffer, const uint64_t offset, const uint64_t size) {
    PRISM_DEBUG_SCOPE_START(device);
    wgpuRenderBundleEncoderSetIndexBuffer(render_bundle_encoder, buffer, WGPUIndexFormat_Uint32,
                                          offset, size);
    PRISM_DEBUG_SCOPE_END(device, "setting index buffer");
}

void draw(WGPUDevice device, WGPURenderBundleEncoder render_bundle_encoder,
          const uint32_t vertex_count, const uint32_t instance_count, const uint32_t first_vertex,
          const uint32_t first_instance) {
    PRISM_DEBUG_SCOPE_START(device);
    wgpuRenderBundleEncoderDraw(render_bundle_encoder, vertex_count, instance_count, first_vertex,
                                first_instance);
    PRISM_DEBUG_SCOPE_END(device, "drawing");
}

void draw_indexed(WGPUDevice device, WGPURenderBundleEncoder render_bundle_encoder,
                  const uint32_t index_count, const uint32_t instance_count,
                  const uint32_t first_index, const int32_t base_vertex,
                  const uint32_t first_instance) {
    PRISM_DEBUG_SCOPE_START(device);
    wgpuRenderBundleEncoderDrawIndexed(render_bundle_encoder, index_count, instance_count,
                                       first_index, base_vertex, first_instance);
    PRISM_DEBUG_SCOPE_END(device, "drawing indexed");
}

void draw_indirect(WGPUDevice device, WGPURenderBundleEncoder render_bundle_encoder,
                   WGPUBuffer indirect_buffer, const uint64_t indirect_offset) {
    PRISM_DEBUG_SCOPE_START(device);
    wgpuRenderBundleEncoderDrawIndirect(render_bundle_encoder, indirect_buffer, indirect_offset);
    PRISM_DEBUG_SCOPE_END(device, "drawing indirect");
}

void draw_indexed_indirect(WGPUDevice device, WGPURenderBundleEncoder render_bundle_encoder,
                           WGPUBuffer indirect_buffer, const uint64_t indirect_offset) {
    PRISM_DEBUG_SCOPE_START(device);
    wgpuRenderBundleEncoderDrawIndexedIndirect(render_bundle_encoder, indirect_buffer,
                                               indirect_offset);
    PRISM_DEBUG_SCOPE_END(device, "drawing indexed indirect");
}

WGPURenderPassEncoder begin_render_pass(WGPUDevice device, WGPUCommandEncoder encoder,
                                        const WGPURenderPassDescriptor& render_pass_desc,
                                        const uint32_t width, const uint32_t height) {
    PRISM_DEBUG_SCOPE_START(device);
    const WGPURenderPassEncoder render_pass =
        wgpuCommandEncoderBeginRenderPass(encoder, &render_pass_desc);
    PRISM_DEBUG_RESULT(render_pass);
    wgpuRenderPassEncoderSetViewport(render_pass, 0.0f, 0.0f, static_cast<float>(width),
                                     static_cast<float>(height), 0.0f, 1.0f);
    wgpuRenderPassEncoderSetScissorRect(render_pass, 0, 0, width, height);
    PRISM_DEBUG_SCOPE_END(device, "starting render pass");
    return render_pass;
}

void end_render_pass(WGPUDevice device, WGPURenderPassEncoder render_pass) {
    PRISM_DEBUG_SCOPE_START(device);
    wgpuRenderPassEncoderEnd(render_pass);
    PRISM_DEBUG_SCOPE_END(device, "ending render pass");
}

void execute_render_bundle(WGPUDevice device, WGPURenderPassEncoder render_pass,
                           WGPURenderBundle render_bundle) {
    PRISM_DEBUG_SCOPE_START(device);
    wgpuRenderPassEncoderExecuteBundles(render_pass, 1, &render_bundle);
    PRISM_DEBUG_SCOPE_END(device, "executing render bundle");
}

void set_pipeline(WGPUDevice device, WGPURenderPassEncoder render_pass,
                  WGPURenderPipeline pipeline) {
    PRISM_DEBUG_SCOPE_START(device);
    wgpuRenderPassEncoderSetPipeline(render_pass, pipeline);
    PRISM_DEBUG_SCOPE_END(device, "setting pipeline");
}

void set_bind_group(WGPUDevice device, WGPURenderPassEncoder render_pass, const uint32_t slot,
                    WGPUBindGroup bind_group) {
    PRISM_DEBUG_SCOPE_START(device);
    wgpuRenderPassEncoderSetBindGroup(render_pass, slot, bind_group, 0, nullptr);
    PRISM_DEBUG_SCOPE_END(device, "setting bind group");
}

void set_buffer(WGPUDevice device, WGPURenderPassEncoder render_pass, const uint32_t slot,
                WGPUBuffer buffer, const uint64_t offset, const uint64_t size) {
    PRISM_DEBUG_SCOPE_START(device);
    wgpuRenderPassEncoderSetVertexBuffer(render_pass, slot, buffer, offset, size);
    PRISM_DEBUG_SCOPE_END(device, "setting buffer");
}

void set_index_u16_buffer(WGPUDevice device, WGPURenderPassEncoder render_pass, WGPUBuffer buffer,
                          const uint64_t offset, const uint64_t size) {
    PRISM_DEBUG_SCOPE_START(device);
    wgpuRenderPassEncoderSetIndexBuffer(render_pass, buffer, WGPUIndexFormat_Uint16, offset, size);
    PRISM_DEBUG_SCOPE_END(device, "setting index buffer");
}

void set_index_u32_buffer(WGPUDevice device, WGPURenderPassEncoder render_pass, WGPUBuffer buffer,
                          const uint64_t offset, const uint64_t size) {
    PRISM_DEBUG_SCOPE_START(device);
    wgpuRenderPassEncoderSetIndexBuffer(render_pass, buffer, WGPUIndexFormat_Uint32, offset, size);
    PRISM_DEBUG_SCOPE_END(device, "setting index buffer");
}

void draw(WGPUDevice device, WGPURenderPassEncoder render_pass, const uint32_t vertex_count,
          const uint32_t instance_count, const uint32_t first_vertex,
          const uint32_t first_instance) {
    PRISM_DEBUG_SCOPE_START(device);
    wgpuRenderPassEncoderDraw(render_pass, vertex_count, instance_count, first_vertex,
                              first_instance);
    PRISM_DEBUG_SCOPE_END(device, "drawing");
}

void draw_indexed(WGPUDevice device, WGPURenderPassEncoder render_pass, const uint32_t index_count,
                  const uint32_t instance_count, const uint32_t first_index,
                  const int32_t base_vertex, const uint32_t first_instance) {
    PRISM_DEBUG_SCOPE_START(device);
    wgpuRenderPassEncoderDrawIndexed(render_pass, index_count, instance_count, first_index,
                                     base_vertex, first_instance);
    PRISM_DEBUG_SCOPE_END(device, "drawing indexed");
}

void draw_indirect(WGPUDevice device, WGPURenderPassEncoder render_pass, WGPUBuffer indirect_buffer,
                   const uint64_t indirect_offset) {
    PRISM_DEBUG_SCOPE_START(device);
    wgpuRenderPassEncoderDrawIndirect(render_pass, indirect_buffer, indirect_offset);
    PRISM_DEBUG_SCOPE_END(device, "drawing indirect");
}

void draw_indexed_indirect(WGPUDevice device, WGPURenderPassEncoder render_pass,
                           WGPUBuffer indirect_buffer, const uint64_t indirect_offset) {
    PRISM_DEBUG_SCOPE_START(device);
    wgpuRenderPassEncoderDrawIndexedIndirect(render_pass, indirect_buffer, indirect_offset);
    PRISM_DEBUG_SCOPE_END(device, "drawing indexed indirect");
}

void draw_multi_indirect(WGPUDevice device, WGPURenderPassEncoder render_pass,
                         WGPUBuffer indirect_buffer, const uint64_t indirect_offset,
                         const uint32_t indirect_count) {
    struct WGPUDrawIndirectCommand {
        uint32_t vertexCount;
        uint32_t instanceCount;
        uint32_t firstVertex;
        uint32_t firstInstance;
    };

    PRISM_DEBUG_SCOPE_START(device);
    // MultiDrawIndirect is not yet generally available across all WebGPU implementations.
    // https://github.com/gpuweb/gpuweb/issues/1354
    // But it is a trivial polyfill using a loop.
    // wgpuRenderPassEncoderMultiDrawIndirect(render_pass, indirect_buffer, indirect_offset,
    // indirect_count);
    for (uint32_t i = 0; i < indirect_count; ++i) {
        wgpuRenderPassEncoderDrawIndirect(render_pass, indirect_buffer,
                                          indirect_offset + i * sizeof(WGPUDrawIndirectCommand));
    }
    PRISM_DEBUG_SCOPE_END(device, "multi drawing indirect");
}

void draw_multi_indexed_indirect(WGPUDevice device, WGPURenderPassEncoder render_pass,
                                 WGPUBuffer indirect_buffer, const uint64_t indirect_offset,
                                 const uint32_t indirect_count) {
    struct WGPUDrawIndexedIndirectCommand {
        uint32_t indexCount;
        uint32_t instanceCount;
        uint32_t firstIndex;
        int32_t  vertexOffset;
        uint32_t firstInstance;
    };

    PRISM_DEBUG_SCOPE_START(device);
    // MultiDrawIndexedIndirect is not yet generally available across all WebGPU implementations.
    // https://github.com/gpuweb/gpuweb/issues/1354
    // But it is a trivial polyfill using a loop.
    // wgpuRenderPassEncoderMultiDrawIndexedIndirect(render_pass, indirect_buffer, indirect_offset,
    // indirect_count);
    for (uint32_t i = 0; i < indirect_count; ++i) {
        wgpuRenderPassEncoderDrawIndexedIndirect(
            render_pass, indirect_buffer,
            indirect_offset + i * sizeof(WGPUDrawIndexedIndirectCommand));
    }
    PRISM_DEBUG_SCOPE_END(device, "multi drawing indexed indirect");
}

}  // namespace common
