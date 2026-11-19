/**
 * @file STCPClient.h
 * @addtogroup Concurrency
 * @author Soumyajit C
 * @date 2026
 * @brief Header for STCPClient class, a TCP client wrapper for connecting to servers.
 * @brief Active TCP client class for connecting to a remote server and exchanging data.
 * @namespace Concurrency::Process
 */

#pragma once

#include "STCPConnection.h"

#include <cstdint>
#include <string>
#include "ExportMacro.h"

namespace Concurrency::Process
{

    /**
     * @class STCPClient
     * @brief Connects to a remote IPv4 TCP server and wraps the active STCPConnection.
     */
    class CONCURRENT_API STCPClient
    {
    public:
        /**
         * @brief Default constructor creating a disconnected client.
         */
        STCPClient() = default;

        /**
         * @brief Disconnects any active connection on destruction.
         */
        ~STCPClient();

        STCPClient(const STCPClient &) = delete;
        STCPClient &operator=(const STCPClient &) = delete;

        /**
         * @brief Connects to a TCP server at server_ip:port.
         * @param server_ip Target server IPv4 address string.
         * @param port Target server TCP port in host byte order.
         * @return true if connected, false on error.
         */
        bool connect_to(const std::string &server_ip, std::uint16_t port);

        /**
         * @brief Sends all bytes in data over the active connection.
         * @param data String payload to send.
         * @return true if sent successfully, false otherwise.
         */
        bool send_all(const std::string &data) const;

        /**
         * @brief Receives up to max_bytes from the server into out.
         * @param[out] out Output buffer for received data.
         * @param max_bytes Maximum number of bytes to read.
         * @return true if data was received, false on error or disconnect.
         */
        bool receive(std::string &out, std::size_t max_bytes = 1024) const;

        /**
         * @brief Closes the active connection if open.
         */
        void disconnect();

    private:
        STCPConnection conn_; ///< Active connection to the remote server.
    };

} // namespace Concurrency::Process