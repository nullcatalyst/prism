#pragma once

#include "prism/gfx/context.hpp"

namespace prism::gfx::image {

TextureView load_png(Context& ctx, const void* data, const size_t data_size);

}  // namespace prism::gfx::image
