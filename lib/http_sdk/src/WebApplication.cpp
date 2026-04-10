#include "http/WebApplication.h"

#include "ApplicationConfiguration.h"
#include "core/net/socket.h"

namespace http {
    WebApplication::WebApplication(const WebApplicationSpecification &specification) {
        this->m_port = specification.port;
        this->m_pConfiguration = std::make_shared<ApplicationConfiguration>();
    }

    WebApplication::~WebApplication() {
        m_port = 0;
    }

    void WebApplication::run() const {
        network_message_queue_t *queue = init_message_queue(5);
        network_socket_t *socket = bind_network_socket(m_port);

        listen_on_network_socket(socket, queue);
        network_message_t *message = get_next_message(queue);

        respond_to(message, "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body>Hello World!</body></html>");
    }
} // http
