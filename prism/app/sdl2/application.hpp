#pragma once

#include <chrono>
#include <functional>
#include <string>
#include <tuple>

#include "SDL.h"
#include "prism/app/input.hpp"
#include "webgpu-headers/webgpu.h"

namespace prism::app::inline sdl2 {

SDL_Window* create_window(const char* const title, const uint32_t width, const uint32_t height,
                          const WGPUBackendType backend_type);
WGPUSurface create_surface_for_window(WGPUInstance instance, SDL_Window* const window);

class Application final {
    SDL_Window*                                    _window = nullptr;
    std::chrono::high_resolution_clock::time_point _last_frame_time;
    float                                          _mouse_scale_factor_x = 1.0f;
    float                                          _mouse_scale_factor_y = 1.0f;

    std::function<void(const float x, const float y)>    _on_mouse_move         = nullptr;
    std::function<void(const input::MouseButton button)> _on_mouse_button_down  = nullptr;
    std::function<void(const input::MouseButton button)> _on_mouse_button_up    = nullptr;
    std::function<void(const input::KeyCode key_code)>   _on_key_down           = nullptr;
    std::function<void(const input::KeyCode key_code)>   _on_key_up             = nullptr;
    std::function<void(const uint32_t width, const uint32_t height)> _on_resize = nullptr;

  public:
    ////////////////////////////////
    // Backend specific
    Application(SDL_Window* window);

    constexpr SDL_Window* window() const { return _window; }
    std::string           base_file_path() const;

    ////////////////////////////////
    // General
    constexpr Application() = default;

    Application(const Application& other)            = delete;
    Application& operator=(const Application& other) = delete;

    Application(Application&& other);
    Application& operator=(Application&& other);

    ~Application();

    [[nodiscard]] std::tuple<uint32_t, uint32_t> window_size() const;
    [[nodiscard]] std::tuple<uint32_t, uint32_t> drawable_size() const;
    [[nodiscard]] float                          pixel_ratio() const {
        const auto [window_width, window_height]     = window_size();
        const auto [drawable_width, drawable_height] = drawable_size();
        return static_cast<float>(drawable_width) / static_cast<float>(window_width);
    }

    void show();
    void hide();
    void close();

    // The amount of time in seconds since the last time `frame_time()` was called
    double frame_time();

    // Returns true if the application should close
    bool poll();

    ////////////////////////////////
    // Event handlers
    template <typename T>
    void on_mouse_move(T&& callback) {
        _on_mouse_move = std::forward<T>(callback);
    }

    template <typename T>
    void on_mouse_button_down(T&& callback) {
        _on_mouse_button_down = std::forward<T>(callback);
    }

    template <typename T>
    void on_mouse_button_up(T&& callback) {
        _on_mouse_button_up = std::forward<T>(callback);
    }

    template <typename T>
    void on_key_down(T&& callback) {
        _on_key_down = std::forward<T>(callback);
    }

    template <typename T>
    void on_key_up(T&& callback) {
        _on_key_up = std::forward<T>(callback);
    }

    template <typename T>
    void on_resize(T&& callback) {
        _on_resize = std::forward<T>(callback);
    }
};

}  // namespace prism::app::inline sdl2
