#include <memory>

#include "prism/prism.hpp"
#include "prism/wasm/export.hpp"

namespace {

prism::Application app;
prism::Context     ctx;

}  // namespace

WASM_EXPORT("init")
void init() {
    // Here we create a window and a graphics context.
    // We need to use a separate function for this because WASM WebGPU requires an asynchronous
    // callback, and async/await is not yet supported in WebAssembly.

    // So instead, we call `init()`, await the promise resolving, and then call `start()`.

#if defined(PRISM_BACKEND_SDL2)
    auto [_app, _ctx] = prism::create_window("hello_triangle", 1280, 720);
#elif defined(PRISM_BACKEND_WEB)
    auto [_app, _ctx] = prism::create_for_canvas("hello_triangle");
#else
#error "No prism platform defined"
#endif

    app = std::move(_app);
    ctx = std::move(_ctx);
}

WASM_EXPORT("start")
void start() {
    // [Optional] Add some event handlers if desired.
    app.on_mouse_move([&](const float x, const float y) {});
    app.on_mouse_button_down([&](const prism::app::input::MouseButton button) {});
    app.on_mouse_button_up([&](const prism::app::input::MouseButton button) {});
    app.on_key_down([&](const prism::app::input::KeyCode key_code) {});
    app.on_key_up([&](const prism::app::input::KeyCode key_code) {});

#if defined(PRISM_BACKEND_WEB)
    // TODO: Temporary workaround
    app.show();
#endif
}

WASM_EXPORT("render")
void render() {
    // Do rendering here.
}

#if defined(__wasm__)

WASM_EXPORT("memAlloc") void* memory_alloc(size_t size) { return malloc(size); }
WASM_EXPORT("memFree") void memory_free(void* ptr) { return free(ptr); }

#else

// DO NOT CHANGE main arg types.
// They must match SDL_main args for SDL to work.
int main(const int argc, char** const argv) {
    // Create the window and graphics context.
    init();

    // Load resources.
    start();

    // Render the first frame then call show to prevent a flash of garbage contents that sometimes
    // happens on some systems.
    render();
    app.show();

    // Start the main loop.
    while (!app.poll()) {
        render();
    }

    return 0;
}

#endif
