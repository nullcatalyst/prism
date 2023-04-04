cc_library(
    name = "qoi",
    srcs = ["@//third_party/qoi:impl.cpp"],
    hdrs = ["qoi.h"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "converter",
    srcs = ["qoiconv.c"],
    visibility = ["//visibility:public"],
    deps = [
        ":qoi",
        "@//third_party/stb:image",
        "@//third_party/stb:image_write",
    ],
)
