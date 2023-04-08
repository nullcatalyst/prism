#pragma once

#include "prism/common/log.hpp"

#if !defined(NDEBUG)

#include <iostream>

#define PRISM_DEBUG_ASSERT_CONDITION($condition)                                    \
    do {                                                                            \
        if (!($condition)) {                                                        \
            ::prism::common::log_fatal(__FILE__, ":", __LINE__, ": ", #$condition); \
        }                                                                           \
    } while (0)

#define PRISM_DEBUG_RESULT($value) PRISM_DEBUG_ASSERT_CONDITION(($value) != nullptr)

#if defined(PRISM_BACKEND_DAWN)

// Even though we don't currently support the Dawn backend, this is the code that would be useful to
// have to debug it.

#define PRISM_DEBUG_SCOPE_START($device) \
    wgpuDevicePushErrorScope(($device), WGPUErrorFilter_Validation)

#define PRISM_DEBUG_SCOPE_END($device, $msg)                                               \
    wgpuDevicePopErrorScope(($device),                                                     \
                            [](WGPUErrorType type, char const* message, void* user_data) { \
                                if (message != nullptr && message[0] != '\0') {            \
                                    ::prism::common::log_error($msg, ":\n  ", message);    \
                                }                                                          \
                            },                                                             \
                            nullptr)

#else
#define PRISM_DEBUG_SCOPE_START($device)

#define PRISM_DEBUG_SCOPE_END($device, $msg)

#endif

#else

#define PRISM_DEBUG_ASSERT_CONDITION($condition)

#define PRISM_DEBUG_RESULT($value)

#define PRISM_DEBUG_SCOPE_START($device)

#define PRISM_DEBUG_SCOPE_END($device, $msg)

#endif
