#include "Logger.h"

#include <cstdarg>
#include <cstdio>
#include <string>
#include <vector>
#include <sstream>

void kernel_panic(const char *file_name, int line_number, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    http::Logger::write_log(ApplicationLogLevel::PANIC_LEVEL, file_name, line_number, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

void kernel_log(const int level, const char *file_name, int line_number, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    http::Logger::write_log(static_cast<ApplicationLogLevel>(level), file_name, line_number, fmt, args);
    va_end(args);
}

std::string clean_file_name(const char *file_name) {
    std::vector<std::string> tokens;
    std::stringstream ss(file_name);
    std::string token;

    while (std::getline(ss, token, '/')) {
        tokens.push_back(token);
    }

    return tokens.back();
}

void http::Logger::write_log(const ApplicationLogLevel level, const char *file_name, const int line_number,
                             const char *fmt, va_list args) {
#if LOG_LEVEL != 0
    if (level < static_cast<ApplicationLogLevel>(LOG_LEVEL)) return;
#endif

    char message[1024];
    vsnprintf(message, sizeof(message), fmt, args);

    const std::string cleaned_file_name = clean_file_name(file_name);

    switch (level) {
        case ApplicationLogLevel::TRACE_LEVEL:
            std::printf("[\x1b[34mTRACE\x1b[0m] %s:%d\n\t %s\n",
                        cleaned_file_name.c_str(), line_number, message);
            break;
        case ApplicationLogLevel::INFO_LEVEL:
            std::printf("[\x1b[32mINFO\x1b[0m] %s:%d\n\t %s\n",
                        cleaned_file_name.c_str(), line_number, message);
            break;
        case ApplicationLogLevel::DEBUG_LEVEL:
            std::printf("[\x1b[36mDEBUG\x1b[0m] %s:%d\n\t %s\n",
                        cleaned_file_name.c_str(), line_number, message);
            break;
        case ApplicationLogLevel::WARNING_LEVEL:
            std::printf("[\x1b[33mWARNING\x1b[0m] %s:%d\n\t %s\n",
                        cleaned_file_name.c_str(), line_number, message);
            break;
        case ApplicationLogLevel::ERROR_LEVEL:
            std::fprintf(stderr, "[\x1b[31mERROR\x1b[0m] %s:%d\n\t %s\n",
                         cleaned_file_name.c_str(), line_number, message);
            break;
        case ApplicationLogLevel::PANIC_LEVEL:
            std::fprintf(stderr, "[\x1b[31mPANIC\x1b[0m] %s:%d\n\t %s\n",
                         cleaned_file_name.c_str(), line_number, message);
            break;

        // The default switch case is used for ignored log levels
        default:
            break;
    }
}
