#pragma once
#include <unordered_map>
#include <string>

#include "http/Configuration.h"

namespace http {

    class ApplicationConfiguration final : public IConfiguration {
    public:
        ApplicationConfiguration();
        ~ApplicationConfiguration() override = default;

        void set(std::string key, int value) override;
        void set(std::string key, std::string value) override;

        bool tryGet_int(std::string key, int *out) override;
        bool tryGet_str(std::string key, std::string *out) override;

    private:
        std::unordered_map<std::string, int> m_int_sections;
        std::unordered_map<std::string, std::string> m_str_sections;
    };

}
