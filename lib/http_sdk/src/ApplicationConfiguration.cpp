#include "ApplicationConfiguration.h"

#include <ranges>

#include "core/kernel.h"

namespace http {
    http::ApplicationConfiguration::ApplicationConfiguration()
    {
        m_int_sections.reserve(10);
        m_str_sections.reserve(10);
    }

    void ApplicationConfiguration::set(std::string key, int value) {
        const auto it = m_int_sections.find(key);

        if (it != m_int_sections.end()) {
            if (it->second == value) {
                PANIC("Can't push the same configuration multiple times");
            }
            it->second = value;
            return;
        }

        m_int_sections.emplace(std::move(key), value);
    }

    void ApplicationConfiguration::set(std::string key, std::string value) {
        const auto it = m_str_sections.find(key);

        if (it != m_str_sections.end()) {
            if (it->second == value) {
                PANIC("Can't push the same configuration multiple times");
            }
            it->second = std::move(value);
            return;
        }

        m_str_sections.emplace(std::move(key), std::move(value));
    }

    bool ApplicationConfiguration::tryGet_int(std::string key, int *out) {
        const auto it = m_int_sections.find(key);

        if (it != m_int_sections.end()) {
            if (out != nullptr) {
                *out = it->second;
            }
            return true;
        }

        return false;
    }

    bool ApplicationConfiguration::tryGet_str(std::string key, std::string *out) {
        const auto it = m_str_sections.find(key);

        if (it != m_str_sections.end()) {
            if (out != nullptr) {
                *out = it->second;
            }
            return true;
        }

        return false;
    }
}
