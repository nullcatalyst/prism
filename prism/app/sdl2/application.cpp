#include "prism/app/sdl2/application.hpp"

#include <chrono>
#include <mutex>  // std::call_once, std::once_flag
#include <tuple>

#include "SDL_syswm.h"
#include "SDL_vulkan.h"
#include "prism/common/debug.hpp"
#include "prism/common/platform.hpp"

// TODO: Remove this when SDL2 gets proper Windows DPI support
// Abuse SDL header to load correct OS headers
#include "SDL_syswm.h"

namespace prism::app::inline sdl2 {

namespace {

std::once_flag _init_flag;

}  // namespace

SDL_Window* create_window(const char* const title, uint32_t width, uint32_t height,
                          const WGPUBackendType backend_type) {
    std::call_once(_init_flag, []() {
#if defined(PRISM_PLATFORM_WINDOWS)
        // TODO: Remove this when SDL2 gets proper Windows DPI support
        // See https://github.com/libsdl-org/SDL/pull/5393
        SetProcessDPIAware();
#endif

        // Disable fake mouse events being created for touch events.
        SDL_SetHint(SDL_HINT_TOUCH_MOUSE_EVENTS, "0");

        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
            ::prism::common::log_fatal("[SDL2] failed to initialize");
        }

        return true;
    });

    auto* window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    static_cast<int>(width), static_cast<int>(height),
                                    SDL_WINDOW_HIDDEN | SDL_WINDOW_ALLOW_HIGHDPI
#if defined(PRISM_PLATFORM_IOS)
                                        | SDL_WINDOW_FULLSCREEN
#elif defined(PRISM_PLATFORM_LINUX)
                                        | SDL_WINDOW_VULKAN
#endif
    );

    if (window == nullptr) {
        ::prism::common::log_fatal("[SDL2] failed to create window: ", SDL_GetError());
    }
    return window;
}

WGPUSurface create_surface_for_window(WGPUInstance instance, SDL_Window* const window) {
    SDL_SysWMinfo wm_info{};
    SDL_VERSION(&wm_info.version);
    SDL_GetWindowWMInfo(window, &wm_info);

#if defined(PRISM_PLATFORM_WINDOWS)
    const WGPUSurfaceDescriptorFromWindowsHWND windows_surface_desc{
        .chain =
            {
                .next  = nullptr,
                .sType = WGPUSType_SurfaceDescriptorFromWindowsHWND,
            },
        .hinstance = wm_info.info.win.hinstance,
        .hwnd      = wm_info.info.win.window,
    };
    const WGPUChainedStruct* surface_chain = &windows_surface_desc.chain;
#elif defined(PRISM_PLATFORM_LINUX)
    const WGPUSurfaceDescriptorFromXlibWindow x11_surface_desc{
        .chain =
            {
                .next  = nullptr,
                .sType = WGPUSType_SurfaceDescriptorFromXlibWindow,
            },
        .display = wm_info.info.x11.display,
        .window  = static_cast<uint32_t>(wm_info.info.x11.window),
    };
    const WGPUChainedStruct* surface_chain = &x11_surface_desc.chain;
#elif defined(PRISM_PLATFORM_MACOS) || defined(PRISM_PLATFORM_IOS)
    auto*      metal_layer        = SDL_Metal_GetLayer(SDL_Metal_CreateView(window));
    const auto metal_surface_desc = WGPUSurfaceDescriptorFromMetalLayer{
        .chain =
            {
                .next  = nullptr,
                .sType = WGPUSType_SurfaceDescriptorFromMetalLayer,
            },
        .layer = metal_layer,
    };
    const WGPUChainedStruct* surface_chain = &metal_surface_desc.chain;
#else
#error "No GPU supported platform detected"
    const WGPUChainedStruct* surface_chain = nullptr;
#endif

    const WGPUSurfaceDescriptor surface_desc{
        .nextInChain = surface_chain,
        .label       = nullptr,
    };
    WGPUSurface surface = wgpuInstanceCreateSurface(instance, &surface_desc);
    PRISM_DEBUG_RESULT(surface);
    return surface;
}

Application::Application(SDL_Window* const window) : _window{window} {
    const auto [window_width, window_height] = window_size();
    const auto [draw_width, draw_height]     = drawable_size();
    _mouse_scale_factor_x                    = draw_width / window_width;
    _mouse_scale_factor_y                    = draw_height / window_height;
}

Application::Application(Application&& other)
    : _window{other._window},
      _last_frame_time{other._last_frame_time},
      _mouse_scale_factor_x{other._mouse_scale_factor_x},
      _mouse_scale_factor_y{other._mouse_scale_factor_y},
      _on_mouse_move{std::move(other._on_mouse_move)},
      _on_mouse_button_down{std::move(other._on_mouse_button_down)},
      _on_mouse_button_up{std::move(other._on_mouse_button_up)},
      _on_key_down{std::move(other._on_key_down)},
      _on_key_up{std::move(other._on_key_up)} {
    other._window = nullptr;
}

Application& Application::operator=(Application&& other) {
    if (_window != nullptr) {
        close();
    }
    _window               = other._window;
    _last_frame_time      = other._last_frame_time;
    _mouse_scale_factor_x = other._mouse_scale_factor_x;
    _mouse_scale_factor_y = other._mouse_scale_factor_y;
    _on_mouse_move        = std::move(other._on_mouse_move);
    _on_mouse_button_down = std::move(other._on_mouse_button_down);
    _on_mouse_button_up   = std::move(other._on_mouse_button_up);
    _on_key_down          = std::move(other._on_key_down);
    _on_key_up            = std::move(other._on_key_up);

    other._window = nullptr;

    return *this;
}

Application::~Application() {
    if (_window != nullptr) {
        close();
    }
}

[[nodiscard]] std::string Application::base_file_path() const {
    char*       base_path = SDL_GetBasePath();
    std::string result    = base_path;
    SDL_free(base_path);
    return result;
}

[[nodiscard]] std::tuple<uint32_t, uint32_t> Application::window_size() const {
#if defined(PLATFORM_IOS)
    SDL_DisplayMode display_mode = {};
    if (SDL_GetCurrentDisplayMode(0, &display_mode) == 0) {
        return std::make_tuple(static_cast<uint32_t>(display_mode.w),
                               static_cast<uint32_t>(display_mode.h));
    }
    return std::make_tuple(0, 0);
#else
    int w = 0;
    int h = 0;
    SDL_GetWindowSize(_window, &w, &h);
    return std::make_tuple(static_cast<uint32_t>(w), static_cast<uint32_t>(h));
#endif
}

[[nodiscard]] std::tuple<uint32_t, uint32_t> Application::drawable_size() const {
    int w = 0;
    int h = 0;
#if defined(PLATFORM_MACOS) || defined(PLATFORM_IOS)
    SDL_Metal_GetDrawableSize(_window, &w, &h);
#else
    SDL_Vulkan_GetDrawableSize(_window, &w, &h);
#endif
    return std::make_tuple(static_cast<uint32_t>(w), static_cast<uint32_t>(h));
}

void Application::show() {
    PRISM_DEBUG_RESULT(_window);
    SDL_ShowWindow(_window);
}

void Application::hide() {
    PRISM_DEBUG_RESULT(_window);
    SDL_HideWindow(_window);
}

void Application::close() {
    PRISM_DEBUG_RESULT(_window);
    SDL_DestroyWindow(_window);
    _window = nullptr;
}

// The amount of time in seconds since the last time `frame_time()` was called
double Application::frame_time() {
    const auto now = std::chrono::high_resolution_clock::now();
    const auto delta =
        std::chrono::duration_cast<std::chrono::duration<double>>(now - _last_frame_time);
    _last_frame_time = now;
    return delta.count();
}

bool Application::poll() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return true;
            case SDL_MOUSEMOTION:
                if (_on_mouse_move != nullptr) {
                    _on_mouse_move(event.motion.x * _mouse_scale_factor_x,
                                   event.motion.y * _mouse_scale_factor_y);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (_on_mouse_button_down != nullptr) {
                    _on_mouse_button_down(static_cast<input::MouseButton>(event.button.button));
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (_on_mouse_button_up != nullptr) {
                    _on_mouse_button_up(static_cast<input::MouseButton>(event.button.button));
                }
                break;
            case SDL_KEYDOWN:
                if (_on_key_down != nullptr) {
                    _on_key_down(static_cast<input::KeyCode>(event.key.keysym.scancode));
                }
                break;
            case SDL_KEYUP:
                if (_on_key_up != nullptr) {
                    _on_key_up(static_cast<input::KeyCode>(event.key.keysym.scancode));
                }
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    if (_on_resize != nullptr) {
                        const auto [w, h] = drawable_size();
                        _on_resize(w, h);
                    }
                }
                break;
        }
    }

    return false;
}

}  // namespace prism::app::inline sdl2
