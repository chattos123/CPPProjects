/**
 * @file SConfigParser.h
 * @addtogroup Concurrency
 * @author Soumyajit C
 * @date 2026
 * @brief Shared key-value configuration file parser for Concurrency modules.
 * @namespace Concurrency::Common
 */

#pragma once

#ifdef _MSC_VER
    #pragma warning(push)
    #pragma warning(disable : 4251)
#endif

#include "ExportMacro.h"

#include <cstdint>
#include <string>
#include <unordered_map>

namespace Concurrency::Common
{

    /**
     * @struct STCPNodeConfig
     * @brief Holds parsed TCP node runtime settings ("server" or "client").
     */
    struct CONCURRENT_API STCPNodeConfig
    {
        std::string role = "client";    ///< Operating role: "server" or "client".
        std::string host = "127.0.0.1"; ///< Bind IP (server) or target server IP (client).
        std::uint16_t port = 54000;     ///< TCP port number.
    };

    /**
     * @class SConfigParser
     * @brief Parses key=value configuration files with '#' or ';' comments and whitespace trimming.
     */
    class CONCURRENT_API SConfigParser
    {
    public:
        /**
         * @brief Default constructor.
         */
        SConfigParser() = default;

        /**
         * @brief Loads and parses key=value pairs from a file on disk.
         * @param file_path Path to the configuration file (e.g., "config.ini").
         * @return true if the file was opened and parsed, false if opening failed.
         */
        bool load(const std::string &file_path);

        /**
         * @brief Retrieves a string value by key, or returns a fallback if absent.
         * @param key Configuration key name.
         * @param default_val Value returned when key is not found.
         * @return Matched string value or default_val.
         */
        std::string get_string(const std::string &key, const std::string &default_val = "") const;

        /**
         * @brief Retrieves an integer value by key, or returns a fallback if absent or non-numeric.
         * @param key Configuration key name.
         * @param default_val Value returned when key is missing or invalid.
         * @return Parsed integer or default_val.
         */
        int get_int(const std::string &key, int default_val = 0) const;

        /**
         * @brief Builds a typed STCPNodeConfig from the parsed values with validation.
         * @param[out] out_config Populated configuration struct on success.
         * @return true if role is "server" or "client" and port is in [1, 65535], false otherwise.
         */
        bool to_node_config(STCPNodeConfig &out_config) const;

    private:
        /**
         * @brief Removes leading and trailing whitespace characters from a string.
         * @param str Input string.
         * @return Trimmed copy of str.
         */
        static std::string Trim(const std::string &str);

        std::unordered_map<std::string, std::string> entries_; ///< Parsed key-value map.
    };

} // namespace Concurrency::Common