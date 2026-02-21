#ifndef HTTP_APPLICATION_H
#define HTTP_APPLICATION_H

#include <memory>

namespace http {
    /// @brief Represents an <b>Application</b> that can be started and managed
    class IApplication {
    public:
        virtual ~IApplication() = default;

        /// @brief Starts the application and handles the app loop
        virtual void run() = 0;

        /// @brief Raises a flag to stop the application at the end of the current loop
        virtual void quit() = 0;
    };

    std::unique_ptr<IApplication> create(int port);
}

#endif //HTTP_APPLICATION_H
