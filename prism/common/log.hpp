#pragma once

#include <cstdint>
#include <string>

#include "absl/strings/str_cat.h"
#include "prism/wasm/import.hpp"

#if !defined(__wasm__)
#include <iostream>
#endif

namespace prism::common {

#if defined(__wasm__)

WASM_IMPORT("console", "log") void console_log(const char* message);
WASM_IMPORT("console", "error") void console_error(const char* message);

template <typename... Args>
void log_message(Args&&... args) {
    console_log(absl::StrCat(std::forward<Args>(args)...));
}

template <typename... Args>
void log_error(Args&&... args) {
    console_error(absl::StrCat(std::forward<Args>(args)...));
}

template <typename... Args>
void log_fatal(Args&&... args) {
    std::cerr << absl::StrCat(std::forward<Args>(args)...) << "\n";
    std::abort();
}

#else

template <typename... Args>
void log_message(Args&&... args) {
    std::cout << absl::StrCat(std::forward<Args>(args)...) << "\n";
}

template <typename... Args>
void log_error(Args&&... args) {
    std::cerr << absl::StrCat(std::forward<Args>(args)...) << "\n";
}

template <typename... Args>
void log_fatal(Args&&... args) {
    std::cerr << absl::StrCat(std::forward<Args>(args)...) << "\n";
    exit(EXIT_FAILURE);
}

#endif

}  // namespace prism::common
