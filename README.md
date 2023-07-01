# Prism

## About

Prism is a thin graphics library that makes it easy to use webgpu graphics for both native and
browser based applications.

By default, prism uses the SDL2 and WGPU libraries internally. Though, changing to use other
implementations under the hood, like GLFW or Dawn, should not be too difficult.

## Building

Prism uses [bazel](https://bazel.build/) to manage dependencies and to compile the library. There
are plenty of better tutorials on how to install bazel, so that won't be included here.

### Running the hello_triangle example

If you are starting with a terminal pointing to the prism directory, then you can start by `cd`ing
into the `examples` directory.

```sh
cd examples
```

Tell `bazel` which target you want to run.

```sh
bazel run //hello_triangle
```

And that's it. There is no step 3. Your game should be running, and you should see a window appear
that is rendering a static RGB triangle.

Similarly, a web compatible application can be compiled using:

```sh
bazel build //hello_triangle:website --config wasm
```

This will build a zip file containing an HTML file, a javascript file, and the WebAssembly binary.
If instead all you need is the `.wasm` file, you can instead compile the same as running the app
natively (above). Just add the flag `--config wasm`.

```sh
bazel run //hello_triangle --config wasm
```
