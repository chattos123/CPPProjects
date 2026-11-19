/**
 * @file SConfigParser.cpp
 * @addtogroup Concurrency
 * @author Soumyajit C
 * @date 2026
 * @brief Implementation of Concurrency::Common::SConfigParser for reading and validating config files.
 */

#include "SConfigParser.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

namespace Concurrency::Common
{

    /**
     * @brief Trims spaces, tabs, carriage returns, and newlines from both ends of str.
     */
    std::string SConfigParser::Trim(const std::string &str)
    {
        const std::size_t first = str.find_first_not_of(" \t\r\n");

        if (first == std::string::npos)
        {
            return "";
        }
        const std::size_t last = str.find_last_not_of(" \t\r\n");
        return str.substr(first, last - first + 1);
    }

    /**
     * @brief Reads lines from file_path, strips comments, splits on '=', and stores Trimmed entries.
     */
    bool SConfigParser::load(const std::string &file_path)
    {
        std::ifstream file(file_path);
        if (!file.is_open())
        {
            std::cerr << "[SConfigParser] Failed to open config file: " << file_path << "\n";
            return false;
        }

        entries_.clear();
        std::string line;
        while (std::getline(file, line))
        {
            const std::size_t comment_pos = line.find_first_of("#;");
            if (comment_pos != std::string::npos)
            {
                line = line.substr(0, comment_pos);
            }

            line = Trim(line);
            if (line.empty())
            {
                continue;
            }

            const std::size_t eq_pos = line.find('=');
            if (eq_pos == std::string::npos)
            {
                continue;
            }

            const std::string key = Trim(line.substr(0, eq_pos));
            const std::string value = Trim(line.substr(eq_pos + 1));
            if (!key.empty())
            {
                entries_[key] = value;
            }
        }

        return true;
    }

    /**
     * @brief Looks up key in entries_ and returns its value or default_val.
     */
    std::string SConfigParser::get_string(const std::string &key, const std::string &default_val) const
    {
        const auto it = entries_.find(key);
        if (it == entries_.end())
        {
            return default_val;
        }
        return it->second;
    }

    /**
     * @brief Looks up key in entries_ and converts it to int, or returns default_val on error.
     */
    int SConfigParser::get_int(const std::string &key, int default_val) const
    {
        const auto it = entries_.find(key);
        if (it == entries_.end())
        {
            return default_val;
        }
        try
        {
            std::size_t parsed_chars = 0;
            const int val = std::stoi(it->second, &parsed_chars);
            if (parsed_chars != it->second.size())
            {
                return default_val;
            }
            return val;
        }
        catch (const std::exception &)
        {
            return default_val;
        }
    }

    /**
     * @brief Populates and validates role, host, and port into out_config.
     */
    bool SConfigParser::to_node_config(STCPNodeConfig &out_config) const
    {
        STCPNodeConfig cfg;
        cfg.role = get_string("role", cfg.role);
        cfg.host = get_string("host", cfg.host);

        const int raw_port = get_int("port", static_cast<int>(cfg.port));
        if (raw_port < 1 || raw_port > 65535)
        {
            std::cerr << "[SConfigParser] Port out of range (1-65535): " << raw_port << "\n";
            return false;
        }
        cfg.port = static_cast<std::uint16_t>(raw_port);

        if (cfg.role != "server" && cfg.role != "client")
        {
            std::cerr << "[SConfigParser] Invalid role '" << cfg.role
                      << "' (expected 'server' or 'client').\n";
            return false;
        }

        out_config = cfg;
        return true;
    }

} // namespace Concurrency::Common