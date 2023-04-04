#pragma once

#include "webgpu-headers/webgpu.h"

// This header exists entirely to validate that the enums in the prism::graphics namespace match the
// enums in by the WGPU C headers. Duplicating the enums into C++ allows us to introduce type safety
// through the use of enum classes.

#define ASSERT_ENUM_EQ($type, $value) \
    static_assert(static_cast<uint32_t>(prism::graphics::$type::$value) == WGPU##$type##_##$value)

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

// static_assert(prism::graphics::common::SamplerBindingType::Undefined ==
//               WGPUSamplerBindingType_Undefined);
// static_assert(prism::graphics::common::SamplerBindingType::Filtering ==
//               WGPUSamplerBindingType_Filtering);
// static_assert(prism::graphics::common::SamplerBindingType::NonFiltering ==
//               WGPUSamplerBindingType_NonFiltering);
// static_assert(prism::graphics::common::SamplerBindingType::Comparison ==
//               WGPUSamplerBindingType_Comparison);

// static_assert(prism::graphics::common::StoreOp::Undefined == WGPUStoreOp_Undefined);
// static_assert(prism::graphics::common::StoreOp::Store == WGPUStoreOp_Store);
// static_assert(prism::graphics::common::StoreOp::Discard == WGPUStoreOp_Discard);

// static_assert(prism::graphics::common::TextureComponentType::Float ==
//               WGPUTextureComponentType_Float);
// static_assert(prism::graphics::common::TextureComponentType::Sint ==
// WGPUTextureComponentType_Sint); static_assert(prism::graphics::common::TextureComponentType::Uint
// == WGPUTextureComponentType_Uint);
// static_assert(prism::graphics::common::TextureComponentType::DepthComparison ==
//               WGPUTextureComponentType_DepthComparison);

// static_assert(prism::graphics::common::TextureDimension::_1D == WGPUTextureDimension_1D);
// static_assert(prism::graphics::common::TextureDimension::_2D == WGPUTextureDimension_2D);
// static_assert(prism::graphics::common::TextureDimension::_3D == WGPUTextureDimension_3D);

// static_assert(prism::graphics::common::TextureFormat::Undefined == WGPUTextureFormat_Undefined);
// static_assert(prism::graphics::common::TextureFormat::R8Unorm == WGPUTextureFormat_R8Unorm);
// static_assert(prism::graphics::common::TextureFormat::R8Snorm == WGPUTextureFormat_R8Snorm);
// static_assert(prism::graphics::common::TextureFormat::R8Uint == WGPUTextureFormat_R8Uint);
// static_assert(prism::graphics::common::TextureFormat::R8Sint == WGPUTextureFormat_R8Sint);
// static_assert(prism::graphics::common::TextureFormat::R16Uint == WGPUTextureFormat_R16Uint);
// static_assert(prism::graphics::common::TextureFormat::R16Sint == WGPUTextureFormat_R16Sint);
// static_assert(prism::graphics::common::TextureFormat::R16Float == WGPUTextureFormat_R16Float);
// static_assert(prism::graphics::common::TextureFormat::RG8Unorm == WGPUTextureFormat_RG8Unorm);
// static_assert(prism::graphics::common::TextureFormat::RG8Snorm == WGPUTextureFormat_RG8Snorm);
// static_assert(prism::graphics::common::TextureFormat::RG8Uint == WGPUTextureFormat_RG8Uint);
// static_assert(prism::graphics::common::TextureFormat::RG8Sint == WGPUTextureFormat_RG8Sint);
// static_assert(prism::graphics::common::TextureFormat::R32Float == WGPUTextureFormat_R32Float);
// static_assert(prism::graphics::common::TextureFormat::R32Uint == WGPUTextureFormat_R32Uint);
// static_assert(prism::graphics::common::TextureFormat::R32Sint == WGPUTextureFormat_R32Sint);
// static_assert(prism::graphics::common::TextureFormat::RG16Uint == WGPUTextureFormat_RG16Uint);
// static_assert(prism::graphics::common::TextureFormat::RG16Sint == WGPUTextureFormat_RG16Sint);
// static_assert(prism::graphics::common::TextureFormat::RG16Float == WGPUTextureFormat_RG16Float);
// static_assert(prism::graphics::common::TextureFormat::RGBA8Unorm ==
// WGPUTextureFormat_RGBA8Unorm);
// static_assert(prism::graphics::common::TextureFormat::RGBA8UnormSrgb ==
//               WGPUTextureFormat_RGBA8UnormSrgb);
// static_assert(prism::graphics::common::TextureFormat::RGBA8Snorm ==
// WGPUTextureFormat_RGBA8Snorm); static_assert(prism::graphics::common::TextureFormat::RGBA8Uint ==
// WGPUTextureFormat_RGBA8Uint); static_assert(prism::graphics::common::TextureFormat::RGBA8Sint ==
// WGPUTextureFormat_RGBA8Sint); static_assert(prism::graphics::common::TextureFormat::BGRA8Unorm ==
// WGPUTextureFormat_BGRA8Unorm);
// static_assert(prism::graphics::common::TextureFormat::BGRA8UnormSrgb ==
//               WGPUTextureFormat_BGRA8UnormSrgb);
// // static_assert(prism::graphics::common::TextureFormat::RGB10A2Unorm ==
// //               WGPUTextureFormat_RGB10A2Unorm);
// // static_assert(prism::graphics::common::TextureFormat::RG11B10Ufloat ==
// //               WGPUTextureFormat_RG11B10Ufloat);
// // static_assert(prism::graphics::common::TextureFormat::RGB9E5Ufloat ==
// //               WGPUTextureFormat_RGB9E5Ufloat);
// static_assert(prism::graphics::common::TextureFormat::RG32Float == WGPUTextureFormat_RG32Float);
// static_assert(prism::graphics::common::TextureFormat::RG32Uint == WGPUTextureFormat_RG32Uint);
// static_assert(prism::graphics::common::TextureFormat::RG32Sint == WGPUTextureFormat_RG32Sint);
// static_assert(prism::graphics::common::TextureFormat::RGBA16Uint ==
// WGPUTextureFormat_RGBA16Uint); static_assert(prism::graphics::common::TextureFormat::RGBA16Sint
// == WGPUTextureFormat_RGBA16Sint);
// static_assert(prism::graphics::common::TextureFormat::RGBA16Float ==
// WGPUTextureFormat_RGBA16Float); static_assert(prism::graphics::common::TextureFormat::RGBA32Float
// == WGPUTextureFormat_RGBA32Float);
// static_assert(prism::graphics::common::TextureFormat::RGBA32Uint ==
// WGPUTextureFormat_RGBA32Uint); static_assert(prism::graphics::common::TextureFormat::RGBA32Sint
// == WGPUTextureFormat_RGBA32Sint);
// static_assert(prism::graphics::common::TextureFormat::Depth16Unorm ==
//               WGPUTextureFormat_Depth16Unorm);
// static_assert(prism::graphics::common::TextureFormat::Depth32Float ==
//               WGPUTextureFormat_Depth32Float);

// static_assert(prism::graphics::common::TextureSampleType::Undefined ==
//               WGPUTextureSampleType_Undefined);
// static_assert(prism::graphics::common::TextureSampleType::Float == WGPUTextureSampleType_Float);
// static_assert(prism::graphics::common::TextureSampleType::UnfilterableFloat ==
//               WGPUTextureSampleType_UnfilterableFloat);
// static_assert(prism::graphics::common::TextureSampleType::Depth == WGPUTextureSampleType_Depth);
// static_assert(prism::graphics::common::TextureSampleType::Sint == WGPUTextureSampleType_Sint);
// static_assert(prism::graphics::common::TextureSampleType::Uint == WGPUTextureSampleType_Uint);

#undef ASSERT_ENUM_EQ
