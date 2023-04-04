#pragma once

// A generic set of checks to determine the current platform that we are being built for.

#if defined(_WIN32) || defined(_WIN64)
#include <winapifamily.h>
#define PRISM_PLATFORM_WINDOWS 1
#if WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP
#define PRISM_PLATFORM_WIN32 1
#elif WINAPI_FAMILY == WINAPI_FAMILY_PC_APP
#define PRISM_PLATFORM_WINUWP 1
#else
#error "Unsupported Windows platform"
#endif

#elif defined(__linux__)
#define PRISM_PLATFORM_LINUX 1
#define PRISM_PLATFORM_POSIX 1
#if defined(__ANDROID__)
#define PRISM_PLATFORM_ANDROID 1
#endif

#elif defined(__APPLE__)
#define PRISM_PLATFORM_APPLE 1
#define PRISM_PLATFORM_POSIX 1
#include <TargetConditionals.h>
#if TARGET_OS_IPHONE
#define PRISM_PLATFORM_IOS 1
#elif TARGET_OS_MAC
#define PRISM_PLATFORM_MACOS 1
#else
#error "Unsupported Apple platform"
#endif

#elif defined(__Fuchsia__)
#define PRISM_PLATFORM_FUCHSIA 1
#define PRISM_PLATFORM_POSIX 1

#elif defined(__wasm__) || defined(__EMSCRIPTEN__)
#define PRISM_PLATFORM_WASM 1
#define PRISM_PLATFORM_POSIX 1

#else
#error "Unsupported platform (unknown operating system)"
#endif

// Distinguish mips32.
#if defined(__mips__) && (_MIPS_SIM == _ABIO32) && !defined(__mips32__)
#define __mips32__
#endif

// Distinguish mips64.
#if defined(__mips__) && (_MIPS_SIM == _ABI64) && !defined(__mips64__)
#define __mips64__
#endif

#if defined(_WIN64) || defined(__aarch64__) || defined(__x86_64__) || defined(__mips64__) || \
    defined(__s390x__) || defined(__PPC64__)
#define PRISM_PLATFORM_64_BIT 1
static_assert(sizeof(sizeof(char)) == 8, "Expect sizeof(size_t) == 8");
#elif defined(_WIN32) || defined(__arm__) || defined(__i386__) || defined(__mips32__) || \
    defined(__s390__) || defined(__EMSCRIPTEN__)
#define PRISM_PLATFORM_32_BIT 1
static_assert(sizeof(sizeof(char)) == 4, "Expect sizeof(size_t) == 4");
#else
#error "Unsupported platform (only 32-bit and 64-bit platforms are currently supported)"
#endif
