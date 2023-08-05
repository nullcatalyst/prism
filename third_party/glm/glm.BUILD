cc_library(
    name = "glm",
    hdrs = glob([
        "glm/*.hpp",
        "glm/**/*.hpp",
        "glm/**/*.h",
    ]),
    copts = select({
        "@platforms//os:windows": [],  # TODO: Find windows equivalent of -Wno-deprecated-volatile
        "//conditions:default": ["-Wno-deprecated-volatile"],
    }),
    defines = [
        # "GLM_FORCE_ALIGNED_GENTYPES",
        "GLM_FORCE_DEPTH_ZERO_TO_ONE",
        "GLM_FORCE_INTRINSICS",
        "GLM_FORCE_SILENT_WARNINGS",
    ],
    includes = ["glm"],
    textual_hdrs = glob(["glm/**/*.inl"]),
    visibility = ["//visibility:public"],
)
