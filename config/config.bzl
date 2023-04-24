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
