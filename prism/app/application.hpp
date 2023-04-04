#pragma once

#include "prism/app/input.hpp"

#if defined(PRISM_BACKEND_SDL2)
#include "prism/app/sdl2/application.hpp"
#elif defined(PRISM_BACKEND_WEB)
#include "prism/app/web/application.hpp"
#else
#error "No prism application backend defined"
#endif

#if __cplusplus >= 202002L && __has_include(<concepts>)

#include <concepts>

namespace prism::app::internal {

template <typename T>
concept Application =
    requires(T app) {
        { app.show() };
        { app.hide() };
        { app.close() };
        { app.poll() } -> std::convertible_to<bool>;
        { app.on_mouse_move(static_cast<void (*)(float x, float y)>(nullptr)) };
        {
            app.on_mouse_button_down(
                static_cast<void (*)(const prism::app::input::MouseButton button)>(nullptr))
        };
        {
            app.on_mouse_button_up(
                static_cast<void (*)(const prism::app::input::MouseButton button)>(nullptr))
        };
        {
            app.on_key_down(
                static_cast<void (*)(const prism::app::input::KeyCode key_code)>(nullptr))
        };
        {
            app.on_key_up(static_cast<void (*)(const prism::app::input::KeyCode key_code)>(nullptr))
        };
    };

static_assert(Application<::prism::app::Application>);

}  // namespace prism::app::internal

#endif
