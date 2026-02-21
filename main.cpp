#include <iostream>

#include "Application.h"

int main() {
    std::unique_ptr<http::IApplication> app = http::create(8080);
    app->run();

    app.reset();
    return 0;
}
