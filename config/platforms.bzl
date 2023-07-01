# import selects
# load("@bazel_tools//tools/build_defs/selects:selects.bzl", "selects")

def select_platform(windows = None, linux = None, macos = None, ios = None, wasm = None):
    return select({
        # Forced targets
        "@com_nullcatalyst_prism//config:platform_windows": windows,
        "@com_nullcatalyst_prism//config:platform_macos": macos,
        "@com_nullcatalyst_prism//config:platform_linux": linux,
        "@com_nullcatalyst_prism//config:platform_ios": ios,
        "@com_nullcatalyst_prism//config:platform_wasm": wasm,
        # Implicit targets
        "@platforms//os:windows": windows,
        "@platforms//os:linux": linux,
        "@platforms//os:macos": macos,
        "@platforms//os:ios": ios,
        # Fallback
        "//conditions:default": [],
    })
