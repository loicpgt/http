#pragma once

#include <string>

namespace http {
    /**
 * @brief This interface represents a data structure used to store application
 * configuration elements such as connection strings, encryption keys, etc.
 *
 * It provides a generic key-value storage where values can be retrieved safely
 * using "tryGet" methods. Keys are unique within their respective type.
 */
class IConfiguration {
public:
    virtual ~IConfiguration() = default;

    /**
     * @brief Sets an integer value for the specified key.
     *
     * If the key already exists, its value is updated.
     *
     * @param key The key used to identify the configuration entry.
     * @param value The integer value to associate with the key.
     */
    virtual void set(std::string key, int value) = 0;

    /**
     * @brief Sets a string value for the specified key.
     *
     * If the key already exists, its value is updated.
     *
     * @param key The key used to identify the configuration entry.
     * @param value The string value to associate with the key.
     */
    virtual void set(std::string key, std::string value) = 0;

    /**
     * @brief Attempts to retrieve an integer value associated with the given key.
     *
     * @param key The key used to look up the configuration value.
     * @param out Pointer to an integer where the result will be stored if found.
     *            Can be nullptr if the caller only wants to check existence.
     *
     * @return true if the key exists and the value was found, false otherwise.
     */
    virtual bool tryGet_int(std::string key, int* out) = 0;

    /**
     * @brief Attempts to retrieve a string value associated with the given key.
     *
     * @param key The key used to look up the configuration value.
     * @param out Pointer to a string where the result will be stored if found.
     *            Can be nullptr if the caller only wants to check existence.
     *
     * @return true if the key exists and the value was found, false otherwise.
     */
    virtual bool tryGet_str(std::string key, std::string* out) = 0;
};

}