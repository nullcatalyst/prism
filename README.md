# prism

## About

Prism is a thin graphics library that makes it easy to use webgpu graphics for both native and
browser based applications.

By default, prism uses the SDL2 and WGPU libraries internally. Though, changing to use other
implementations under the hood, like GLFW or Dawn, should not be too difficult.

## Building

Prism uses [bazel](https://bazel.build/) to manage dependencies and to compile the library. There
are plenty of better tutorials on how to install bazel, so that won't be included here.

#### Running the hello_triangle example

If you are starting with a terminal pointing to the prism directory, then you can start by `cd`ing
into the `examples` directory.

```sh
cd examples
```

Tell `bazel` which target you want to run. Note that you need to pass `--config macos` or your
current OS name (eg: `--config windows`, `--config linux`, or `--config wasm`). This is needed
because there is no way to autodetect that you are intending to compile for WebAssembly, and
auto-detecting the current platform is on the TODO list.

```sh
bazel run //hello_triangle --config macos
```

And that's it. There is no step 3. Your game should be running, and you should see a window appear
that is rendering a static RGB triangle.
