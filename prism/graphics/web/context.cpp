#include "prism/graphics/web/context.hpp"

#include "parse/common/log.hpp"
#include "prism/graphics/web/js_api.hpp"
#include "prism/graphics/web/js_strings.hpp"

namespace prism::graphics::inline web {

Context::Context(js::HtmlCanvasElement canvas)
    : _context{js::from_raw(gpu_create_context(canvas.obj_id()))} {
    // TODO: Fetch this properly instead of assuming, even if this is true in chrome at the moment.
    _surface_format = WGPUTextureFormat_BGRA8Unorm;
}

BindGroupLayout Context::create_bind_group_layout(const desc::BindGroupLayout& layout_desc) {
    js::Object js_desc = js::Object::object();

    js::Object entries_desc = js::Object::array();
    for (int i = 0, end = layout_desc.entryCount; i < end; ++i) {
        js::Object entry_desc = js::Object::object();
        entry_desc.set("binding", static_cast<double>(layout_desc.entries[i].binding));
        entry_desc.set("visibility", static_cast<double>(layout_desc.entries[i].visibility));

        if (layout_desc.entries[i].buffer.type != WGPUBufferBindingType_Undefined) {
            js::Object buffer_desc = js::Object::object();
            buffer_desc.set("type", enum_to_string(layout_desc.entries[i].buffer.type));
            buffer_desc.set("minBindingSize",
                            static_cast<double>(layout_desc.entries[i].buffer.minBindingSize));
            entry_desc.set("buffer", buffer_desc);
        }

        if (layout_desc.entries[i].sampler.type != WGPUSamplerBindingType_Undefined) {
            js::Object sampler_desc = js::Object::object();
            sampler_desc.set("type", enum_to_string(layout_desc.entries[i].sampler.type));
            entry_desc.set("sampler", sampler_desc);
        }

        if (layout_desc.entries[i].texture.sampleType != WGPUTextureSampleType_Undefined) {
            js::Object texture_desc = js::Object::object();
            texture_desc.set("sampleType",
                             enum_to_string(layout_desc.entries[i].texture.sampleType));
            texture_desc.set("viewDimension",
                             enum_to_string(layout_desc.entries[i].texture.viewDimension));
            texture_desc.set("multisampled",
                             static_cast<double>(layout_desc.entries[i].texture.multisampled));
            entry_desc.set("texture", texture_desc);
        }

        entries_desc.push(entry_desc);
    }
    js_desc.set("entries", entries_desc);

    return BindGroupLayout{_context.obj_id(),
                           gpu_create_bind_group_layout(_context.obj_id(), js_desc.obj_id())};
}

BindGroup Context::create_bind_group(const desc::BindGroup& bind_group_desc) {
    js::Object js_desc = js::Object::object();
    gpu_set_object_bind_group_layout_property(_context.obj_id(), js_desc.obj_id(), "layout",
                                              reinterpret_cast<uintptr_t>(bind_group_desc.layout));

    js::Object entries_desc = js::Object::array();
    for (int i = 0, end = bind_group_desc.entryCount; i < end; ++i) {
        js::Object entry_desc = js::Object::object();
        entry_desc.set("binding", static_cast<double>(bind_group_desc.entries[i].binding));

        if (bind_group_desc.entries[i].buffer != nullptr) {
            js::Object buffer_entry_desc = js::Object::object();
            gpu_set_object_buffer_property(
                _context.obj_id(), buffer_entry_desc.obj_id(), "buffer",
                reinterpret_cast<uintptr_t>(bind_group_desc.entries[i].buffer));
            buffer_entry_desc.set("offset", static_cast<double>(bind_group_desc.entries[i].offset));
            buffer_entry_desc.set("size", static_cast<double>(bind_group_desc.entries[i].size));
            entry_desc.set("resource", buffer_entry_desc);
        }

        if (bind_group_desc.entries[i].sampler != nullptr) {
            gpu_set_object_sampler_property(
                _context.obj_id(), entry_desc.obj_id(), "resource",
                reinterpret_cast<uintptr_t>(bind_group_desc.entries[i].sampler));
        }

        if (bind_group_desc.entries[i].textureView != nullptr) {
            gpu_set_object_texture_view_property(
                _context.obj_id(), entry_desc.obj_id(), "resource",
                reinterpret_cast<uintptr_t>(bind_group_desc.entries[i].textureView));
        }

        entries_desc.push(entry_desc);
    }
    js_desc.set("entries", entries_desc);

    return BindGroup{_context.obj_id(), gpu_create_bind_group(_context.obj_id(), js_desc.obj_id())};
}

ShaderModule Context::create_shader_module(const char* source) {
    return ShaderModule{_context.obj_id(), gpu_create_shader_module(_context.obj_id(), source)};
}

PipelineLayout Context::create_pipeline_layout(const desc::PipelineLayout& layout_desc) {
    js::Object js_desc = js::Object::object();

    js::Object bind_group_layouts_array = js::Object::array();
    for (int i = 0, end = layout_desc.bindGroupLayoutCount; i < end; ++i) {
        gpu_set_object_bind_group_layout_property(
            _context.obj_id(), bind_group_layouts_array.obj_id(), nullptr,
            reinterpret_cast<uintptr_t>(layout_desc.bindGroupLayouts[i]));
    }
    js_desc.set("bindGroupLayouts", bind_group_layouts_array);

    return PipelineLayout{_context.obj_id(),
                          gpu_create_pipeline_layout(_context.obj_id(), js_desc.obj_id())};
}

RenderPipeline Context::create_render_pipeline(const desc::RenderPipeline& pipeline_desc) {
    js::Object js_desc = js::Object::object();
    gpu_set_object_pipeline_layout_property(_context.obj_id(), js_desc.obj_id(), "layout",
                                            reinterpret_cast<uintptr_t>(pipeline_desc.layout));

    {  // desc.vertex
        js::Object vertex_desc = js::Object::object();
        gpu_set_object_shader_module_property(
            _context.obj_id(), vertex_desc.obj_id(), "module",
            reinterpret_cast<uintptr_t>(pipeline_desc.vertex.module));
        vertex_desc.set("entryPoint", pipeline_desc.vertex.entryPoint);

        js::Object buffers_desc = js::Object::array();
        for (int i = 0, end = pipeline_desc.vertex.bufferCount; i < end; ++i) {
            js::Object buffer_desc = js::Object::object();
            buffer_desc.set("arrayStride",
                            static_cast<double>(pipeline_desc.vertex.buffers[i].arrayStride));
            buffer_desc.set("stepMode", enum_to_string(pipeline_desc.vertex.buffers[i].stepMode));

            js::Object attributes_desc = js::Object::array();
            for (int j = 0, end = pipeline_desc.vertex.buffers[i].attributeCount; j < end; ++j) {
                js::Object attribute_desc = js::Object::object();
                attribute_desc.set(
                    "format", enum_to_string(pipeline_desc.vertex.buffers[i].attributes[j].format));
                attribute_desc.set(
                    "offset",
                    static_cast<double>(pipeline_desc.vertex.buffers[i].attributes[j].offset));
                attribute_desc.set(
                    "shaderLocation",
                    static_cast<double>(
                        pipeline_desc.vertex.buffers[i].attributes[j].shaderLocation));
                attributes_desc.push(attribute_desc);
            }
            buffer_desc.set("attributes", attributes_desc);

            buffers_desc.push(buffer_desc);
        }
        vertex_desc.set("buffers", buffers_desc);

        js_desc.set("vertex", vertex_desc);
    }
    {  // desc.primitive
        js::Object primitive_desc = js::Object::object();
        primitive_desc.set("topology", enum_to_string(pipeline_desc.primitive.topology));
        if (pipeline_desc.primitive.stripIndexFormat != WGPUIndexFormat_Undefined) {
            primitive_desc.set("stripIndexFormat",
                               enum_to_string(pipeline_desc.primitive.stripIndexFormat));
        }
        primitive_desc.set("frontFace", enum_to_string(pipeline_desc.primitive.frontFace));
        primitive_desc.set("cullMode", enum_to_string(pipeline_desc.primitive.cullMode));
        js_desc.set("primitive", primitive_desc);
    }

    if (pipeline_desc.depthStencil != nullptr) {
        // TODO: Add support for stencils
        js::Object depth_desc = js::Object::object();
        depth_desc.set("format", enum_to_string(pipeline_desc.depthStencil->format));
        depth_desc.set("depthCompare", enum_to_string(pipeline_desc.depthStencil->depthCompare));
        depth_desc.set("depthWriteEnabled",
                       static_cast<double>(pipeline_desc.depthStencil->depthWriteEnabled));
        depth_desc.set("depthBias", static_cast<double>(pipeline_desc.depthStencil->depthBias));
        depth_desc.set("depthBiasSlopeScale",
                       static_cast<double>(pipeline_desc.depthStencil->depthBiasSlopeScale));
        depth_desc.set("depthBiasClamp",
                       static_cast<double>(pipeline_desc.depthStencil->depthBiasClamp));

        js_desc.set("depthStencil", depth_desc);
    }
    // TODO: multisample

    if (pipeline_desc.fragment != nullptr) {  // desc.fragment
        js::Object fragment_desc = js::Object::object();
        gpu_set_object_shader_module_property(
            _context.obj_id(), fragment_desc.obj_id(), "module",
            reinterpret_cast<uintptr_t>(pipeline_desc.fragment->module));
        fragment_desc.set("entryPoint", pipeline_desc.fragment->entryPoint);

        js::Object targets_desc = js::Object::array();
        for (int i = 0, end = pipeline_desc.fragment->targetCount; i < end; ++i) {
            const auto& target = pipeline_desc.fragment->targets[i];

            js::Object target_desc = js::Object::object();
            target_desc.set("format", enum_to_string(target.format));

            if (target.blend != nullptr) {
                js::Object blend_desc = js::Object::object();
                target_desc.set("blend", blend_desc);

                js::Object color_desc = js::Object::object();
                blend_desc.set("color", color_desc);
                color_desc.set("operation", enum_to_string(target.blend->color.operation));
                color_desc.set("srcFactor", enum_to_string(target.blend->color.srcFactor));
                color_desc.set("dstFactor", enum_to_string(target.blend->color.dstFactor));

                js::Object alpha_desc = js::Object::object();
                blend_desc.set("alpha", alpha_desc);
                alpha_desc.set("operation", enum_to_string(target.blend->alpha.operation));
                alpha_desc.set("srcFactor", enum_to_string(target.blend->alpha.srcFactor));
                alpha_desc.set("dstFactor", enum_to_string(target.blend->alpha.dstFactor));
            }

            // TODO: writeMask
            targets_desc.push(target_desc);
        }
        fragment_desc.set("targets", targets_desc);

        js_desc.set("fragment", fragment_desc);
    }

    return RenderPipeline{_context.obj_id(),
                          gpu_create_render_pipeline(_context.obj_id(), js_desc.obj_id())};
}

Buffer Context::create_buffer(const uint32_t usage, const uint64_t data_size) {
    return Buffer{_context.obj_id(),
                  gpu_create_buffer(_context.obj_id(), usage, data_size, 0, nullptr, 0)};
}

Buffer Context::create_buffer_with_data(const uint32_t usage, const void* data,
                                        const uint64_t data_size) {
    return Buffer{_context.obj_id(),
                  gpu_create_buffer(_context.obj_id(), usage, data_size, 0, data, data_size)};
}

Buffer Context::create_buffer_with_partial_data(const uint32_t usage, const uint64_t full_size,
                                                const uint64_t offset, const void* data,
                                                const uint64_t data_size) {
    return Buffer{_context.obj_id(),
                  gpu_create_buffer(_context.obj_id(), usage, full_size, offset, data, data_size)};
}

void Context::update_buffer(const Buffer& buffer, const uint64_t offset, const void* data,
                            const uint64_t data_size) {
    gpu_update_buffer(_context.obj_id(), buffer.obj_id(), offset, data, data_size);
}

Texture Context::create_texture_2d(const uint32_t usage, const WGPUTextureFormat format,
                                   const uint32_t width, const uint32_t height) {
    return Texture{_context.obj_id(), gpu_create_texture_2d(_context.obj_id(), usage,
                                                            enum_to_string(format), width, height)};
}

void Context::update_texture_2d(const Texture& texture, const uint32_t width, const uint32_t height,
                                const void* data, const uint64_t data_size) {
    gpu_update_texture_2d(_context.obj_id(), texture.obj_id(), width, height, data, data_size);
}

TextureView Context::create_texture_view_2d(const Texture&          texture,
                                            const WGPUTextureFormat format) {
    return TextureView{
        _context.obj_id(),
        gpu_create_texture_view_2d(_context.obj_id(), texture.obj_id(), enum_to_string(format))};
}

Sampler Context::create_sampler(WGPUAddressMode address_mode, WGPUFilterMode min_filter,
                                WGPUFilterMode mag_filter, WGPUFilterMode mipmap_filter) {
    return Sampler{_context.obj_id(),
                   gpu_create_sampler(_context.obj_id(), enum_to_string(address_mode),
                                      enum_to_string(min_filter), enum_to_string(mag_filter),
                                      enum_to_string(mipmap_filter))};
}

Sampler Context::create_sampler_comparison(WGPUAddressMode address_mode, WGPUFilterMode min_filter,
                                           WGPUFilterMode mag_filter, WGPUFilterMode mipmap_filter,
                                           WGPUCompareFunction compare) {
    return Sampler{_context.obj_id(), gpu_create_sampler_comparison(
                                          _context.obj_id(), enum_to_string(address_mode),
                                          enum_to_string(min_filter), enum_to_string(mag_filter),
                                          enum_to_string(mipmap_filter), enum_to_string(compare))};
}

TextureView Context::swap_chain_view() {
    return TextureView{_context.obj_id(), gpu_get_swap_chain_view(_context.obj_id())};
}

RenderPassEncoder Context::begin_render_pass(const desc::RenderPass& render_pass_desc,
                                             uint32_t width, uint32_t height) {
    js::Object js_desc          = js::Object::object();
    js::Object attachments_desc = js::Object::array();
    for (int i = 0, end = render_pass_desc.colorAttachmentCount; i < end; ++i) {
        const auto& color_attachment = render_pass_desc.colorAttachments[i];

        js::Object attachment_desc = js::Object::object();
        gpu_set_object_texture_view_property(_context.obj_id(), attachment_desc.obj_id(), "view",
                                             reinterpret_cast<uintptr_t>(color_attachment.view));
        attachment_desc.set("loadOp", enum_to_string(color_attachment.loadOp));
        attachment_desc.set("storeOp", enum_to_string(color_attachment.storeOp));

        js::Object clear_value_desc = js::Object::array();
        clear_value_desc.push(color_attachment.clearValue.r);
        clear_value_desc.push(color_attachment.clearValue.g);
        clear_value_desc.push(color_attachment.clearValue.b);
        clear_value_desc.push(color_attachment.clearValue.a);
        attachment_desc.set("clearValue", clear_value_desc);

        attachments_desc.push(attachment_desc);
    }
    js_desc.set("colorAttachments", attachments_desc);

    if (render_pass_desc.depthStencilAttachment != nullptr) {
        js::Object depth_attachment_desc = js::Object::object();
        gpu_set_object_texture_view_property(
            _context.obj_id(), depth_attachment_desc.obj_id(), "view",
            reinterpret_cast<uintptr_t>(render_pass_desc.depthStencilAttachment->view));
        depth_attachment_desc.set(
            "depthLoadOp", enum_to_string(render_pass_desc.depthStencilAttachment->depthLoadOp));
        depth_attachment_desc.set(
            "depthStoreOp", enum_to_string(render_pass_desc.depthStencilAttachment->depthStoreOp));
        depth_attachment_desc.set(
            "depthClearValue",
            static_cast<double>(render_pass_desc.depthStencilAttachment->depthClearValue));
        depth_attachment_desc.set(
            "depthReadOnly",
            static_cast<double>(render_pass_desc.depthStencilAttachment->depthReadOnly));

        js_desc.set("depthStencilAttachment", depth_attachment_desc);
    }

    return RenderPassEncoder{
        _context.obj_id(),
        gpu_begin_render_pass(_context.obj_id(), js_desc.obj_id(), width, height)};
}
void Context::end_render_pass(const RenderPassEncoder& render_pass) {
    gpu_end_render_pass(_context.obj_id(), render_pass.obj_id());
}

void Context::set_pipeline(const RenderPassEncoder& render_pass, const RenderPipeline& pipeline) {
    gpu_set_pipeline(_context.obj_id(), render_pass.obj_id(), pipeline.obj_id());
}

void Context::set_bind_group(const RenderPassEncoder& render_pass, const uint32_t index,
                             const BindGroup& bind_group) {
    gpu_set_bind_group(_context.obj_id(), render_pass.obj_id(), index, bind_group.obj_id());
}

void Context::set_buffer(const RenderPassEncoder& render_pass, const uint32_t slot,
                         const Buffer& buffer) {
    gpu_set_buffer(_context.obj_id(), render_pass.obj_id(), slot, buffer.obj_id(), 0, -1);
}

void Context::set_buffer_with_offset(const RenderPassEncoder& render_pass, const uint32_t slot,
                                     const Buffer& buffer, const uint64_t offset,
                                     const uint64_t length) {
    gpu_set_buffer(_context.obj_id(), render_pass.obj_id(), slot, buffer.obj_id(), offset, length);
}

void Context::set_index_u16_buffer(const RenderPassEncoder& render_pass, const Buffer& buffer) {
    gpu_set_index_u16_buffer(_context.obj_id(), render_pass.obj_id(), buffer.obj_id(), 0, -1);
}

void Context::set_index_u16_buffer_with_offset(const RenderPassEncoder& render_pass,
                                               const Buffer& buffer, const uint64_t offset,
                                               const uint64_t length) {
    gpu_set_index_u16_buffer(_context.obj_id(), render_pass.obj_id(), buffer.obj_id(), offset,
                             length);
}

void Context::set_index_u32_buffer(const RenderPassEncoder& render_pass, const Buffer& buffer) {
    gpu_set_index_u32_buffer(_context.obj_id(), render_pass.obj_id(), buffer.obj_id(), 0, -1);
}

void Context::set_index_u32_buffer_with_offset(const RenderPassEncoder& render_pass,
                                               const Buffer& buffer, const uint64_t offset,
                                               const uint64_t length) {
    gpu_set_index_u32_buffer(_context.obj_id(), render_pass.obj_id(), buffer.obj_id(), offset,
                             length);
}

void Context::draw(const RenderPassEncoder& render_pass, const uint32_t vertex_count,
                   const uint32_t instance_count, const uint32_t first_vertex,
                   const uint32_t first_instance) {
    gpu_draw(_context.obj_id(), render_pass.obj_id(), vertex_count, instance_count, first_vertex,
             first_instance);
}

void Context::draw_indexed(const RenderPassEncoder& render_pass, const uint32_t index_count,
                           const uint32_t instance_count, const uint32_t first_index,
                           const int32_t base_vertex, const uint32_t first_instance) {
    gpu_draw_indexed(_context.obj_id(), render_pass.obj_id(), index_count, instance_count,
                     first_index, base_vertex, first_instance);
}

void Context::draw_indirect(const RenderPassEncoder& render_pass, const Buffer& indirect_buffer,
                            const uint64_t indirect_offset) {
    gpu_draw_indirect(_context.obj_id(), render_pass.obj_id(), indirect_buffer.obj_id(),
                      indirect_offset);
}

void Context::draw_indexed_indirect(const RenderPassEncoder& render_pass,
                                    const Buffer& indirect_buffer, const uint64_t indirect_offset) {
    gpu_draw_indexed_indirect(_context.obj_id(), render_pass.obj_id(), indirect_buffer.obj_id(),
                              indirect_offset);
}

void Context::draw_multi_indirect(const RenderPassEncoder& render_pass,
                                  const Buffer& indirect_buffer, const uint64_t indirect_offset,
                                  const uint32_t indirect_count) {
    for (uint32_t i = 0; i < indirect_count; i++) {
        gpu_draw_indirect(_context.obj_id(), render_pass.obj_id(), indirect_buffer.obj_id(),
                          indirect_offset + i * sizeof(desc::DrawIndirectCommand));
    }
}

void Context::draw_multi_indexed_indirect(const RenderPassEncoder& render_pass,
                                          const Buffer&            indirect_buffer,
                                          const uint64_t           indirect_offset,
                                          const uint32_t           indirect_count) {
    for (uint32_t i = 0; i < indirect_count; i++) {
        gpu_draw_indexed_indirect(_context.obj_id(), render_pass.obj_id(), indirect_buffer.obj_id(),
                                  indirect_offset + i * sizeof(desc::DrawIndexedIndirectCommand));
    }
}

void Context::start_frame() { gpu_start_frame(_context.obj_id()); }

void Context::present_frame() { gpu_present_frame(_context.obj_id()); }

}  // namespace prism::graphics::inline web
