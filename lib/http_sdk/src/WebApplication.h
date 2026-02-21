#ifndef HTTP_WEBAPPLICATION_H
#define HTTP_WEBAPPLICATION_H
#include "Application.h"


namespace http {
    class WebApplication final : public IApplication {
        int m_port;

    public:
        explicit WebApplication(int port);

        ~WebApplication() override;

        void run() override;
        void quit() override;

    private:
        int m_must_stop = 0;
    };
} // http

#endif //HTTP_WEBAPPLICATION_H
