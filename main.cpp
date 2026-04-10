#include "WebApplication.h"

int main() {
    http::WebApplicationSpecification application_specification;

    const auto application = std::make_unique<http::WebApplication>(application_specification);
    application->run();
    return 0;
}
