#pragma once

#include "webgpu-headers/webgpu.h"

// This header exists entirely to validate that the enums in the prism::gfx namespace match the
// enums in by the WGPU C headers. Duplicating the enums into C++ allows us to introduce type safety
// through the use of enum classes.

#define ASSERT_ENUM_EQ($type, $value) \
    static_assert(static_cast<uint32_t>(prism::gfx::$type::$value) == WGPU##$type##_##$value)

#define ASSERT_RENAMED_ENUM_EQ($type, $value, $wgpu_value) \
    static_assert(static_cast<uint32_t>(prism::gfx::$type::$value) == $wgpu_value)

ASSERT_ENUM_EQ(BlendFactor, Zero);
ASSERT_ENUM_EQ(BlendFactor, One);
ASSERT_ENUM_EQ(BlendFactor, Src);
ASSERT_ENUM_EQ(BlendFactor, OneMinusSrc);
ASSERT_ENUM_EQ(BlendFactor, SrcAlpha);
ASSERT_ENUM_EQ(BlendFactor, OneMinusSrcAlpha);
ASSERT_ENUM_EQ(BlendFactor, Dst);
ASSERT_ENUM_EQ(BlendFactor, OneMinusDst);
ASSERT_ENUM_EQ(BlendFactor, DstAlpha);
ASSERT_ENUM_EQ(BlendFactor, OneMinusDstAlpha);
ASSERT_ENUM_EQ(BlendFactor, SrcAlphaSaturated);
ASSERT_ENUM_EQ(BlendFactor, Constant);
ASSERT_ENUM_EQ(BlendFactor, OneMinusConstant);

ASSERT_ENUM_EQ(BlendOperation, Add);
ASSERT_ENUM_EQ(BlendOperation, Subtract);
ASSERT_ENUM_EQ(BlendOperation, ReverseSubtract);
ASSERT_ENUM_EQ(BlendOperation, Min);
ASSERT_ENUM_EQ(BlendOperation, Max);

ASSERT_ENUM_EQ(BufferBindingType, Undefined);
ASSERT_ENUM_EQ(BufferBindingType, Uniform);
ASSERT_ENUM_EQ(BufferBindingType, Storage);
ASSERT_ENUM_EQ(BufferBindingType, ReadOnlyStorage);

ASSERT_ENUM_EQ(CullMode, None);
ASSERT_ENUM_EQ(CullMode, Front);
ASSERT_ENUM_EQ(CullMode, Back);

ASSERT_ENUM_EQ(FilterMode, Nearest);
ASSERT_ENUM_EQ(FilterMode, Linear);

ASSERT_ENUM_EQ(FrontFace, CCW);
ASSERT_ENUM_EQ(FrontFace, CW);

ASSERT_ENUM_EQ(IndexFormat, Undefined);
ASSERT_ENUM_EQ(IndexFormat, Uint16);
ASSERT_ENUM_EQ(IndexFormat, Uint32);

ASSERT_ENUM_EQ(LoadOp, Undefined);
ASSERT_ENUM_EQ(LoadOp, Clear);
ASSERT_ENUM_EQ(LoadOp, Load);

ASSERT_ENUM_EQ(PrimitiveTopology, PointList);
ASSERT_ENUM_EQ(PrimitiveTopology, LineList);
ASSERT_ENUM_EQ(PrimitiveTopology, LineStrip);
ASSERT_ENUM_EQ(PrimitiveTopology, TriangleList);
ASSERT_ENUM_EQ(PrimitiveTopology, TriangleStrip);

ASSERT_ENUM_EQ(SamplerBindingType, Undefined);
ASSERT_ENUM_EQ(SamplerBindingType, Filtering);
ASSERT_ENUM_EQ(SamplerBindingType, NonFiltering);
ASSERT_ENUM_EQ(SamplerBindingType, Comparison);

ASSERT_ENUM_EQ(StoreOp, Undefined);
ASSERT_ENUM_EQ(StoreOp, Store);
ASSERT_ENUM_EQ(StoreOp, Discard);

ASSERT_ENUM_EQ(TextureComponentType, Float);
ASSERT_ENUM_EQ(TextureComponentType, Sint);
ASSERT_ENUM_EQ(TextureComponentType, Uint);
ASSERT_ENUM_EQ(TextureComponentType, DepthComparison);

ASSERT_RENAMED_ENUM_EQ(TextureDimension, _1D, WGPUTextureDimension_1D);
ASSERT_RENAMED_ENUM_EQ(TextureDimension, _2D, WGPUTextureDimension_2D);
ASSERT_RENAMED_ENUM_EQ(TextureDimension, _3D, WGPUTextureDimension_3D);

ASSERT_ENUM_EQ(TextureFormat, Undefined);
ASSERT_ENUM_EQ(TextureFormat, R8Unorm);
ASSERT_ENUM_EQ(TextureFormat, R8Snorm);
ASSERT_ENUM_EQ(TextureFormat, R8Uint);
ASSERT_ENUM_EQ(TextureFormat, R8Sint);
ASSERT_ENUM_EQ(TextureFormat, R16Uint);
ASSERT_ENUM_EQ(TextureFormat, R16Sint);
ASSERT_ENUM_EQ(TextureFormat, R16Float);
ASSERT_ENUM_EQ(TextureFormat, RG8Unorm);
ASSERT_ENUM_EQ(TextureFormat, RG8Snorm);
ASSERT_ENUM_EQ(TextureFormat, RG8Uint);
ASSERT_ENUM_EQ(TextureFormat, RG8Sint);
ASSERT_ENUM_EQ(TextureFormat, R32Float);
ASSERT_ENUM_EQ(TextureFormat, R32Uint);
ASSERT_ENUM_EQ(TextureFormat, R32Sint);
ASSERT_ENUM_EQ(TextureFormat, RG16Uint);
ASSERT_ENUM_EQ(TextureFormat, RG16Sint);
ASSERT_ENUM_EQ(TextureFormat, RG16Float);
ASSERT_ENUM_EQ(TextureFormat, RGBA8Unorm);
ASSERT_ENUM_EQ(TextureFormat, RGBA8UnormSrgb);
ASSERT_ENUM_EQ(TextureFormat, RGBA8Snorm);
ASSERT_ENUM_EQ(TextureFormat, RGBA8Uint);
ASSERT_ENUM_EQ(TextureFormat, RGBA8Sint);
ASSERT_ENUM_EQ(TextureFormat, BGRA8Unorm);
ASSERT_ENUM_EQ(TextureFormat, BGRA8UnormSrgb);
// ASSERT_ENUM_EQ(TextureFormat, RGB10A2Unorm);
// ASSERT_ENUM_EQ(TextureFormat, RG11B10Ufloat);
// ASSERT_ENUM_EQ(TextureFormat, RGB9E5Ufloat);
ASSERT_ENUM_EQ(TextureFormat, RG32Float);
ASSERT_ENUM_EQ(TextureFormat, RG32Uint);
ASSERT_ENUM_EQ(TextureFormat, RG32Sint);
ASSERT_ENUM_EQ(TextureFormat, RGBA16Uint);
ASSERT_ENUM_EQ(TextureFormat, RGBA16Sint);
ASSERT_ENUM_EQ(TextureFormat, RGBA16Float);
ASSERT_ENUM_EQ(TextureFormat, RGBA32Float);
ASSERT_ENUM_EQ(TextureFormat, RGBA32Uint);
ASSERT_ENUM_EQ(TextureFormat, RGBA32Sint);
ASSERT_ENUM_EQ(TextureFormat, Depth16Unorm);
ASSERT_ENUM_EQ(TextureFormat, Depth32Float);

ASSERT_ENUM_EQ(TextureSampleType, Undefined);
ASSERT_ENUM_EQ(TextureSampleType, Float);
ASSERT_ENUM_EQ(TextureSampleType, UnfilterableFloat);
ASSERT_ENUM_EQ(TextureSampleType, Depth);
ASSERT_ENUM_EQ(TextureSampleType, Sint);
ASSERT_ENUM_EQ(TextureSampleType, Uint);

#undef ASSERT_RENAMED_ENUM_EQ
#undef ASSERT_ENUM_EQ
