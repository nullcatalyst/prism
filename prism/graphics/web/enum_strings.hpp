#pragma once

#include "prism/common/log.hpp"
#include "webgpu-headers/webgpu.h"

namespace prism::graphics::inline web {

namespace {

const char* enum_to_string(WGPULoadOp load_op) {
    switch (load_op) {
        case WGPULoadOp_Clear:
            return "clear";
        case WGPULoadOp_Load:
            return "load";
        default:
            common::log_fatal("unknown load op (", load_op, ")");
    }
}

const char* enum_to_string(WGPUStoreOp store_op) {
    switch (store_op) {
        case WGPUStoreOp_Store:
            return "store";
        case WGPUStoreOp_Discard:
            return "discard";
        default:
            common::log_fatal("unknown store op (", store_op, ")");
    }
}

const char* enum_to_string(WGPUPrimitiveTopology topology) {
    switch (topology) {
        case WGPUPrimitiveTopology_PointList:
            return "point-list";
        case WGPUPrimitiveTopology_LineList:
            return "line-list";
        case WGPUPrimitiveTopology_LineStrip:
            return "line-strip";
        case WGPUPrimitiveTopology_TriangleList:
            return "triangle-list";
        case WGPUPrimitiveTopology_TriangleStrip:
            return "triangle-strip";
        default:
            common::log_fatal("unknown topology (", topology, ")");
    }
}

const char* enum_to_string(WGPUIndexFormat index_format) {
    switch (index_format) {
        case WGPUIndexFormat_Uint16:
            return "uint16";
        case WGPUIndexFormat_Uint32:
            return "uint32";
        default:
            common::log_fatal("unknown index format (", index_format, ")");
    }
}

const char* enum_to_string(WGPUFrontFace front_face) {
    switch (front_face) {
        case WGPUFrontFace_CCW:
            return "ccw";
        case WGPUFrontFace_CW:
            return "cw";
        default:
            common::log_fatal("unknown front face (", front_face, ")");
    }
}

const char* enum_to_string(WGPUCullMode cull_mode) {
    switch (cull_mode) {
        case WGPUCullMode_None:
            return "none";
        case WGPUCullMode_Front:
            return "front";
        case WGPUCullMode_Back:
            return "back";
        default:
            common::log_fatal("unknown cull mode (", cull_mode, ")");
    }
}

const char* enum_to_string(WGPUTextureFormat format) {
    switch (format) {
        case WGPUTextureFormat_R16Uint:
            return "r16uint";
        case WGPUTextureFormat_R32Uint:
            return "r32uint";
        case WGPUTextureFormat_RGBA8Unorm:
            return "rgba8unorm";
        case WGPUTextureFormat_RGBA8UnormSrgb:
            return "rgba8unorm-srgb";
        case WGPUTextureFormat_BGRA8Unorm:
            return "bgra8unorm";
        case WGPUTextureFormat_BGRA8UnormSrgb:
            return "bgra8unorm-srgb";
        case WGPUTextureFormat_RGBA16Float:
            return "rgba16float";
        case WGPUTextureFormat_RGBA32Float:
            return "rgba32float";
        case WGPUTextureFormat_Depth32Float:
            return "depth32float";
        default:
            common::log_fatal("unknown texture format (", format, ")");
    }
}

const char* enum_to_string(WGPUAddressMode address_mode) {
    switch (address_mode) {
        case WGPUAddressMode_Repeat:
            return "repeat";
        case WGPUAddressMode_MirrorRepeat:
            return "mirror-repeat";
        case WGPUAddressMode_ClampToEdge:
            return "clamp-to-edge";
        default:
            common::log_fatal("unknown address mode (", address_mode, ")");
    }
}

const char* enum_to_string(WGPUFilterMode filter_mode) {
    switch (filter_mode) {
        case WGPUFilterMode_Nearest:
            return "nearest";
        case WGPUFilterMode_Linear:
            return "linear";
        default:
            common::log_fatal("unknown filter mode (", filter_mode, ")");
    }
}

const char* enum_to_string(WGPUBufferBindingType buffer_binding_type) {
    switch (buffer_binding_type) {
        case WGPUBufferBindingType_Uniform:
            return "uniform";
        case WGPUBufferBindingType_Storage:
            return "storage";
        case WGPUBufferBindingType_ReadOnlyStorage:
            return "read-only-storage";
        default:
            common::log_fatal("unknown buffer binding type (", buffer_binding_type, ")");
    }
}

const char* enum_to_string(WGPUSamplerBindingType sampler_binding_type) {
    switch (sampler_binding_type) {
        case WGPUSamplerBindingType_Filtering:
            return "filtering";
        case WGPUSamplerBindingType_NonFiltering:
            return "non-filtering";
        case WGPUSamplerBindingType_Comparison:
            return "comparison";
        default:
            common::log_fatal("unknown sampler binding type (", sampler_binding_type, ")");
    }
}

const char* enum_to_string(WGPUTextureSampleType texture_sample_type) {
    switch (texture_sample_type) {
        case WGPUTextureSampleType_Float:
            return "float";
        case WGPUTextureSampleType_UnfilterableFloat:
            return "unfilterable-float";
        case WGPUTextureSampleType_Depth:
            return "depth";
        case WGPUTextureSampleType_Sint:
            return "sint";
        case WGPUTextureSampleType_Uint:
            return "uint";
        default:
            common::log_fatal("unknown texture sample type (", texture_sample_type, ")");
    }
}

const char* enum_to_string(WGPUTextureViewDimension texture_view_dimension) {
    switch (texture_view_dimension) {
        case WGPUTextureViewDimension_1D:
            return "1d";
        case WGPUTextureViewDimension_2D:
            return "2d";
        case WGPUTextureViewDimension_2DArray:
            return "2d-array";
        case WGPUTextureViewDimension_Cube:
            return "cube";
        case WGPUTextureViewDimension_CubeArray:
            return "cube-array";
        case WGPUTextureViewDimension_3D:
            return "3d";
        default:
            common::log_fatal("unknown texture view dimension (", texture_view_dimension, ")");
    }
}

const char* enum_to_string(WGPUVertexFormat vertex_format) {
    switch (vertex_format) {
        case WGPUVertexFormat_Float32x4:
            return "float32x4";
        default:
            common::log_fatal("unknown vertex format (", vertex_format, ")");
    }
}

const char* enum_to_string(WGPUVertexStepMode vertex_step_mode) {
    switch (vertex_step_mode) {
        case WGPUVertexStepMode_Vertex:
            return "vertex";
        case WGPUVertexStepMode_Instance:
            return "instance";
        default:
            common::log_fatal("unknown vertex step mode (", vertex_step_mode, ")");
    }
}

const char* enum_to_string(WGPUCompareFunction compare_function) {
    switch (compare_function) {
        case WGPUCompareFunction_Never:
            return "never";
        case WGPUCompareFunction_Less:
            return "less";
        case WGPUCompareFunction_LessEqual:
            return "less-equal";
        case WGPUCompareFunction_Greater:
            return "greater";
        case WGPUCompareFunction_GreaterEqual:
            return "greater-equal";
        case WGPUCompareFunction_Equal:
            return "equal";
        case WGPUCompareFunction_NotEqual:
            return "not-equal";
        case WGPUCompareFunction_Always:
            return "always";
        default:
            common::log_fatal("unknown compare function (", compare_function, ")");
    }
}

const char* enum_to_string(WGPUBlendOperation blend_operation) {
    switch (blend_operation) {
        case WGPUBlendOperation_Add:
            return "add";
        case WGPUBlendOperation_Subtract:
            return "subtract";
        case WGPUBlendOperation_ReverseSubtract:
            return "reverse-subtract";
        case WGPUBlendOperation_Min:
            return "min";
        case WGPUBlendOperation_Max:
            return "max";
        default:
            common::log_fatal("unknown blend operation (", blend_operation, ")");
    }
}

const char* enum_to_string(WGPUBlendFactor blend_factor) {
    switch (blend_factor) {
        case WGPUBlendFactor_Zero:
            return "zero";
        case WGPUBlendFactor_One:
            return "one";
        case WGPUBlendFactor_OneMinusSrc:
            return "one-minus-src";
        case WGPUBlendFactor_SrcAlpha:
            return "src-alpha";
        case WGPUBlendFactor_OneMinusSrcAlpha:
            return "one-minus-src-alpha";
        case WGPUBlendFactor_Dst:
            return "dst";
        case WGPUBlendFactor_OneMinusDst:
            return "one-minus-dst";
        case WGPUBlendFactor_DstAlpha:
            return "dst-alpha";
        case WGPUBlendFactor_OneMinusDstAlpha:
            return "one-minus-dst-alpha";
        case WGPUBlendFactor_SrcAlphaSaturated:
            return "src-alpha-saturated";
        case WGPUBlendFactor_Constant:
            return "constant";
        case WGPUBlendFactor_OneMinusConstant:
            return "one-minus-constant";
        default:
            common::log_fatal("unknown blend factor (", blend_factor, ")");
    }
}

}  // namespace

}  // namespace prism::graphics::inline web
