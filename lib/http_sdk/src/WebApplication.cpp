#include "http/WebApplication.h"

#include <cstring>

#include "ApplicationConfiguration.h"
#include "core/http.h"
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
        http_context_t* context = init_context(message);

        if (std::strcmp(context->request.path, "/") == 0) {
            context->response.status = OK;
            header_map_push(&context->response.headers, "Content-Type", "text/html");

            FILE* file = fopen("/www/index.html", "r");
            char line[256];
            while (fgets(line, sizeof(line), file)) {
                strcat(context->response.message, line);
            }

            char resp_str[5024];
            http_request_to_string(reinterpret_cast<char *>(&resp_str), &context->response);
            respond_to(message, resp_str);
        }

        free(context);
    }
} // http
