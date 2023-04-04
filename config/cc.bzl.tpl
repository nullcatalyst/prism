"""
Custom C/C++ helpers

This is used to allow the end user to inject custom flags without having to customize the contents
of this bazel module.
"""

_COPTS    = [%{copts}]
_LINKOPTS = [%{linkopts}]

def prism_cc_binary(name, copts = [], linkopts = [], **kwargs):
    """
    Compile a C/C++ binary target

    This adds additional C/C++ flags and linker flags to the default
    """
    native.cc_binary(
        name = name,
        copts = copts + _COPTS,
        linkopts = linkopts + _LINKOPTS,
        **kwargs
    )

def prism_cc_library(name, copts = [], linkopts = [], **kwargs):
    """
    Compile a C/C++ library target

    This adds additional C/C++ flags and linker flags to the default
    """
    native.cc_library(
        name = name,
        copts = copts + _COPTS,
        linkopts = linkopts + _LINKOPTS,
        **kwargs
    )

def prism_cc_test(name, copts = [], linkopts = [], **kwargs):
    """
    Compile a C/C++ test target

    This adds additional C/C++ flags and linker flags to the default
    """
    native.cc_test(
        name = name,
        copts = copts + _COPTS,
        linkopts = linkopts + _LINKOPTS,
        **kwargs
    )

def prism_objc_library(name, copts = [], linkopts = [], **kwargs):
    """
    Compile a ObjC/ObjC++ library target

    This adds additional ObjC/ObjC++ flags and linker flags to the default
    """
    native.objc_library(
        name = name,
        copts = copts + _COPTS,
        linkopts = linkopts + _LINKOPTS,
        **kwargs
    )
