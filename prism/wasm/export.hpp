#pragma once

#if defined(__wasm__)

#define WASM_EXPORT($name) __attribute__((export_name(#$name)))

#else

#define WASM_EXPORT($name)

#endif
