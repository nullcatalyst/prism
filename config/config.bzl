load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def _prism_config_impl(ctx):
    ctx.file("WORKSPACE.bazel", 'workspace(name = "{}")\n'.format(ctx.name))

    # An empty BUILD file is required to make the repository a package
    ctx.file("BUILD.bazel", "")

    ctx.template(
        "cc.bzl",
        ctx.attr._cc_tpl,
        {
            "%{copts}": " ".join(["\"" + flag + "\"," for flag in ctx.attr.copts]),
            "%{linkopts}": " ".join(["\"" + flag + "\"," for flag in ctx.attr.linkopts]),
        },
    )

    ctx.template(
        "platforms.bzl",
        ctx.attr._platforms_tpl,
        {
            "%{window_condition}": ctx.attr.window_condition,
            "%{macos_condition}": ctx.attr.macos_condition,
            "%{ios_condition}": ctx.attr.ios_condition,
            "%{linux_condition}": ctx.attr.linux_condition,
            "%{wasm_condition}": ctx.attr.wasm_condition,
        },
    )

_prism_config = repository_rule(
    attrs = {
        "copts": attr.string_list(),
        "linkopts": attr.string_list(),
        "_cc_tpl": attr.label(
            default = Label("@com_nullcatalyst_prism//config:cc.bzl.tpl"),
            allow_single_file = True,
        ),
        # Conditions for platform specific compilation.
        # Normally, @platforms//os:windows, @platforms//os:macos, etc. would be used, but there is
        # no viable option for wasm, so we require passing the --define platform=windows,
        # --define platform=macos, etc. flag.
        "window_condition": attr.string(default = "@com_nullcatalyst_prism//config:platform_windows"),
        "macos_condition": attr.string(default = "@com_nullcatalyst_prism//config:platform_macos"),
        "ios_condition": attr.string(default = "@com_nullcatalyst_prism//config:platform_ios"),
        "linux_condition": attr.string(default = "@com_nullcatalyst_prism//config:platform_linux"),
        "wasm_condition": attr.string(default = "@com_nullcatalyst_prism//config:platform_wasm"),
        "_platforms_tpl": attr.label(
            default = Label("@com_nullcatalyst_prism//config:platforms.bzl.tpl"),
            allow_single_file = True,
        ),
    },
    implementation = _prism_config_impl,
)

def prism_config(copts = [], linkopts = []):
    _prism_config(
        name = "prism_config",
        copts = copts,
        linkopts = linkopts,
    )

def prism_dependencies():
    _ABSEIL_VERSION = "20211102.0"
    maybe(
        http_archive,
        name = "com_google_absl",
        sha256 = "dcf71b9cba8dc0ca9940c4b316a0c796be8fab42b070bb6b7cab62b48f0e66c4",
        strip_prefix = "abseil-cpp-{version}".format(version = _ABSEIL_VERSION),
        url = "https://github.com/abseil/abseil-cpp/archive/refs/tags/{version}.tar.gz".format(version = _ABSEIL_VERSION),
    )

    _RE2_VERSION = "2022-06-01"
    maybe(
        http_archive,
        name = "com_googlesource_code_re2",
        sha256 = "f89c61410a072e5cbcf8c27e3a778da7d6fd2f2b5b1445cd4f4508bee946ab0f",
        strip_prefix = "re2-{version}".format(version = _RE2_VERSION),
        url = "https://github.com/google/re2/archive/refs/tags/{version}.tar.gz".format(version = _RE2_VERSION),
    )

    _GTEST_VERSION = "release-1.11.0"
    maybe(
        http_archive,
        name = "com_google_googletest",
        sha256 = "b4870bf121ff7795ba20d20bcdd8627b8e088f2d1dab299a031c1034eddc93d5",
        strip_prefix = "googletest-{version}".format(version = _GTEST_VERSION),
        url = "https://github.com/google/googletest/archive/refs/tags/{version}.tar.gz".format(version = _GTEST_VERSION),
    )

    _WGPU_VERSION = "0.15.1.2"
    maybe(
        http_archive,
        name = "com_github_gfxrs_wgpu",
        sha256 = "379e83da9cb2a755e5a48fcf2551e891d19c71af582d2116d7e8ad8b83db3d01",
        strip_prefix = "wgpu-native-lib-{version}".format(version = _WGPU_VERSION),
        url = "https://github.com/nullcatalyst/wgpu-native-lib/archive/refs/tags/v{version}.tar.gz".format(version = _WGPU_VERSION),
    )

    _SDL2_VERSION = "2.26.3"
    maybe(
        http_archive,
        name = "org_libsdl_sdl2",
        build_file = "@com_nullcatalyst_prism//third_party/sdl2:sdl2.BUILD",
        sha256 = "af0ff86e4a268bc12c915a0ea19ea1a16419ab1426d92bad5f4e26eb31583967",
        strip_prefix = "SDL-release-{version}".format(version = _SDL2_VERSION),
        url = "https://github.com/libsdl-org/SDL/archive/refs/tags/release-{version}.tar.gz".format(version = _SDL2_VERSION),
    )

    _GLM_VERSION = "0.9.9.8"
    maybe(
        http_archive,
        name = "net_gtruc_glm",
        build_file = "@com_nullcatalyst_prism//third_party/glm:glm.BUILD",
        sha256 = "7d508ab72cb5d43227a3711420f06ff99b0a0cb63ee2f93631b162bfe1fe9592",
        strip_prefix = "glm-{version}".format(version = _GLM_VERSION),
        url = "https://github.com/g-truc/glm/archive/refs/tags/{version}.tar.gz".format(version = _GLM_VERSION),
    )

    _GLM_VERSION = "0.9.9.8"
    maybe(
        http_archive,
        name = "com_nullcatalyst_wasmtoolchain",
        sha256 = "7d508ab72cb5d43227a3711420f06ff99b0a0cb63ee2f93631b162bfe1fe9592",
        strip_prefix = "glm-{version}".format(version = _GLM_VERSION),
        url = "https://github.com/g-truc/glm/archive/refs/tags/{version}.tar.gz".format(version = _GLM_VERSION),
    )
