load("@bazel_skylib//rules:write_file.bzl", "write_file")

cc_library(
    name = "image",
    srcs = [":stb_image_impl.cpp"],
    hdrs = ["stb_image.h"],
    includes = ["."],
    visibility = ["//visibility:public"],
)

write_file(
    name = "stb_image_impl",
    out = "stb_image_impl.cpp",
    content = [
        "#define STB_IMAGE_IMPLEMENTATION",
        "#include \"stb_image.h\"",
    ],
)

cc_library(
    name = "image_write",
    srcs = [":stb_image_write_impl.cpp"],
    hdrs = ["stb_image_write.h"],
    includes = ["."],
    visibility = ["//visibility:public"],
)

write_file(
    name = "stb_image_write_impl",
    out = "stb_image_write_impl.cpp",
    content = [
        "#define STB_IMAGE_WRITE_IMPLEMENTATION",
        "#include \"stb_image_write.h\"",
    ],
)
