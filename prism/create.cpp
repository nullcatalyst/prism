#include "prism/create.hpp"

#include "prism/common/platform.hpp"

namespace prism {

#if defined(PRISM_BACKEND_WEB)
std::tuple<app::Application, graphics::Context> create_for_canvas(const char* canvas_id) {
    const auto canvas = base::wasm::dom::HtmlCanvasElement::get_by_id(canvas_id);
    return std::make_tuple(app::Application{canvas}, graphics::Context{canvas});
}
#endif

#if defined(PRISM_BACKEND_SDL2) && defined(PRISM_BACKEND_WGPU)
std::tuple<app::Application, graphics::Context> create_window(const char*    title,
                                                              const uint32_t width,
                                                              const uint32_t height) {
#if defined(PRISM_PLATFORM_WINDOWS)
    constexpr const WGPUBackendType backend = WGPUBackendType_Vulkan;  // WGPUBackendType_D3D12;
#elif defined(PRISM_PLATFORM_MACOS) || defined(PRISM_PLATFORM_IOS)
    constexpr const WGPUBackendType backend = WGPUBackendType_Metal;
#elif defined(PRISM_PLATFORM_LINUX)
    constexpr const WGPUBackendType backend = WGPUBackendType_Vulkan;
#else
    static_assert(false, "Unsupported platform");
#endif

    const auto window = app::create_window(title, width, height, backend);
    PRISM_DEBUG_RESULT(window);
    const WGPUInstanceDescriptor instance_desc = {
        .nextInChain = nullptr,
    };
    WGPUInstance instance = wgpuCreateInstance(&instance_desc);
    PRISM_DEBUG_RESULT(instance);
    const auto surface = app::create_surface_for_window(instance, window);
    PRISM_DEBUG_RESULT(surface);

    auto app          = app::Application{window};
    const auto [w, h] = app.drawable_size();
    auto ctx          = graphics::Context{instance, surface, w, h, app.pixel_ratio()};

    return std::make_tuple(std::move(app), std::move(ctx));
}
#endif  // defined(PRISM_BACKEND_SDL2) && defined(PRISM_BACKEND_WGPU)

}  // namespace prism
