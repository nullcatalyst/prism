"""
Custom C/C++ helpers

This is used to allow the end user to inject custom flags without having to customize the contents
of this bazel module.
"""

load("@com_nullcatalyst_prism//config:platforms.bzl", "select_platform")

_COPTS = [
    "-std=c++20",  # Use C++20
    "-fno-rtti",  # Disable RTTI
    "-fno-exceptions",  # Disable exceptions
]
_LINKOPTS = [
    "-flto",  # Link time optimization
]

_WINDOWS_COPTS = [
    "/std:c++20",  # Use C++20
    "/GL",  # Whole program optimization
]
_WINDOWS_LINKOPTS = [
    "/LTCG",  # Link time code generation
]

def prism_cc_binary(name, copts = [], linkopts = [], **kwargs):
    """
    Compile a C/C++ binary target

    This adds additional C/C++ flags and linker flags to the default
    """
    native.cc_binary(
        name = name,
        copts = copts + select_platform(
            ios = _COPTS,
            linux = _COPTS,
            macos = _COPTS,
            wasm = _COPTS,
            windows = _WINDOWS_COPTS,
        ),
        linkopts = linkopts + select_platform(
            ios = _LINKOPTS,
            linux = _LINKOPTS,
            macos = _LINKOPTS,
            wasm = _LINKOPTS,
            windows = _WINDOWS_LINKOPTS,
        ),
        **kwargs
    )

def prism_cc_library(name, copts = [], linkopts = [], **kwargs):
    """
    Compile a C/C++ library target

    This adds additional C/C++ flags and linker flags to the default
    """
    native.cc_library(
        name = name,
        copts = copts + select_platform(
            ios = _COPTS,
            linux = _COPTS,
            macos = _COPTS,
            wasm = _COPTS,
            windows = _WINDOWS_COPTS,
        ),
        linkopts = linkopts + select_platform(
            ios = _LINKOPTS,
            linux = _LINKOPTS,
            macos = _LINKOPTS,
            wasm = _LINKOPTS,
            windows = _WINDOWS_LINKOPTS,
        ),
        **kwargs
    )

def prism_cc_test(name, copts = [], linkopts = [], **kwargs):
    """
    Compile a C/C++ test target

    This adds additional C/C++ flags and linker flags to the default
    """
    native.cc_test(
        name = name,
        copts = copts + select_platform(
            ios = _COPTS,
            linux = _COPTS,
            macos = _COPTS,
            wasm = _COPTS,
            windows = _WINDOWS_COPTS,
        ),
        linkopts = linkopts + select_platform(
            ios = _LINKOPTS,
            linux = _LINKOPTS,
            macos = _LINKOPTS,
            wasm = _LINKOPTS,
            windows = _WINDOWS_LINKOPTS,
        ),
        **kwargs
    )

def prism_objc_library(name, copts = [], linkopts = [], **kwargs):
    """
    Compile a ObjC/ObjC++ library target

    This adds additional ObjC/ObjC++ flags and linker flags to the default
    """
    native.objc_library(
        name = name,
        copts = copts + select_platform(
            ios = _COPTS,
            linux = _COPTS,
            macos = _COPTS,
            wasm = _COPTS,
            windows = _WINDOWS_COPTS,
        ),
        linkopts = linkopts + select_platform(
            ios = _LINKOPTS,
            linux = _LINKOPTS,
            macos = _LINKOPTS,
            wasm = _LINKOPTS,
            windows = _WINDOWS_LINKOPTS,
        ),
        **kwargs
    )
