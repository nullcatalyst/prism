#pragma once

#include <functional>

#include "prism/app/input.hpp"
#include "prism/js/dom.hpp"

namespace prism::app::inline web {

class Application final {
    js::HtmlCanvasElement _canvas;

    std::function<void(const float x, const float y)>    _on_mouse_move         = nullptr;
    std::function<void(const input::MouseButton button)> _on_mouse_button_down  = nullptr;
    std::function<void(const input::MouseButton button)> _on_mouse_button_up    = nullptr;
    std::function<void(const input::KeyCode key_code)>   _on_key_down           = nullptr;
    std::function<void(const input::KeyCode key_code)>   _on_key_up             = nullptr;
    std::function<void(const uint32_t width, const uint32_t height)> _on_resize = nullptr;

  public:
    ////////////////////////////////
    // Backend specific
    Application(js::HtmlCanvasElement canvas);

    js::HtmlCanvasElement canvas() const { return _canvas; }

    void attach_event_listeners();

    ////////////////////////////////
    // General
    constexpr Application() = default;

    Application(const Application& other)            = delete;
    Application& operator=(const Application& other) = delete;

    Application(Application&& other)            = default;
    Application& operator=(Application&& other) = default;

    ~Application() = default;

    [[nodiscard]] std::tuple<uint32_t, uint32_t> window_size() const;
    [[nodiscard]] std::tuple<uint32_t, uint32_t> drawable_size() const;
    [[nodiscard]] float                          pixel_ratio() const;

    void show();
    void hide();
    void close();

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

}  // namespace prism::app::inline web
