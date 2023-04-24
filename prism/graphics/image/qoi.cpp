#include "prism/graphics/image/qoi.hpp"

#include "qoi.h"

namespace prism::graphics::image {

TextureView load_qoi(Context& ctx, const void* data, const size_t data_size) {
    qoi_desc out_desc{};
    void*    texture_bytes = qoi_decode(data, data_size, &out_desc, 4);

    const auto texture =
        ctx.create_texture_2d(TextureUsage::CopyDst | TextureUsage::TextureBinding,
                              TextureFormat::RGBA8Unorm, out_desc.width, out_desc.height);
    ctx.update_texture_2d(texture, out_desc.width, out_desc.height, texture_bytes,
                          sizeof(uint8_t) * 4 * out_desc.width * out_desc.height);

    free(texture_bytes);

    return ctx.create_texture_view_2d(texture, TextureFormat::RGBA8Unorm);
}

}  // namespace prism::graphics::image
