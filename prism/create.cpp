#include "prism/create.hpp"

#include "prism/common/platform.hpp"

namespace prism {

#if defined(PRISM_BACKEND_WEB)
std::tuple<app::Application, gfx::Context> create_for_canvas(const char* canvas_id) {
    const auto canvas = js::HtmlCanvasElement::get_by_id(canvas_id);
    return std::make_tuple(app::Application{canvas}, gfx::Context{canvas});
}
#endif

#if defined(PRISM_BACKEND_SDL2) && defined(PRISM_BACKEND_WGPU)
constexpr WGPUBackendType choose_backend() {
#if defined(PRISM_PLATFORM_WINDOWS)
    return WGPUBackendType_D3D12;
#elif defined(PRISM_PLATFORM_MACOS) || defined(PRISM_PLATFORM_IOS)
    return WGPUBackendType_Metal;
#elif defined(PRISM_PLATFORM_LINUX)
    return WGPUBackendType_Vulkan;
#else
    static_assert(false, "Unsupported platform");
#endif
}

std::tuple<app::Application, gfx::Context> create_window(const char* const title,
                                                         const uint32_t    width,
                                                         const uint32_t    height,
                                                         const PresentMode present_mode) {
    const auto window = app::create_window(title, width, height, choose_backend());
    PRISM_DEBUG_RESULT(window);
    const WGPUInstanceDescriptor instance_desc = {
        .nextInChain = nullptr,
    };
    WGPUInstance instance = wgpuCreateInstance(&instance_desc);
    PRISM_DEBUG_RESULT(instance);
    const auto surface = app::create_surface_for_window(instance, window);
    PRISM_DEBUG_RESULT(surface);

    auto app                                   = app::Application{window};
    const auto [surface_width, surface_height] = app.drawable_size();

    return std::make_tuple(
        std::move(app),
        gfx::Context{instance, surface, surface_width, surface_height, present_mode,
                     static_cast<float>(surface_width) / static_cast<float>(width)});
}
#endif  // defined(PRISM_BACKEND_SDL2) && defined(PRISM_BACKEND_WGPU)

}  // namespace prism
