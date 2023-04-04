cc_library(
    name = "glm",
    hdrs = glob([
        "glm/*.hpp",
        "glm/**/*.hpp",
        "glm/**/*.h",
    ]),
    copts = select({
        "@platforms//os:windows": [],  # TODO: Find windows equivalent
        "//conditions:default": ["-Wno-deprecated-volatile"],
    }),
    defines = ["GLM_FORCE_DEPTH_ZERO_TO_ONE=1"],
    includes = ["glm"],
    textual_hdrs = glob(["glm/**/*.inl"]),
    visibility = ["//visibility:public"],
)
