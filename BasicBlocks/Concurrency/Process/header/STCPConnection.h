/**
 * @file STCPConnection.h
 * @addtogroup Concurrency
 * @author Soumyajit C
 * @date 2026
 * @brief Move-only RAII wrapper for an active TCP socket stream.
 * @namespace Concurrency::Process
 */

#pragma once

#include <cstddef>
#include <string>
#include "ExportMacro.h"

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
using stcp_socket_t = SOCKET;
// Invalid socket constant for Windows (SOCKET type).
inline constexpr stcp_socket_t kInvalidSocket = INVALID_SOCKET;
#else
using stcp_socket_t = int;
// Invalid socket constant for POSIX/Linux (int type).
inline constexpr stcp_socket_t kInvalidSocket = -1;
#endif

namespace Concurrency::Process
{

    /**
     * @class STCPConnection
     * @brief Owns a connected TCP socket descriptor and provides reliable send/receive helpers.
     *
     * Non-copyable to avoid accidental duplicate socket closures, but movable so accepted
     * client sockets can be returned from STCPServer::accept_client() or transferred.
     */
    class CONCURRENT_API STCPConnection
    {
    public:
        /**
         * @brief Wraps an existing raw socket descriptor.
         * @param sock Connected socket handle (defaults to kInvalidSocket).
         */
        explicit STCPConnection(stcp_socket_t sock = kInvalidSocket);

        /**
         * @brief Closes the owned socket if still open.
         */
        ~STCPConnection();

        STCPConnection(const STCPConnection &) = delete;
        STCPConnection &operator=(const STCPConnection &) = delete;

        /**
         * @brief Move constructor transferring socket ownership.
         * @param other Source connection to move from; left with kInvalidSocket.
         */
        STCPConnection(STCPConnection &&other) noexcept;

        /**
         * @brief Move assignment operator closing any current socket and taking ownership.
         * @param other Source connection to move from; left with kInvalidSocket.
         * @return Reference to this connection.
         */
        STCPConnection &operator=(STCPConnection &&other) noexcept;

        /**
         * @brief Checks whether the underlying socket handle is valid.
         * @return true if sock_ != kInvalidSocket, false otherwise.
         */
        bool is_valid() const;

        /**
         * @brief Returns the underlying platform socket handle.
         * @return Native socket descriptor (SOCKET on Windows, int on Linux).
         */
        stcp_socket_t native_handle() const;

        /**
         * @brief Sends the entire string buffer over TCP, looping until all bytes are written.
         * @param data Payload bytes to transmit.
         * @return true if all bytes were sent, false on error or invalid socket.
         */
        bool send_all(const std::string &data) const;

        /**
         * @brief Receives up to max_bytes from the peer into out.
         * @param[out] out Buffer populated with received bytes (cleared on failure/disconnect).
         * @param max_bytes Maximum number of bytes to read in one call.
         * @return true if bytes were read, false on clean disconnect or socket error.
         */
        bool receive(std::string &out, std::size_t max_bytes = 1024) const;

        /**
         * @brief Explicitly closes the socket and resets the handle to kInvalidSocket.
         */
        void close();

    private:
        stcp_socket_t sock_ = kInvalidSocket; ///< Owned socket descriptor.
    };

} // namespace Concurrency::Process