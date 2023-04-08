#pragma once

#include <cstdint>

#include "prism/graphics/enums.hpp"
#include "webgpu-headers/webgpu.h"

namespace prism::graphics {

struct ChainedStruct {
    const ChainedStruct* next   = nullptr;
    WGPUSType            s_type = WGPUSType_Invalid;
};

struct Chainable {
    const ChainedStruct* next_in_chain = nullptr;
};

struct Labelable {
    const char* label = nullptr;
};

// BindGroupLayoutDescriptor

struct BufferBindingLayout : public Chainable {
    BufferBindingType type;
    bool              has_dynamic_offset;
    uint64_t          min_binding_size;
};

struct SamplerBindingLayout : public Chainable {
    SamplerBindingType type;
};

struct TextureBindingLayout : public Chainable {
    TextureSampleType    sample_type;
    TextureViewDimension view_dimension;
    bool                 multisampled;
};

struct StorageTextureBindingLayout : public Chainable {
    StorageTextureAccess access;
    TextureFormat        format;
    TextureViewDimension view_dimension;
};

struct BindGroupLayoutEntry : public Chainable {
    uint32_t                    binding;
    ShaderStage                 visibility;
    BufferBindingLayout         buffer;
    SamplerBindingLayout        sampler;
    TextureBindingLayout        texture;
    StorageTextureBindingLayout storage_texture;
};

struct BindGroupLayoutDescriptor : public Chainable, public Labelable {
    uint32_t                    entry_count;
    const BindGroupLayoutEntry* entries;
};

// BindGroupDescriptor

struct BindGroupEntry : public Chainable {
    uint32_t        binding;
    WGPUBuffer      buffer = nullptr;
    uint64_t        offset;
    uint64_t        size;
    WGPUSampler     sampler      = nullptr;
    WGPUTextureView texture_view = nullptr;
};

struct BindGroupDescriptor : public Chainable, public Labelable {
    WGPUBindGroupLayout   layout;
    uint32_t              entry_count;
    const BindGroupEntry* entries;
};

// PipelineLayoutDescriptor

struct PipelineLayoutDescriptor : public Chainable, public Labelable {
    uint32_t                   bind_group_layout_count;
    const WGPUBindGroupLayout* bind_group_layouts;
};

// RenderPipelineDescriptor

struct ConstantEntry : public Chainable {
    char const* key;
    double      value;
};

struct VertexAttribute {
    VertexFormat format;
    uint64_t     offset;
    uint32_t     shader_location;
};

struct VertexBufferLayout {
    uint64_t               array_stride;
    VertexStepMode         step_mode;
    uint32_t               attribute_count;
    const VertexAttribute* attributes;
};

struct VertexState : public Chainable {
    WGPUShaderModule          module;
    const char*               entry_point;
    uint32_t                  constant_count = 0;
    const ConstantEntry*      constants      = nullptr;
    uint32_t                  buffer_count   = 0;
    const VertexBufferLayout* buffers        = nullptr;
};

struct PrimitiveState : public Chainable {
    PrimitiveTopology topology;
    IndexFormat       strip_index_format = IndexFormat::Undefined;
    FrontFace         front_face         = FrontFace::CCW;
    CullMode          cull_mode          = CullMode::None;
};

struct StencilFaceState {
    CompareFunction  compare;
    StencilOperation fail_op;
    StencilOperation depth_fail_op;
    StencilOperation pass_op;
};

struct DepthStencilState : public Chainable {
    TextureFormat    format;
    bool             depth_writeE_enabled;
    CompareFunction  depth_compare;
    StencilFaceState stencil_front;
    StencilFaceState stencil_back;
    uint32_t         stencil_read_mask;
    uint32_t         stencil_write_mask;
    int32_t          depth_bias;
    float            depth_bias_slope_scale;
    float            depth_bias_clamp;
};

struct MultisampleState : public Chainable {
    uint32_t count                     = 1;
    uint32_t mask                      = 0xFFFFFFFF;
    bool     alpha_to_coverage_enabled = false;
};

struct BlendComponent {
    BlendOperation operation  = BlendOperation::Add;
    BlendFactor    src_factor = BlendFactor::One;
    BlendFactor    dst_factor = BlendFactor::Zero;
};

struct BlendState {
    BlendComponent color;
    BlendComponent alpha;
};

struct ColorTargetState : public Chainable {
    TextureFormat     format;
    const BlendState* blend      = nullptr;
    ColorWriteMask    write_mask = ColorWriteMask::All;
};

struct FragmentState : public Chainable {
    WGPUShaderModule        module;
    const char*             entry_point;
    uint32_t                constant_count = 0;
    const ConstantEntry*    constants      = nullptr;
    uint32_t                target_count;
    const ColorTargetState* targets;
};

struct RenderPipelineDescriptor : public Chainable, public Labelable {
    WGPUPipelineLayout       layout = nullptr;
    VertexState              vertex;
    PrimitiveState           primitive;
    const DepthStencilState* depth_stencil = nullptr;
    MultisampleState         multisample;
    const FragmentState*     fragment = nullptr;
};

// RenderPassDescriptor

struct Color {
    double r = 0.0;
    double g = 0.0;
    double b = 0.0;
    double a = 0.0;
};

struct RenderPassColorAttachment {
    WGPUTextureView view           = nullptr;
    WGPUTextureView resolve_target = nullptr;
    LoadOp          load_op        = LoadOp::Clear;
    StoreOp         store_op       = StoreOp::Store;
    Color           clear_value;
};

struct RenderPassDepthStencilAttachment {
    WGPUTextureView view;
    LoadOp          depth_load_op       = LoadOp::Clear;
    StoreOp         depth_store_op      = StoreOp::Store;
    float           depth_clear_value   = 1.0f;
    bool            depth_read_only     = false;
    LoadOp          stencil_load_op     = LoadOp::Clear;
    StoreOp         stencil_store_op    = StoreOp::Discard;
    uint32_t        stencil_clear_value = 0;
    bool            stencil_read_only   = false;
};

struct RenderPassTimestampWrite {
    WGPUQuerySet                query_set;
    uint32_t                    query_index;
    RenderPassTimestampLocation location;
};

struct RenderPassDescriptor : public Chainable, public Labelable {
    uint32_t                                color_attachment_count   = 0;
    const RenderPassColorAttachment*        color_attachments        = nullptr;
    const RenderPassDepthStencilAttachment* depth_stencil_attachment = nullptr;
    WGPUQuerySet                            occlusion_query_set      = nullptr;
    uint32_t                                timestamp_write_count    = 0;
    const RenderPassTimestampWrite*         timestamp_writes         = nullptr;
};

// Indirect Commands (Draw, DrawIndexed)

struct DrawIndirectCommand {
    uint32_t vertex_count;
    uint32_t instance_count;
    uint32_t first_vertex;
    uint32_t first_instance;
};

struct DrawIndexedIndirectCommand {
    uint32_t index_count;
    uint32_t instance_count;
    uint32_t first_index;
    int32_t  base_vertex;
    uint32_t first_instance;
};

}  // namespace prism::graphics

#if !defined(NDEBUG)
#include "prism/graphics/types_validate.hpp"
#endif
