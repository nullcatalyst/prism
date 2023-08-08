#pragma once

#include "webgpu-headers/webgpu.h"

// This header exists entirely to validate that the enums in the prism::gfx namespace match the
// enums in by the WGPU C headers. Duplicating the enums into C++ allows us to introduce type safety
// through the use of enum classes.

#define ASSERT_ENUM_EQ($type, $value) \
    static_assert(static_cast<uint32_t>(prism::gfx::$type::$value) == WGPU##$type##_##$value)

#define ASSERT_RENAMED_ENUM_EQ($type, $value, $wgpu_value) \
    static_assert(static_cast<uint32_t>(prism::gfx::$type::$value) == $wgpu_value)

ASSERT_ENUM_EQ(AddressMode, Repeat);
ASSERT_ENUM_EQ(AddressMode, MirrorRepeat);
ASSERT_ENUM_EQ(AddressMode, ClampToEdge);

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

ASSERT_ENUM_EQ(BufferUsage, None);
ASSERT_ENUM_EQ(BufferUsage, MapRead);
ASSERT_ENUM_EQ(BufferUsage, MapWrite);
ASSERT_ENUM_EQ(BufferUsage, CopySrc);
ASSERT_ENUM_EQ(BufferUsage, CopyDst);
ASSERT_ENUM_EQ(BufferUsage, Index);
ASSERT_ENUM_EQ(BufferUsage, Vertex);
ASSERT_ENUM_EQ(BufferUsage, Uniform);
ASSERT_ENUM_EQ(BufferUsage, Storage);
ASSERT_ENUM_EQ(BufferUsage, Indirect);
ASSERT_ENUM_EQ(BufferUsage, QueryResolve);

ASSERT_ENUM_EQ(ColorWriteMask, None);
ASSERT_ENUM_EQ(ColorWriteMask, Red);
ASSERT_ENUM_EQ(ColorWriteMask, Green);
ASSERT_ENUM_EQ(ColorWriteMask, Blue);
ASSERT_ENUM_EQ(ColorWriteMask, Alpha);
ASSERT_ENUM_EQ(ColorWriteMask, All);

ASSERT_ENUM_EQ(CompareFunction, Undefined);
ASSERT_ENUM_EQ(CompareFunction, Never);
ASSERT_ENUM_EQ(CompareFunction, Less);
ASSERT_ENUM_EQ(CompareFunction, LessEqual);
ASSERT_ENUM_EQ(CompareFunction, Greater);
ASSERT_ENUM_EQ(CompareFunction, GreaterEqual);
ASSERT_ENUM_EQ(CompareFunction, Equal);
ASSERT_ENUM_EQ(CompareFunction, NotEqual);
ASSERT_ENUM_EQ(CompareFunction, Always);

ASSERT_ENUM_EQ(ComputePassTimestampLocation, Beginning);
ASSERT_ENUM_EQ(ComputePassTimestampLocation, End);

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

ASSERT_ENUM_EQ(PresentMode, Immediate);
ASSERT_ENUM_EQ(PresentMode, Mailbox);
ASSERT_ENUM_EQ(PresentMode, Fifo);

ASSERT_ENUM_EQ(PrimitiveTopology, PointList);
ASSERT_ENUM_EQ(PrimitiveTopology, LineList);
ASSERT_ENUM_EQ(PrimitiveTopology, LineStrip);
ASSERT_ENUM_EQ(PrimitiveTopology, TriangleList);
ASSERT_ENUM_EQ(PrimitiveTopology, TriangleStrip);

ASSERT_ENUM_EQ(RenderPassTimestampLocation, Beginning);
ASSERT_ENUM_EQ(RenderPassTimestampLocation, End);

ASSERT_ENUM_EQ(SamplerBindingType, Undefined);
ASSERT_ENUM_EQ(SamplerBindingType, Filtering);
ASSERT_ENUM_EQ(SamplerBindingType, NonFiltering);
ASSERT_ENUM_EQ(SamplerBindingType, Comparison);

ASSERT_ENUM_EQ(ShaderStage, None);
ASSERT_ENUM_EQ(ShaderStage, Vertex);
ASSERT_ENUM_EQ(ShaderStage, Fragment);
ASSERT_ENUM_EQ(ShaderStage, Compute);

ASSERT_ENUM_EQ(StencilOperation, Keep);
ASSERT_ENUM_EQ(StencilOperation, Zero);
ASSERT_ENUM_EQ(StencilOperation, Replace);
ASSERT_ENUM_EQ(StencilOperation, Invert);
ASSERT_ENUM_EQ(StencilOperation, IncrementClamp);
ASSERT_ENUM_EQ(StencilOperation, DecrementClamp);
ASSERT_ENUM_EQ(StencilOperation, IncrementWrap);
ASSERT_ENUM_EQ(StencilOperation, DecrementWrap);

ASSERT_ENUM_EQ(StorageTextureAccess, Undefined);
ASSERT_ENUM_EQ(StorageTextureAccess, WriteOnly);

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

ASSERT_ENUM_EQ(TextureUsage, None);
ASSERT_ENUM_EQ(TextureUsage, CopySrc);
ASSERT_ENUM_EQ(TextureUsage, CopyDst);
ASSERT_ENUM_EQ(TextureUsage, TextureBinding);
ASSERT_ENUM_EQ(TextureUsage, StorageBinding);
ASSERT_ENUM_EQ(TextureUsage, RenderAttachment);

ASSERT_ENUM_EQ(TextureViewDimension, Undefined);
ASSERT_RENAMED_ENUM_EQ(TextureViewDimension, _1D, WGPUTextureViewDimension_1D);
ASSERT_RENAMED_ENUM_EQ(TextureViewDimension, _2D, WGPUTextureViewDimension_2D);
ASSERT_RENAMED_ENUM_EQ(TextureViewDimension, _2DArray, WGPUTextureViewDimension_2DArray);
ASSERT_ENUM_EQ(TextureViewDimension, Cube);
ASSERT_ENUM_EQ(TextureViewDimension, CubeArray);
ASSERT_RENAMED_ENUM_EQ(TextureViewDimension, _3D, WGPUTextureViewDimension_3D);

ASSERT_ENUM_EQ(VertexFormat, Undefined);
ASSERT_ENUM_EQ(VertexFormat, Uint8x2);
ASSERT_ENUM_EQ(VertexFormat, Uint8x4);
ASSERT_ENUM_EQ(VertexFormat, Sint8x2);
ASSERT_ENUM_EQ(VertexFormat, Sint8x4);
ASSERT_ENUM_EQ(VertexFormat, Unorm8x2);
ASSERT_ENUM_EQ(VertexFormat, Unorm8x4);
ASSERT_ENUM_EQ(VertexFormat, Snorm8x2);
ASSERT_ENUM_EQ(VertexFormat, Snorm8x4);
ASSERT_ENUM_EQ(VertexFormat, Uint16x2);
ASSERT_ENUM_EQ(VertexFormat, Uint16x4);
ASSERT_ENUM_EQ(VertexFormat, Sint16x2);
ASSERT_ENUM_EQ(VertexFormat, Sint16x4);
ASSERT_ENUM_EQ(VertexFormat, Unorm16x2);
ASSERT_ENUM_EQ(VertexFormat, Unorm16x4);
ASSERT_ENUM_EQ(VertexFormat, Snorm16x2);
ASSERT_ENUM_EQ(VertexFormat, Snorm16x4);
ASSERT_ENUM_EQ(VertexFormat, Float16x2);
ASSERT_ENUM_EQ(VertexFormat, Float16x4);
ASSERT_ENUM_EQ(VertexFormat, Float32);
ASSERT_ENUM_EQ(VertexFormat, Float32x2);
ASSERT_ENUM_EQ(VertexFormat, Float32x3);
ASSERT_ENUM_EQ(VertexFormat, Float32x4);
ASSERT_ENUM_EQ(VertexFormat, Uint32);
ASSERT_ENUM_EQ(VertexFormat, Uint32x2);
ASSERT_ENUM_EQ(VertexFormat, Uint32x3);
ASSERT_ENUM_EQ(VertexFormat, Uint32x4);
ASSERT_ENUM_EQ(VertexFormat, Sint32);
ASSERT_ENUM_EQ(VertexFormat, Sint32x2);
ASSERT_ENUM_EQ(VertexFormat, Sint32x3);
ASSERT_ENUM_EQ(VertexFormat, Sint32x4);

ASSERT_ENUM_EQ(VertexStepMode, Vertex);
ASSERT_ENUM_EQ(VertexStepMode, Instance);
ASSERT_ENUM_EQ(VertexStepMode, VertexBufferNotUsed);

#undef ASSERT_RENAMED_ENUM_EQ
#undef ASSERT_ENUM_EQ
