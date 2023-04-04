#include <memory>

#include "prism/prism.hpp"
#include "prism/wasm/export.hpp"

namespace {

// I would recommend storing this somewhere rather than having a global variable.
// This is just for the sake of simplicity.
prism::RenderPipeline render_pipeline;

// These on the other hand do need to be global variables, in order to support WASM.
prism::Application app;
prism::Context     ctx;

const char* SHADER_WGSL = R"(
struct Varyings {
    @builtin(position) position: vec4<f32>,
    @location(0) color: vec4<f32>,
};

@vertex
fn vs_main(@builtin(vertex_index) i: u32) -> Varyings {
    var positions = array<vec4<f32>, 3>(
        vec4<f32>( 0.0,  0.5,  0.0, 1.0),
        vec4<f32>(-0.5, -0.5,  0.0, 1.0),
        vec4<f32>( 0.5, -0.5,  0.0, 1.0),
    );
    var color = array<vec4<f32>, 3>(
        vec4<f32>( 1.0,  0.0,  0.0, 1.0),
        vec4<f32>( 0.0,  1.0,  0.0, 1.0),
        vec4<f32>( 0.0,  0.0,  1.0, 1.0),
    );

    var o: Varyings;
    o.position = positions[i];
    o.color = color[i];
    return o;
}

@fragment
fn fs_main(v: Varyings) -> @location(0) vec4<f32> {
    return v.color;
}
)";

}  // namespace

WASM_EXPORT("init")
void init() {
    // Here we create a window and a graphics context.
    // We need to use a separate function for this because WASM WebGPU requires an asynchronous
    // callback, and async/await is not yet supported in WebAssembly.

    // So instead, we call `init()`, await the promise resolving, and then call `start()`.

#if defined(PRISM_BACKEND_SDL2)
    auto [new_app, new_ctx] = prism::create_window("hello_triangle", 1280, 720);
#elif defined(PRISM_BACKEND_WEB)
    auto [new_app, new_ctx] = prism::create_for_canvas("hello_triangle");
#else
#error "No prism platform defined"
#endif

    app = std::move(new_app);
    ctx = std::move(new_ctx);
}

WASM_EXPORT("start")
void start() {
    prism::Context::enable_debug();

    // Load resources here.
    auto shader_module = ctx.create_shader_module(SHADER_WGSL);

    const prism::ColorTargetState targets[] = {
        prism::ColorTargetState{
            .format = ctx.surface_format(),
        },
    };
    const auto fragment = prism::FragmentState{
        .module       = shader_module,
        .entry_point  = "fs_main",
        .target_count = std::size(targets),
        .targets      = targets,
    };
    render_pipeline = ctx.create_render_pipeline(prism::RenderPipelineDescriptor{
        .vertex =
            prism::VertexState{
                .module      = shader_module,
                .entry_point = "vs_main",
            },
        .primitive =
            prism::PrimitiveState{
                .topology = prism::PrimitiveTopology::TriangleList,
            },
        .fragment = &fragment,
    });

    // [Optional] Enable as many event handlers as desired.
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

    ctx.start_frame();

    const auto [width, height] = app.drawable_size();

    // Get the texture view for the next frame that will be displayed to the screen.
    auto next_frame = ctx.swap_chain_view();

    const prism::RenderPassColorAttachment color_attachments[] = {
        prism::RenderPassColorAttachment{
            .view        = next_frame,
            .load_op     = prism::LoadOp::Clear,
            .store_op    = prism::StoreOp::Store,
            .clear_value = {0.0f, 0.0f, 0.0f, 1.0f},
        },
    };

    auto render_pass = ctx.begin_render_pass(
        prism::RenderPassDescriptor{
            .color_attachment_count = std::size(color_attachments),
            .color_attachments      = color_attachments,
        },
        width, height);
    ctx.set_pipeline(render_pass, render_pipeline);
    ctx.draw(render_pass, 3);
    ctx.end_render_pass(render_pass);

    ctx.present_frame();
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
