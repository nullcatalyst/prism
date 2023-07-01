#include "prism/gfx/image/jpg.hpp"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_STDIO
#define STBI_NO_FAILURE_STRINGS
#define STBI_ONLY_JPEG
#include "stb_image.h"

namespace prism::gfx::image {

TextureView load_jpg(Context& ctx, const void* data, const size_t data_size) {
    stbi__context s{};
    stbi__start_mem(&s, reinterpret_cast<const stbi_uc*>(data), static_cast<int>(data_size));

    if (!stbi__jpeg_test(&s)) {
        return {};
    }

    int               width           = 0;
    int               height          = 0;
    int               component_count = 0;
    stbi__result_info result{};
    void* texture_bytes = stbi__jpeg_load(&s, &width, &height, &component_count, 4, &result);

    const auto texture = ctx.create_texture_2d(TextureUsage::CopyDst | TextureUsage::TextureBinding,
                                               TextureFormat::RGBA8Unorm, width, height);
    ctx.update_texture_2d(texture, width, height, texture_bytes,
                          sizeof(uint8_t) * 4 * width * height);

    stbi_image_free(texture_bytes);

    return ctx.create_texture_view_2d(texture, TextureFormat::RGBA8Unorm);
}

}  // namespace prism::gfx::image
