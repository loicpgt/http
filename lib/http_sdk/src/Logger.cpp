#include "Logger.h"

#include <cstdarg>
#include <cstdio>
#include <string>
#include <vector>
#include <sstream>

std::string clean_file_name(const char* file_name) {
    std::vector<std::string> tokens;
    std::stringstream ss(file_name);
    std::string token;

    while (std::getline(ss, token, '/')) {
        tokens.push_back(token);
    }

    return tokens.back();
}

void http::Logger::write_log(const ApplicationLogLevel level, const char *file_name, const short line_number, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    // Buffer pour le message formaté
    char message[1024];
    vsnprintf(message, sizeof(message), fmt, args);

    va_end(args);

    const std::string cleaned_file_name = clean_file_name(file_name);

    switch (level) {

#if LOG_LEVEL < 1
        case ApplicationLogLevel::TRACE_LEVEL:
            std::printf("[\x1b[34mTRACE\x1b[0m] %s:%d \n\t %s\n\n",
                        cleaned_file_name.c_str(), line_number, message);
            break;
#endif

#if LOG_LEVEL <= 1
        case ApplicationLogLevel::INFO_LEVEL:
            std::printf("[\x1b[32mINFO\x1b[0m] %s:%d \n\t %s\n\n",
                        cleaned_file_name.c_str(), line_number, message);
            break;
#endif

#if LOG_LEVEL <= 2
        case ApplicationLogLevel::DEBUG_LEVEL:
            std::printf("[\x1b[36mDEBUG\x1b[0m] %s:%d \n\t %s\n\n",
                        cleaned_file_name.c_str(), line_number, message);
            break;
#endif

#if LOG_LEVEL <= 3
        case ApplicationLogLevel::WARNING_LEVEL:
            std::printf("[\x1b[33mWARNING\x1b[0m] %s:%d \n\t %s\n\n",
                        cleaned_file_name.c_str(), line_number, message);
            break;
#endif

#if LOG_LEVEL <= 4
        case ApplicationLogLevel::ERROR_LEVEL:
            std::printf("[\x1b[31mERROR\x1b[0m] %s:%d \n\t %s\n\n",
                        cleaned_file_name.c_str(), line_number, message);
            break;
#endif

#if LOG_LEVEL <= 5
        case ApplicationLogLevel::PANIC_LEVEL:
            std::printf("[\x1b[31mPANIC\x1b[0m] %s:%d \n\t %s\n\n",
                        cleaned_file_name.c_str(), line_number, message);
            break;
#endif

        // The default switch case is used for ignored log levels
        default:
            break;
    }
}
