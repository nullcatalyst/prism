"""
Custom Platform Conditions

Normally, @platforms//os:windows, @platforms//os:macos, etc. would be used to determine the target
platform (and they can still be used by passing those values in to wasm_toolchain), but that would
mean that there is no way to select and build wasm.

So instead, we default to requiring the user pass the command line flags, --define platform=windows,
--define platform=macos, etc.
"""

WINDOWS_PLATFORM    = "%{window_condition}"
MACOS_PLATFORM      = "%{macos_condition}"
IOS_PLATFORM        = "%{ios_condition}"
LINUX_PLATFORM      = "%{linux_condition}"
WASM_PLATFORM       = "%{wasm_condition}"
