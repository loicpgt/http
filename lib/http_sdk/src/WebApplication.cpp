#include "WebApplication.h"

#include <memory>

#include "socket.h"

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
        network_message_queue_t* queue = init_message_queue(5);
        network_socket_t* socket = bind_network_socket(m_port);

        listen_on_network_socket(socket, queue);
        network_message_t* message = get_next_message(queue);

        respond_to(message, "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body>Hello World!</body></html>");
    }

    std::unique_ptr<IApplication> create(const int port) {
        return std::make_unique<WebApplication>(port);
    }
} // http
