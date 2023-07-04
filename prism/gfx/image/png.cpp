#include "prism/gfx/image/png.hpp"

#include "prism/common/log.hpp"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_STDIO
#define STBI_NO_FAILURE_STRINGS
#define STBI_ONLY_PNG
#include "stb_image.h"

namespace prism::gfx::image {

namespace {

// TODO: Move this to a more appropriate (shared) place.
std::pair<int /*bits_per_channel*/, int /*num_channels*/> get_format_info(TextureFormat format) {
    int bits_per_channel = 0;
    int num_channels     = 0;

    // TODO: Add support for more formats.
    switch (format) {
        case TextureFormat::R8Unorm:
        case TextureFormat::R8Snorm:
        case TextureFormat::R8Uint:
        case TextureFormat::R8Sint:
            bits_per_channel = 8;
            num_channels     = 1;
            break;

        case TextureFormat::RG8Unorm:
        case TextureFormat::RG8Snorm:
        case TextureFormat::RG8Uint:
        case TextureFormat::RG8Sint:
            bits_per_channel = 8;
            num_channels     = 2;
            break;

        case TextureFormat::RGBA8Unorm:
        case TextureFormat::RGBA8UnormSrgb:
        case TextureFormat::RGBA8Snorm:
        case TextureFormat::RGBA8Uint:
        case TextureFormat::RGBA8Sint:
            bits_per_channel = 8;
            num_channels     = 4;
            break;

        case TextureFormat::R16Uint:
        case TextureFormat::R16Sint:
            bits_per_channel = 16;
            num_channels     = 1;
            break;

        case TextureFormat::RG16Uint:
        case TextureFormat::RG16Sint:
            bits_per_channel = 16;
            num_channels     = 2;
            break;

        case TextureFormat::RGBA16Uint:
        case TextureFormat::RGBA16Sint:
            bits_per_channel = 16;
            num_channels     = 4;
            break;

        default:
            // TODO: Better error handling.
            common::log_fatal("unable to load into unsupported texture format");
    }

    return std::make_pair(bits_per_channel, num_channels);
}

}  // namespace

TextureView load_png(Context& ctx, TextureFormat format, const void* data, const size_t data_size) {
    stbi__context s{};
    stbi__start_mem(&s, reinterpret_cast<const stbi_uc*>(data), static_cast<int>(data_size));

    if (!stbi__png_test(&s)) {
        return {};
    }

    const auto [bits_per_channel, num_channels] = get_format_info(format);

    int               width           = 0;
    int               height          = 0;
    int               component_count = 0;
    stbi__result_info result{};
    void*             texture_bytes =
        stbi__png_load(&s, &width, &height, &component_count, num_channels, &result);

    if (result.bits_per_channel != bits_per_channel || component_count != num_channels) {
        common::log_fatal("mismatch between requested and loaded texture format");
    }

    const auto texture = ctx.create_texture_2d(TextureUsage::CopyDst | TextureUsage::TextureBinding,
                                               format, width, height);
    ctx.update_texture_2d(texture, width, height, texture_bytes,
                          sizeof(uint8_t) * 4 * width * height);

    stbi_image_free(texture_bytes);

    return ctx.create_texture_view_2d(texture, format);
}

}  // namespace prism::gfx::image
