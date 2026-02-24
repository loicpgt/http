/*
 * [2026-02-20] File created by loicpgt
 *
 *  Comments:
 *  [2025-02-20] - loicpgt: Using macros to get the file name and the line where the log is called from
 */

#ifndef HTTP_KERNEL_H
#define HTTP_KERNEL_H

#define PANIC(fmt, ...) kernel_panic(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_TRACE(fmt, ...) kernel_log(TRACE_LEVEL, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...) kernel_log(DEBUG_LEVEL, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) kernel_log(INFO_LEVEL, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) kernel_log(WARN_LEVEL, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) kernel_log(ERROR_LEVEL, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Log levels used by the application
 */
enum ApplicationLogLevel {
    TRACE_LEVEL = 0,
    DEBUG_LEVEL = 1,
    INFO_LEVEL = 2,
    WARNING_LEVEL = 3,
    ERROR_LEVEL = 4,
    PANIC_LEVEL = 5,
};

/**
 * @brief Writes the message in the configured application logs sink
* @param level The log level
 * @param file_name The file name where the log occurred
 * @param line_number The line number where the log occurred
 * @param fmt The log format
 * @param ... The log arguments
 */
void kernel_log(int level, const char* file_name, short line_number, const char* fmt, ...);

/**
 * @brief Represents an unhandled error
 * @param file_name The file name where the error occurred
 * @param line_number The line number where the error occurred
 * @param fmt The error message format
 * @param ... The error message arguments
 */
void kernel_panic(const char* file_name, short line_number, const char* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif //HTTP_KERNEL_H
