#pragma once

#include <cstdarg>

#include "core/kernel.h"

#define LOG_LEVEL 0

namespace http {
    class Logger final {
    public:
        static void write_log(ApplicationLogLevel level, const char *file_name, int line_number, const char *fmt,
                              va_list args);
    };
}
