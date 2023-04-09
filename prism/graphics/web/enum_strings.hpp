#pragma once

#include "prism/common/log.hpp"
#include "prism/graphics/types.hpp"

namespace prism::graphics::inline web {

namespace {

const char* enum_to_string(LoadOp load_op) {
    switch (load_op) {
        case LoadOp::Clear:
            return "clear";
        case LoadOp::Load:
            return "load";
        default:
            common::log_fatal("unknown load op (", load_op, ")");
    }
}

const char* enum_to_string(StoreOp store_op) {
    switch (store_op) {
        case StoreOp::Store:
            return "store";
        case StoreOp::Discard:
            return "discard";
        default:
            common::log_fatal("unknown store op (", store_op, ")");
    }
}

const char* enum_to_string(PrimitiveTopology topology) {
    switch (topology) {
        case PrimitiveTopology::PointList:
            return "point-list";
        case PrimitiveTopology::LineList:
            return "line-list";
        case PrimitiveTopology::LineStrip:
            return "line-strip";
        case PrimitiveTopology::TriangleList:
            return "triangle-list";
        case PrimitiveTopology::TriangleStrip:
            return "triangle-strip";
        default:
            common::log_fatal("unknown topology (", topology, ")");
    }
}

const char* enum_to_string(IndexFormat index_format) {
    switch (index_format) {
        case IndexFormat::Uint16:
            return "uint16";
        case IndexFormat::Uint32:
            return "uint32";
        default:
            common::log_fatal("unknown index format (", index_format, ")");
    }
}

const char* enum_to_string(FrontFace front_face) {
    switch (front_face) {
        case FrontFace::CCW:
            return "ccw";
        case FrontFace::CW:
            return "cw";
        default:
            common::log_fatal("unknown front face (", front_face, ")");
    }
}

const char* enum_to_string(CullMode cull_mode) {
    switch (cull_mode) {
        case CullMode::None:
            return "none";
        case CullMode::Front:
            return "front";
        case CullMode::Back:
            return "back";
        default:
            common::log_fatal("unknown cull mode (", cull_mode, ")");
    }
}

const char* enum_to_string(TextureFormat format) {
    switch (format) {
        case TextureFormat::R8Unorm:
            return "r8unorm";
        case TextureFormat::R8Snorm:
            return "r8snorm";
        case TextureFormat::R8Uint:
            return "r8uint";
        case TextureFormat::R8Sint:
            return "r8sint";
        case TextureFormat::R16Uint:
            return "r16uint";
        case TextureFormat::R16Sint:
            return "r16sint";
        case TextureFormat::R16Float:
            return "r16float";
        case TextureFormat::RG8Unorm:
            return "rg8unorm";
        case TextureFormat::RG8Snorm:
            return "rg8snorm";
        case TextureFormat::RG8Uint:
            return "rg8uint";
        case TextureFormat::RG8Sint:
            return "rg8sint";
        case TextureFormat::R32Float:
            return "r32float";
        case TextureFormat::R32Uint:
            return "r32uint";
        case TextureFormat::R32Sint:
            return "r32sint";
        case TextureFormat::RG16Uint:
            return "rg16uint";
        case TextureFormat::RG16Sint:
            return "rg16sint";
        case TextureFormat::RG16Float:
            return "rg16float";
        case TextureFormat::RGBA8Unorm:
            return "rgba8unorm";
        case TextureFormat::RGBA8UnormSrgb:
            return "rgba8unorm-srgb";
        case TextureFormat::RGBA8Snorm:
            return "rgba8snorm";
        case TextureFormat::RGBA8Uint:
            return "rgba8uint";
        case TextureFormat::RGBA8Sint:
            return "rgba8sint";
        case TextureFormat::BGRA8Unorm:
            return "bgra8unorm";
        case TextureFormat::BGRA8UnormSrgb:
            return "bgra8unorm-srgb";
        // case RGB10A2Unorm:
        //     return "rgb10a2unorm";
        // case RG11B10Ufloat:
        //     return "rg11b10ufloat";
        // case RGB9E5Ufloat:
        //     return "rgb9e5ufloat";
        case TextureFormat::RG32Float:
            return "rg32float";
        case TextureFormat::RG32Uint:
            return "rg32uint";
        case TextureFormat::RG32Sint:
            return "rg32sint";
        case TextureFormat::RGBA16Uint:
            return "rgba16uint";
        case TextureFormat::RGBA16Sint:
            return "rgba16sint";
        case TextureFormat::RGBA16Float:
            return "rgba16float";
        case TextureFormat::RGBA32Float:
            return "rgba32float";
        case TextureFormat::RGBA32Uint:
            return "rgba32uint";
        case TextureFormat::RGBA32Sint:
            return "rgba32sint";
        case TextureFormat::Depth16Unorm:
            return "depth16unorm";
        case TextureFormat::Depth32Float:
            return "depth32float";
        default:
            common::log_fatal("unknown texture format (", format, ")");
    }
}

const char* enum_to_string(AddressMode address_mode) {
    switch (address_mode) {
        case AddressMode::Repeat:
            return "repeat";
        case AddressMode::MirrorRepeat:
            return "mirror-repeat";
        case AddressMode::ClampToEdge:
            return "clamp-to-edge";
        default:
            common::log_fatal("unknown address mode (", address_mode, ")");
    }
}

const char* enum_to_string(FilterMode filter_mode) {
    switch (filter_mode) {
        case FilterMode::Nearest:
            return "nearest";
        case FilterMode::Linear:
            return "linear";
        default:
            common::log_fatal("unknown filter mode (", filter_mode, ")");
    }
}

const char* enum_to_string(BufferBindingType buffer_binding_type) {
    switch (buffer_binding_type) {
        case BufferBindingType::Uniform:
            return "uniform";
        case BufferBindingType::Storage:
            return "storage";
        case BufferBindingType::ReadOnlyStorage:
            return "read-only-storage";
        default:
            common::log_fatal("unknown buffer binding type (", buffer_binding_type, ")");
    }
}

const char* enum_to_string(SamplerBindingType sampler_binding_type) {
    switch (sampler_binding_type) {
        case SamplerBindingType::Filtering:
            return "filtering";
        case SamplerBindingType::NonFiltering:
            return "non-filtering";
        case SamplerBindingType::Comparison:
            return "comparison";
        default:
            common::log_fatal("unknown sampler binding type (", sampler_binding_type, ")");
    }
}

const char* enum_to_string(TextureSampleType texture_sample_type) {
    switch (texture_sample_type) {
        case TextureSampleType::Float:
            return "float";
        case TextureSampleType::UnfilterableFloat:
            return "unfilterable-float";
        case TextureSampleType::Depth:
            return "depth";
        case TextureSampleType::Sint:
            return "sint";
        case TextureSampleType::Uint:
            return "uint";
        default:
            common::log_fatal("unknown texture sample type (", texture_sample_type, ")");
    }
}

const char* enum_to_string(TextureViewDimension texture_view_dimension) {
    switch (texture_view_dimension) {
        case TextureViewDimension::_1D:
            return "1d";
        case TextureViewDimension::_2D:
            return "2d";
        case TextureViewDimension::_2DArray:
            return "2d-array";
        case TextureViewDimension::Cube:
            return "cube";
        case TextureViewDimension::CubeArray:
            return "cube-array";
        case TextureViewDimension::_3D:
            return "3d";
        default:
            common::log_fatal("unknown texture view dimension (", texture_view_dimension, ")");
    }
}

const char* enum_to_string(VertexFormat vertex_format) {
    switch (vertex_format) {
        case VertexFormat::Float32x4:
            return "float32x4";
        default:
            common::log_fatal("unknown vertex format (", vertex_format, ")");
    }
}

const char* enum_to_string(VertexStepMode vertex_step_mode) {
    switch (vertex_step_mode) {
        case VertexStepMode::Vertex:
            return "vertex";
        case VertexStepMode::Instance:
            return "instance";
        default:
            common::log_fatal("unknown vertex step mode (", vertex_step_mode, ")");
    }
}

const char* enum_to_string(CompareFunction compare_function) {
    switch (compare_function) {
        case CompareFunction::Never:
            return "never";
        case CompareFunction::Less:
            return "less";
        case CompareFunction::LessEqual:
            return "less-equal";
        case CompareFunction::Greater:
            return "greater";
        case CompareFunction::GreaterEqual:
            return "greater-equal";
        case CompareFunction::Equal:
            return "equal";
        case CompareFunction::NotEqual:
            return "not-equal";
        case CompareFunction::Always:
            return "always";
        default:
            common::log_fatal("unknown compare function (", compare_function, ")");
    }
}

const char* enum_to_string(BlendOperation blend_operation) {
    switch (blend_operation) {
        case BlendOperation::Add:
            return "add";
        case BlendOperation::Subtract:
            return "subtract";
        case BlendOperation::ReverseSubtract:
            return "reverse-subtract";
        case BlendOperation::Min:
            return "min";
        case BlendOperation::Max:
            return "max";
        default:
            common::log_fatal("unknown blend operation (", blend_operation, ")");
    }
}

const char* enum_to_string(BlendFactor blend_factor) {
    switch (blend_factor) {
        case BlendFactor::Zero:
            return "zero";
        case BlendFactor::One:
            return "one";
        case BlendFactor::OneMinusSrc:
            return "one-minus-src";
        case BlendFactor::SrcAlpha:
            return "src-alpha";
        case BlendFactor::OneMinusSrcAlpha:
            return "one-minus-src-alpha";
        case BlendFactor::Dst:
            return "dst";
        case BlendFactor::OneMinusDst:
            return "one-minus-dst";
        case BlendFactor::DstAlpha:
            return "dst-alpha";
        case BlendFactor::OneMinusDstAlpha:
            return "one-minus-dst-alpha";
        case BlendFactor::SrcAlphaSaturated:
            return "src-alpha-saturated";
        case BlendFactor::Constant:
            return "constant";
        case BlendFactor::OneMinusConstant:
            return "one-minus-constant";
        default:
            common::log_fatal("unknown blend factor (", blend_factor, ")");
    }
}

}  // namespace

}  // namespace prism::graphics::inline web
