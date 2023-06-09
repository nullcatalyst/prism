#pragma once

#include <tuple>

#include "prism/app/application.hpp"
#include "prism/gfx/context.hpp"

namespace prism {

#if defined(PRISM_BACKEND_WEB)
std::tuple<app::Application, gfx::Context> create_for_canvas(const char* canvas_id);
#endif

#if defined(PRISM_BACKEND_SDL2) && defined(PRISM_BACKEND_WGPU)
std::tuple<app::Application, gfx::Context> create_window(
    const char* title, uint32_t width, uint32_t height,
    PresentMode present_mode = PresentMode::Fifo);
#endif

}  // namespace prism
