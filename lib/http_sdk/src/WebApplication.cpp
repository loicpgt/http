#include "WebApplication.h"
#include "Logger.h"

#include <memory>

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
