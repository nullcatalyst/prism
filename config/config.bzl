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

_prism_config = repository_rule(
    attrs = {
        "copts": attr.string_list(),
        "linkopts": attr.string_list(),
        "_cc_tpl": attr.label(
            default = Label("@com_nullcatalyst_prism//config:cc.bzl.tpl"),
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
