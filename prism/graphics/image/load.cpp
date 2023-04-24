#include "prism/graphics/image/load.hpp"

#include "qoi.h"
#include "stb_image.h"

namespace prism::graphics::image {

TextureView load(Context& ctx, const void* data, const size_t data_size) {
    int width  = 0;
    int height = 0;

    qoi_desc out_desc{};
    void*    texture_bytes = qoi_decode(data, data_size, &out_desc, 4);
    if (texture_bytes != nullptr) {
        width  = out_desc.width;
        height = out_desc.height;

        const auto texture =
            ctx.create_texture_2d(TextureUsage::CopyDst | TextureUsage::TextureBinding,
                                  TextureFormat::RGBA8Unorm, width, height);
        ctx.update_texture_2d(texture, width, height, texture_bytes,
                              sizeof(uint8_t) * 4 * width * height);

        free(texture_bytes);

        return ctx.create_texture_view_2d(texture, TextureFormat::RGBA8Unorm);
    }

    int channels  = 0;
    texture_bytes = stbi_load_from_memory(reinterpret_cast<const stbi_uc*>(data), data_size, &width,
                                          &height, &channels, 4);

    const auto texture = ctx.create_texture_2d(TextureUsage::CopyDst | TextureUsage::TextureBinding,
                                               TextureFormat::RGBA8Unorm, width, height);
    ctx.update_texture_2d(texture, width, height, texture_bytes,
                          sizeof(uint8_t) * 4 * width * height);

    stbi_image_free(texture_bytes);

    return ctx.create_texture_view_2d(texture, TextureFormat::RGBA8Unorm);
}

}  // namespace prism::graphics::image
