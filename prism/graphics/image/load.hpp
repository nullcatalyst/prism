#pragma once

#include "prism/graphics/context.hpp"

namespace prism::graphics::image {

TextureView load(Context& ctx, const void* data, const size_t data_size);

}  // namespace prism::graphics::image
