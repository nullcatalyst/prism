#pragma once

#include <cstdint>
#include <limits>

#include "prism/gfx/enums.hpp"
#include "webgpu-headers/webgpu.h"

namespace prism::gfx {

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
    BufferBindingType type               = BufferBindingType::Undefined;
    bool              has_dynamic_offset = false;
    uint64_t          min_binding_size   = std::numeric_limits<uint64_t>::max();
};

struct SamplerBindingLayout : public Chainable {
    SamplerBindingType type = SamplerBindingType::Undefined;
};

struct TextureBindingLayout : public Chainable {
    TextureSampleType    sample_type    = TextureSampleType::Undefined;
    TextureViewDimension view_dimension = TextureViewDimension::Undefined;
    bool                 multisampled   = false;
};

struct StorageTextureBindingLayout : public Chainable {
    StorageTextureAccess access         = StorageTextureAccess::Undefined;
    TextureFormat        format         = TextureFormat::Undefined;
    TextureViewDimension view_dimension = TextureViewDimension::Undefined;
};

struct BindGroupLayoutEntry : public Chainable {
    uint32_t                    binding    = 0;
    ShaderStage                 visibility = ShaderStage::None;
    BufferBindingLayout         buffer;
    SamplerBindingLayout        sampler;
    TextureBindingLayout        texture;
    StorageTextureBindingLayout storage_texture;
};

struct BindGroupLayoutDescriptor : public Chainable, public Labelable {
    uint32_t                    entry_count = 0;
    const BindGroupLayoutEntry* entries     = nullptr;
};

// BindGroupDescriptor

struct BindGroupEntry : public Chainable {
    uint32_t        binding      = 0;
    WGPUBuffer      buffer       = nullptr;
    uint64_t        offset       = 0;
    uint64_t        size         = 0;
    WGPUSampler     sampler      = nullptr;
    WGPUTextureView texture_view = nullptr;
};

struct BindGroupDescriptor : public Chainable, public Labelable {
    WGPUBindGroupLayout   layout      = nullptr;
    uint32_t              entry_count = 0;
    const BindGroupEntry* entries     = nullptr;
};

// PipelineLayoutDescriptor

struct PipelineLayoutDescriptor : public Chainable, public Labelable {
    uint32_t                   bind_group_layout_count = 0;
    const WGPUBindGroupLayout* bind_group_layouts      = nullptr;
};

// RenderPipelineDescriptor

struct ConstantEntry : public Chainable {
    char const* key   = nullptr;
    double      value = 0.0;
};

struct VertexAttribute {
    VertexFormat format          = VertexFormat::Undefined;
    uint64_t     offset          = 0;
    uint32_t     shader_location = 0;
};

struct VertexBufferLayout {
    uint64_t               array_stride    = 0;
    VertexStepMode         step_mode       = VertexStepMode::Vertex;
    uint32_t               attribute_count = 0;
    const VertexAttribute* attributes      = nullptr;
};

struct VertexState : public Chainable {
    WGPUShaderModule          module         = nullptr;
    const char*               entry_point    = nullptr;
    uint32_t                  constant_count = 0;
    const ConstantEntry*      constants      = nullptr;
    uint32_t                  buffer_count   = 0;
    const VertexBufferLayout* buffers        = nullptr;
};

struct PrimitiveState : public Chainable {
    PrimitiveTopology topology           = PrimitiveTopology::TriangleList;
    IndexFormat       strip_index_format = IndexFormat::Undefined;
    FrontFace         front_face         = FrontFace::CCW;
    CullMode          cull_mode          = CullMode::None;
};

struct StencilFaceState {
    CompareFunction  compare       = CompareFunction::Always;
    StencilOperation fail_op       = StencilOperation::Keep;
    StencilOperation depth_fail_op = StencilOperation::Keep;
    StencilOperation pass_op       = StencilOperation::Keep;
};

struct DepthStencilState : public Chainable {
    TextureFormat    format              = TextureFormat::Undefined;
    bool             depth_write_enabled = false;
    CompareFunction  depth_compare       = CompareFunction::Always;
    StencilFaceState stencil_front;
    StencilFaceState stencil_back;
    uint32_t         stencil_read_mask      = 0;
    uint32_t         stencil_write_mask     = 0;
    int32_t          depth_bias             = 0;
    float            depth_bias_slope_scale = 0.0f;
    float            depth_bias_clamp       = 0.0f;
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
    TextureFormat     format     = TextureFormat::Undefined;
    const BlendState* blend      = nullptr;
    ColorWriteMask    write_mask = ColorWriteMask::All;
};

struct FragmentState : public Chainable {
    WGPUShaderModule        module         = nullptr;
    const char*             entry_point    = nullptr;
    uint32_t                constant_count = 0;
    const ConstantEntry*    constants      = nullptr;
    uint32_t                target_count   = 0;
    const ColorTargetState* targets        = nullptr;
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
    WGPUQuerySet                query_set   = nullptr;
    uint32_t                    query_index = 0;
    RenderPassTimestampLocation location    = RenderPassTimestampLocation::Beginning;
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
    uint32_t vertex_count   = 0;
    uint32_t instance_count = 0;
    uint32_t first_vertex   = 0;
    uint32_t first_instance = 0;
};

struct DrawIndexedIndirectCommand {
    uint32_t index_count    = 0;
    uint32_t instance_count = 0;
    uint32_t first_index    = 0;
    int32_t  base_vertex    = 0;
    uint32_t first_instance = 0;
};

}  // namespace prism::gfx

#if !defined(NDEBUG)
#include "prism/gfx/types_validate.hpp"
#endif
