load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def prism_dependencies():
    _SKYLIB_VERSION = "1.2.1"
    maybe(
        http_archive,
        name = "bazel_skylib",
        sha256 = "710c2ca4b4d46250cdce2bf8f5aa76ea1f0cba514ab368f2988f70e864cfaf51",
        strip_prefix = "bazel-skylib-{version}".format(version = _SKYLIB_VERSION),
        url = "https://github.com/bazelbuild/bazel-skylib/archive/refs/tags/{version}.tar.gz".format(version = _SKYLIB_VERSION),
    )

    # Abseil does not handle being compiled with one version of C++ and linked to another very well.
    # Instead of using the default version of Abseil, we use a fork that has been modified to force
    # it to be compiled with C++20. Otherwise, it is identical to the upstream version,
    # "LTS version 20230125.3".

    # _ABSEIL_VERSION = "20230125.3"
    # maybe(
    #     http_archive,
    #     name = "com_google_absl",
    #     sha256 = "5366d7e7fa7ba0d915014d387b66d0d002c03236448e1ba9ef98122c13b35c36",
    #     strip_prefix = "abseil-cpp-{version}".format(version = _ABSEIL_VERSION),
    #     url = "https://github.com/abseil/abseil-cpp/archive/refs/tags/{version}.tar.gz".format(version = _ABSEIL_VERSION),
    # )
    _ABSEIL_COMMIT = "b71ebb2d41e68936b58f6fc1d4ade961891019be"
    maybe(
        http_archive,
        name = "com_google_absl",
        sha256 = "7693018c675120fcda0d9c9afed8f3bff309815880858a28bdbfd56d2977b47b",
        strip_prefix = "abseil-cpp-{commit}".format(commit = _ABSEIL_COMMIT),
        url = "https://github.com/nullcatalyst/abseil-cpp/archive/{commit}.tar.gz".format(commit = _ABSEIL_COMMIT),
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

    _QOI_COMMIT = "f6dffaf1e8170cdd79945a4fb60f6403e447e020"
    maybe(
        http_archive,
        name = "com_phoboslab_qoi",
        build_file = "//third_party/qoi:qoi.BUILD",
        sha256 = "946ed7adb128ed12924c83cf89717d37e9059353d327b5f6bf778413351f7907",
        strip_prefix = "qoi-{commit}".format(commit = _QOI_COMMIT),
        url = "https://github.com/phoboslab/qoi/archive/{commit}.tar.gz".format(commit = _QOI_COMMIT),
    )

    _STB_COMMIT = "5736b15f7ea0ffb08dd38af21067c314d6a3aae9"
    maybe(
        http_archive,
        name = "com_github_nothings_stb",
        build_file = "//third_party/stb:stb.BUILD",
        sha256 = "d00921d49b06af62aa6bfb97c1b136bec661dd11dd4eecbcb0da1f6da7cedb4c",
        strip_prefix = "stb-{commit}".format(commit = _STB_COMMIT),
        url = "https://github.com/nothings/stb/archive/{commit}.tar.gz".format(commit = _STB_COMMIT),
    )

def prism_wasm_dependencies():
    _BAZEL_LIB_VERSION = "1.32.1"
    maybe(
        http_archive,
        name = "aspect_bazel_lib",
        sha256 = "e3151d87910f69cf1fc88755392d7c878034a69d6499b287bcfc00b1cf9bb415",
        strip_prefix = "bazel-lib-{version}".format(version = _BAZEL_LIB_VERSION),
        url = "https://github.com/aspect-build/bazel-lib/archive/refs/tags/v{version}.tar.gz".format(version = _BAZEL_LIB_VERSION),
    )

    _JS_RULES_VERSION = "1.28.0"
    maybe(
        http_archive,
        name = "aspect_rules_js",
        sha256 = "2a88d837f8fb7bfe46b1d9f413df9a777ec2973e1f812929b597c1971a3a1da5",
        strip_prefix = "rules_js-{version}".format(version = _JS_RULES_VERSION),
        url = "https://github.com/aspect-build/rules_js/archive/refs/tags/v{version}.tar.gz".format(version = _JS_RULES_VERSION),
    )

    _NODEJS_RULES_VERSION = "5.8.3"
    maybe(
        http_archive,
        name = "rules_nodejs",
        strip_prefix = "rules_nodejs-{version}".format(version = _NODEJS_RULES_VERSION),
        sha256 = "53305bf2d5084ffc8d4d92d28c7db3447a4cc44922721492de909b3d27d733a2",
        url = "https://github.com/bazelbuild/rules_nodejs/archive/refs/tags/{version}.tar.gz".format(version = _NODEJS_RULES_VERSION),
    )

    _TS_RULES_VERSION = "1.4.2"
    maybe(
        http_archive,
        name = "aspect_rules_ts",
        sha256 = "40ab6d3d9cc3259da54fe2f162588aba92244af0f151fbc905dcc8e7b8744296",
        strip_prefix = "rules_ts-{version}".format(version = _TS_RULES_VERSION),
        url = "https://github.com/aspect-build/rules_ts/archive/refs/tags/v{version}.tar.gz".format(version = _TS_RULES_VERSION),
    )

    _ROLLUP_RULES_VERSION = "0.15.0"
    maybe(
        http_archive,
        name = "aspect_rules_rollup",
        sha256 = "55aec79b04d84b489895ac6f57a7ed7e4a1ef94dc4680701634463dd1720802d",
        strip_prefix = "rules_rollup-{}".format(_ROLLUP_RULES_VERSION),
        url = "https://github.com/aspect-build/rules_rollup/archive/refs/tags/v{}.tar.gz".format(_ROLLUP_RULES_VERSION),
    )

    _TERSER_RULES_VERSION = "0.14.1"
    maybe(
        http_archive,
        name = "aspect_rules_terser",
        sha256 = "f30ec7ceff6a01deaf68e501233eba01a339a8d305376706a31de4201d7a260b",
        strip_prefix = "rules_terser-{version}".format(version = _TERSER_RULES_VERSION),
        url = "https://github.com/aspect-build/rules_terser/archive/refs/tags/v{version}.tar.gz".format(version = _TERSER_RULES_VERSION),
    )
