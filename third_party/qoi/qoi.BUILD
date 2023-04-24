load("@bazel_skylib//rules:write_file.bzl", "write_file")

cc_library(
    name = "qoi",
    srcs = [":qoi_impl.cpp"],
    hdrs = ["qoi.h"],
    visibility = ["//visibility:public"],
)

write_file(
    name = "qoi_impl",
    out = "qoi_impl.cpp",
    content = [
        "#define QOI_IMPLEMENTATION",
        "#include \"qoi.h\"",
    ],
)

cc_binary(
    name = "converter",
    srcs = ["qoiconv.c"],
    visibility = ["//visibility:public"],
    deps = [
        ":qoi",
        "@com_github_nothings_stb//:image",
        "@com_github_nothings_stb//:image_write",
    ],
)
