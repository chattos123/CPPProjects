/**
 * @file STCPConnection.cpp
 * @author Soumyajit C
 * @date 2026
 * @brief Implementation of STCPConnection for cross-platform TCP stream I/O.
 */

#include "STCPConnection.h"

#ifdef _WIN32
#include <ws2tcpip.h>
namespace
{
    /**
     * @brief Closes a Winsock socket handle if valid.
     * @param s Socket descriptor to close.
     */
    void close_raw_socket(stcp_socket_t s)
    {
        if (s != kInvalidSocket)
            closesocket(s);
    }
} // namespace
#else
#include <sys/socket.h>
#include <unistd.h>
namespace
{
    /**
     * @brief Closes a POSIX file descriptor if valid.
     * @param s File descriptor to close.
     */
    void close_raw_socket(stcp_socket_t s)
    {
        if (s != kInvalidSocket)
            ::close(s);
    }
} // namespace
#endif

namespace Concurrency::Process
{

    /**
     * @brief Initializes STCPConnection with a raw socket handle.
     */
    STCPConnection::STCPConnection(stcp_socket_t sock) : sock_(sock) {}

    /**
     * @brief Ensures the socket is closed upon destruction.
     */
    STCPConnection::~STCPConnection()
    {
        close();
    }

    /**
     * @brief Transfers ownership of sock_ from other and invalidates other.sock_.
     */
    STCPConnection::STCPConnection(STCPConnection &&other) noexcept : sock_(other.sock_)
    {
        other.sock_ = kInvalidSocket;
    }

    /**
     * @brief Closes existing socket, takes ownership of other.sock_, and invalidates other.
     */
    STCPConnection &STCPConnection::operator=(STCPConnection &&other) noexcept
    {
        if (this != &other)
        {
            close();
            sock_ = other.sock_;
            other.sock_ = kInvalidSocket;
        }
        return *this;
    }

    /**
     * @brief Returns true if sock_ is not kInvalidSocket.
     */
    bool STCPConnection::is_valid() const
    {
        return sock_ != kInvalidSocket;
    }

    /**
     * @brief Returns the raw socket handle.
     */
    stcp_socket_t STCPConnection::native_handle() const
    {
        return sock_;
    }

    /**
     * @brief Loops over send() until every byte in data has been transmitted.
     */
    bool STCPConnection::send_all(const std::string &data) const
    {
        if (!is_valid())
            return false;
        std::size_t total_sent = 0;
        while (total_sent < data.size())
        {
#ifdef _WIN32
            int sent = send(sock_, data.data() + total_sent,
                            static_cast<int>(data.size() - total_sent), 0);
#else
            ssize_t sent = ::send(sock_, data.data() + total_sent,
                                  data.size() - total_sent, 0);
#endif
            if (sent <= 0)
                return false;
            total_sent += static_cast<std::size_t>(sent);
        }
        return true;
    }

    /**
     * @brief Reads up to max_bytes from the socket and resizes out to actual bytes received.
     */
    bool STCPConnection::receive(std::string &out, std::size_t max_bytes) const
    {
        if (!is_valid() || max_bytes == 0)
            return false;
        out.resize(max_bytes);
#ifdef _WIN32
        int bytes = recv(sock_, out.data(), static_cast<int>(max_bytes), 0);
#else
        ssize_t bytes = ::recv(sock_, out.data(), max_bytes, 0);
#endif
        if (bytes <= 0)
        {
            out.clear();
            return false;
        }
        out.resize(static_cast<std::size_t>(bytes));
        return true;
    }

    /**
     * @brief Closes the raw socket and marks the connection invalid.
     */
    void STCPConnection::close()
    {
        close_raw_socket(sock_);
        sock_ = kInvalidSocket;
    }

} // namespace Concurrency::Process