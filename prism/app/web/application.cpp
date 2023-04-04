#include "prism/app/web/application.hpp"

#include "prism/app/web/js_api.hpp"
#include "prism/common/debug.hpp"

namespace prism::app::inline web {

Application::Application(base::wasm::dom::HtmlCanvasElement canvas) : _canvas{canvas} {}

[[nodiscard]] std::tuple<uint32_t, uint32_t> Application::window_size() const {
    return {_canvas.width(), _canvas.height()};
}

[[nodiscard]] std::tuple<uint32_t, uint32_t> Application::drawable_size() const {
    return {_canvas.width(), _canvas.height()};
}

[[nodiscard]] float Application::pixel_ratio() const { return _gpu_get_pixel_ratio(); }

void Application::show() {
    // Do nothing

    _canvas.on_mouse_moved(
        [](double x, double y, void* user_data) {
            auto* app = static_cast<Application*>(user_data);
            if (app->_on_mouse_move != nullptr) {
                app->_on_mouse_move(x, y);
            }
        },
        this);

    _canvas.on_mouse_button_down(
        [](uint32_t button, void* user_data) {
            auto* app = static_cast<Application*>(user_data);
            if (app->_on_mouse_button_down) {
                app->_on_mouse_button_down(static_cast<input::MouseButton>(button));
            }
        },
        this);

    _canvas.on_mouse_button_up(
        [](uint32_t button, void* user_data) {
            auto* app = static_cast<Application*>(user_data);
            if (app->_on_mouse_button_up != nullptr) {
                app->_on_mouse_button_up(static_cast<input::MouseButton>(button));
            }
        },
        this);

    _canvas.on_key_down(
        [](uint32_t key_code, void* user_data) {
            auto* app = static_cast<Application*>(user_data);
            if (app->_on_key_down) {
                app->_on_key_down(static_cast<input::KeyCode>(key_code));
            }
        },
        this);

    _canvas.on_key_up(
        [](uint32_t key_code, void* user_data) {
            auto* app = static_cast<Application*>(user_data);
            if (app->_on_key_up != nullptr) {
                app->_on_key_up(static_cast<input::KeyCode>(key_code));
            }
        },
        this);
}

void Application::hide() {
    // Unsupported
}

void Application::close() {
    // Unsupported
}

bool Application::poll() {
    // Do nothing
    return false;
}

}  // namespace prism::app::inline web
