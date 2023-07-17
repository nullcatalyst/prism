#pragma once

#include <tuple>

#include "prism/app/application.hpp"
#include "prism/gfx/context.hpp"

namespace prism {

#if defined(PRISM_BACKEND_WEB)
std::tuple<app::Application, gfx::Context> create_for_canvas(const char* canvas_id);
#endif

#if defined(PRISM_BACKEND_SDL2) && defined(PRISM_BACKEND_WGPU)
std::tuple<app::Application, gfx::Context> create_window(const char* const title, const uint32_t width,
                                                         const uint32_t    height,
                                                         const PresentMode present_mode);
#endif

}  // namespace prism
