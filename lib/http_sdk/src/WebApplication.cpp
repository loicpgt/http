#include "WebApplication.h"
#include "Logger.h"

#include <memory>

void kernel_log(int level, const char* file_name, short line_number, const char* fmt, ...) {
    http::Logger::write_log(static_cast<ApplicationLogLevel>(level), file_name, line_number, fmt);
}

void kernel_panic(const char* file_name, short line_number, const char* fmt, ...) {
    http::Logger::write_log(ApplicationLogLevel::PANIC_LEVEL, file_name, line_number, fmt);
    exit(EXIT_FAILURE);
}

namespace http {
    WebApplication::WebApplication(const int port) : m_port(port) {
    }

    WebApplication::~WebApplication() {
        m_port = 0;
    }

    void WebApplication::quit() {
        m_must_stop = 1;
    }

    void WebApplication::run() {
        LOG_TRACE("Test");
    }

    std::unique_ptr<IApplication> create(const int port) {
        return std::make_unique<WebApplication>(port);
    }
} // http
