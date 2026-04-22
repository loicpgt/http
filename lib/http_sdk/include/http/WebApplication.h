#pragma once
#include <memory>

#include "Configuration.h"

namespace http {
    struct WebApplicationSpecification {
        int port = 8080;
        std::string www_root = "/www";
    };

    class WebApplication final {
    public:
        explicit WebApplication(const WebApplicationSpecification& specification);

        ~WebApplication();

        void run() const;

    private:
        int m_port;
        std::shared_ptr<IConfiguration> m_pConfiguration;
    };
}
