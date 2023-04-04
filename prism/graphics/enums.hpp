#pragma once

#include <cstdint>

#define PRISM_ENUM_BITFLAG($type)                                                       \
    constexpr $type operator|($type a, $type b) {                                       \
        return static_cast<$type>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b)); \
    }                                                                                   \
    constexpr $type operator&($type a, $type b) {                                       \
        return static_cast<$type>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b)); \
    }

namespace prism::graphics {

// Enum type names are sorted alphabetically for easier lookup.

enum AddressMode {
    Repeat       = 0x00000000,
    MirrorRepeat = 0x00000001,
    ClampToEdge  = 0x00000002,
};

enum class BlendFactor : uint32_t {
    Zero              = 0x00000000,
    One               = 0x00000001,
    Src               = 0x00000002,
    OneMinusSrc       = 0x00000003,
    SrcAlpha          = 0x00000004,
    OneMinusSrcAlpha  = 0x00000005,
    Dst               = 0x00000006,
    OneMinusDst       = 0x00000007,
    DstAlpha          = 0x00000008,
    OneMinusDstAlpha  = 0x00000009,
    SrcAlphaSaturated = 0x0000000A,
    Constant          = 0x0000000B,
    OneMinusConstant  = 0x0000000C,
};

enum class BlendOperation : uint32_t {
    Add             = 0x00000000,
    Subtract        = 0x00000001,
    ReverseSubtract = 0x00000002,
    Min             = 0x00000003,
    Max             = 0x00000004,
};

enum class BufferBindingType : uint32_t {
    Undefined       = 0x00000000,
    Uniform         = 0x00000001,
    Storage         = 0x00000002,
    ReadOnlyStorage = 0x00000003,
};

enum class BufferUsage : uint32_t {
    None         = 0x00000000,
    MapRead      = 0x00000001,
    MapWrite     = 0x00000002,
    CopySrc      = 0x00000004,
    CopyDst      = 0x00000008,
    Index        = 0x00000010,
    Vertex       = 0x00000020,
    Uniform      = 0x00000040,
    Storage      = 0x00000080,
    Indirect     = 0x00000100,
    QueryResolve = 0x00000200,
};
PRISM_ENUM_BITFLAG(BufferUsage)

enum class ColorWriteMask {
    None  = 0x00000000,
    Red   = 0x00000001,
    Green = 0x00000002,
    Blue  = 0x00000004,
    Alpha = 0x00000008,
    All   = 0x0000000F,
};
PRISM_ENUM_BITFLAG(ColorWriteMask)

enum class CompareFunction : uint32_t {
    Undefined    = 0x00000000,
    Never        = 0x00000001,
    Less         = 0x00000002,
    LessEqual    = 0x00000003,
    Greater      = 0x00000004,
    GreaterEqual = 0x00000005,
    Equal        = 0x00000006,
    NotEqual     = 0x00000007,
    Always       = 0x00000008,
};

enum class CullMode : uint32_t {
    None  = 0x00000000,
    Front = 0x00000001,
    Back  = 0x00000002,
};

enum class FilterMode : uint32_t {
    Nearest = 0x00000000,
    Linear  = 0x00000001,
};

enum class FrontFace : uint32_t {
    CCW = 0x00000000,
    CW  = 0x00000001,
};

enum class IndexFormat : uint32_t {
    Undefined = 0x00000000,
    Uint16    = 0x00000001,
    Uint32    = 0x00000002,
};

enum class LoadOp : uint32_t {
    Undefined = 0x00000000,
    Clear     = 0x00000001,
    Load      = 0x00000002,
};

enum class PrimitiveTopology : uint32_t {
    PointList     = 0x00000000,
    LineList      = 0x00000001,
    LineStrip     = 0x00000002,
    TriangleList  = 0x00000003,
    TriangleStrip = 0x00000004,
};

enum class RenderPassTimestampLocation : uint32_t {
    Beginning = 0x00000000,
    End       = 0x00000001,
};

enum class SamplerBindingType : uint32_t {
    Undefined    = 0x00000000,
    Filtering    = 0x00000001,
    NonFiltering = 0x00000002,
    Comparison   = 0x00000003,
};

enum class ShaderStage : uint32_t {
    None     = 0x00000000,
    Vertex   = 0x00000001,
    Fragment = 0x00000002,
    Compute  = 0x00000004,
};
PRISM_ENUM_BITFLAG(ShaderStage)

enum class StencilOperation : uint32_t {
    Keep           = 0x00000000,
    Zero           = 0x00000001,
    Replace        = 0x00000002,
    Invert         = 0x00000003,
    IncrementClamp = 0x00000004,
    DecrementClamp = 0x00000005,
    IncrementWrap  = 0x00000006,
    DecrementWrap  = 0x00000007,
};

enum class StorageTextureAccess : uint32_t {
    Undefined = 0x00000000,
    WriteOnly = 0x00000001,
};

enum StoreOp : uint32_t {
    Undefined = 0x00000000,
    Store     = 0x00000001,
    Discard   = 0x00000002,
};

enum class TextureComponentType : uint32_t {
    Float           = 0x00000000,
    Sint            = 0x00000001,
    Uint            = 0x00000002,
    DepthComparison = 0x00000003,
};

enum class TextureDimension : uint32_t {
    _1D = 0x00000000,
    _2D = 0x00000001,
    _3D = 0x00000002,
};

enum class TextureFormat : uint32_t {
    Undefined      = 0x00000000,
    R8Unorm        = 0x00000001,
    R8Snorm        = 0x00000002,
    R8Uint         = 0x00000003,
    R8Sint         = 0x00000004,
    R16Uint        = 0x00000005,
    R16Sint        = 0x00000006,
    R16Float       = 0x00000007,
    RG8Unorm       = 0x00000008,
    RG8Snorm       = 0x00000009,
    RG8Uint        = 0x0000000A,
    RG8Sint        = 0x0000000B,
    R32Float       = 0x0000000C,
    R32Uint        = 0x0000000D,
    R32Sint        = 0x0000000E,
    RG16Uint       = 0x0000000F,
    RG16Sint       = 0x00000010,
    RG16Float      = 0x00000011,
    RGBA8Unorm     = 0x00000012,
    RGBA8UnormSrgb = 0x00000013,
    RGBA8Snorm     = 0x00000014,
    RGBA8Uint      = 0x00000015,
    RGBA8Sint      = 0x00000016,
    BGRA8Unorm     = 0x00000017,
    BGRA8UnormSrgb = 0x00000018,
    // RGB10A2Unorm   = 0x00000019,
    // RG11B10Ufloat  = 0x0000001A,
    // RGB9E5Ufloat   = 0x0000001B,
    RG32Float    = 0x0000001C,
    RG32Uint     = 0x0000001D,
    RG32Sint     = 0x0000001E,
    RGBA16Uint   = 0x0000001F,
    RGBA16Sint   = 0x00000020,
    RGBA16Float  = 0x00000021,
    RGBA32Float  = 0x00000022,
    RGBA32Uint   = 0x00000023,
    RGBA32Sint   = 0x00000024,
    Depth16Unorm = 0x00000026,
    Depth32Float = 0x00000029,
};

enum class TextureSampleType : uint32_t {
    Undefined         = 0x00000000,
    Float             = 0x00000001,
    UnfilterableFloat = 0x00000002,
    Depth             = 0x00000003,
    Sint              = 0x00000004,
    Uint              = 0x00000005,
};

enum class TextureUsage : uint32_t {
    None             = 0x00000000,
    CopySrc          = 0x00000001,
    CopyDst          = 0x00000002,
    TextureBinding   = 0x00000004,
    StorageBinding   = 0x00000008,
    RenderAttachment = 0x00000010,
};
PRISM_ENUM_BITFLAG(TextureUsage)

enum class TextureViewDimension : uint32_t {
    Undefined = 0x00000000,
    _1D       = 0x00000001,
    _2D       = 0x00000002,
    _2DArray  = 0x00000003,
    Cube      = 0x00000004,
    CubeArray = 0x00000005,
    _3D       = 0x00000006,
};

enum class VertexFormat : uint32_t {
    Undefined = 0x00000000,
    Uint8x2   = 0x00000001,
    Uint8x4   = 0x00000002,
    Sint8x2   = 0x00000003,
    Sint8x4   = 0x00000004,
    Unorm8x2  = 0x00000005,
    Unorm8x4  = 0x00000006,
    Snorm8x2  = 0x00000007,
    Snorm8x4  = 0x00000008,
    Uint16x2  = 0x00000009,
    Uint16x4  = 0x0000000A,
    Sint16x2  = 0x0000000B,
    Sint16x4  = 0x0000000C,
    Unorm16x2 = 0x0000000D,
    Unorm16x4 = 0x0000000E,
    Snorm16x2 = 0x0000000F,
    Snorm16x4 = 0x00000010,
    Float16x2 = 0x00000011,
    Float16x4 = 0x00000012,
    Float32   = 0x00000013,
    Float32x2 = 0x00000014,
    Float32x3 = 0x00000015,
    Float32x4 = 0x00000016,
    Uint32    = 0x00000017,
    Uint32x2  = 0x00000018,
    Uint32x3  = 0x00000019,
    Uint32x4  = 0x0000001A,
    Sint32    = 0x0000001B,
    Sint32x2  = 0x0000001C,
    Sint32x3  = 0x0000001D,
    Sint32x4  = 0x0000001E,
};

enum class VertexStepMode : uint32_t {
    Vertex              = 0x00000000,
    Instance            = 0x00000001,
    VertexBufferNotUsed = 0x00000002,
};

}  // namespace prism::graphics

#if !defined(NDEBUG)
#include "prism/graphics/enums_validate.hpp"
#endif
