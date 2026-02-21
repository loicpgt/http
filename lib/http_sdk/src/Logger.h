#ifndef HTTP_LOGGER_H
#define HTTP_LOGGER_H

#include "kernel.h"

#define LOG_LEVEL 0

namespace http {
    class Logger final {
    public:
        static void write_log(ApplicationLogLevel level, const char* file_name, short line_number, const char* fmt, ...);
    };
}

#endif //HTTP_LOGGER_H