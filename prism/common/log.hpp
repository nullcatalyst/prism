#pragma once

#include <cstdint>
#include <string>

#include "absl/strings/str_cat.h"
#include "prism/wasm/import.hpp"

#if !defined(__wasm__)
#include <iostream>
#endif

namespace prism::common {

template <typename... Args>
void log_message(Args&&... args) {
    log_message<>(absl::StrCat(std::forward<Args>(args)...));
}

template <typename... Args>
void log_error(Args&&... args) {
    log_error<>(absl::StrCat(std::forward<Args>(args)...));
}

#if defined(__wasm__)

WASM_IMPORT("console", "log") void console_log(const char* message);
WASM_IMPORT("console", "error") void console_error(const char* message);

template <>
void log_message(const std::string& message) {
    console_log(message.c_str());
}

template <>
void log_error(const std::string& message) {
    console_error(message.c_str());
}

#else

template <>
void log_message(const std::string& message) {
    std::cout << message.c_str() << "\n";
}

template <>
void log_error(const std::string& message) {
    std::cerr << message.c_str() << "\n";
}

#endif

}  // namespace prism::common
