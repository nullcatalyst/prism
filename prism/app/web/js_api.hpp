#pragma once

#include <cstdint>

#include "base/wasm/import.hpp"

namespace prism::app::inline web {

WASM_IMPORT(gpu, getPixelRatio) float _gpu_get_pixel_ratio();

}  // namespace prism::app::inline web
