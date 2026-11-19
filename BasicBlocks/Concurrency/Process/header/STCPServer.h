/**
 * @file STCPServer.h
 * @addtogroup Concurrency
 * @brief Listening TCP server class for accepting incoming client connections.
 * @author Soumyajit C
 * @date 2026
 * @remark Requires STCPEnvironment to be instantiated before use.
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
     * @class STCPServer
     * @brief Creates a bound, listening IPv4 TCP socket and accepts client connections.
     */
    class CONCURRENT_API STCPServer
    {
    public:
        /**
         * @brief Default constructor creating an uninitialized server.
         */
        STCPServer() = default;

        /**
         * @brief Stops the server and closes the listening socket.
         */
        ~STCPServer();

        STCPServer(const STCPServer &) = delete;
        STCPServer &operator=(const STCPServer &) = delete;

        /**
         * @brief Binds to bind_ip:port and begins listening for incoming connections.
         * @param bind_ip IPv4 address to bind (e.g., "0.0.0.0" or a specific interface IP).
         * @param port TCP port number in host byte order.
         * @param backlog Maximum queue length for pending connections.
         * @return true if the server is listening, false on failure.
         */
        bool start(const std::string &bind_ip, std::uint16_t port, int backlog = 16);

        /**
         * @brief Blocks until a client connects and returns an owning STCPConnection.
         * @param[out] client_ip_out Optional pointer to receive the connected client's IPv4 string.
         * @return Valid STCPConnection on success, or an invalid STCPConnection on error.
         */
        STCPConnection accept_client(std::string *client_ip_out = nullptr) const;

        /**
         * @brief Closes the listening socket if open.
         */
        void stop();

    private:
        stcp_socket_t listen_sock_ = kInvalidSocket; ///< Listening socket descriptor.
    };

} // namespace Concurrency::Process