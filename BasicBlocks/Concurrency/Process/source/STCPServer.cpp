/**
 * @file STCPServer.cpp
 * @author Soumyajit C
 * @date 2026
 * @brief Implementation of STCPServer socket creation, binding, listening, and accepting.
 */

#include "STCPServer.h"

#include <iostream>

#ifdef _WIN32
#include <ws2tcpip.h>
namespace
{
    /**
     * @brief Closes the listening socket handle on Windows.
     * @param s Socket descriptor to close.
     */
    void close_listen_socket(stcp_socket_t s)
    {
        if (s != kInvalidSocket)
            closesocket(s);
    }
} // namespace
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
namespace
{
    /**
     * @brief Closes the listening socket descriptor on POSIX/Linux.
     * @param s File descriptor to close.
     */
    void close_listen_socket(stcp_socket_t s)
    {
        if (s != kInvalidSocket)
            ::close(s);
    }
} // namespace
#endif

namespace Concurrency::Process
{

    /**
     * @brief Destructor that stops the listening socket.
     */
    STCPServer::~STCPServer()
    {
        stop();
    }

    /**
     * @brief Opens a TCP socket, sets SO_REUSEADDR, binds to bind_ip:port, and listens.
     */
    bool STCPServer::start(const std::string &bind_ip, std::uint16_t port, int backlog)
    {
        stop();

        listen_sock_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if (listen_sock_ == kInvalidSocket)
        {
            std::cerr << "[STCPServer] Failed to create socket.\n";
            return false;
        }

        int opt = 1;
#ifdef _WIN32
        setsockopt(listen_sock_, SOL_SOCKET, SO_REUSEADDR,
                   reinterpret_cast<const char *>(&opt), sizeof(opt));
#else
        setsockopt(listen_sock_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
#endif

        // Prepare sockaddr_in structure for binding
        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);

        // Convert bind_ip string to binary form
        if (inet_pton(AF_INET, bind_ip.c_str(), &addr.sin_addr) <= 0)
        {
            std::cerr << "[STCPServer] Invalid bind IP: " << bind_ip << "\n";
            stop();
            return false;
        }

        // Bind the socket to the specified IP and port
        if (bind(listen_sock_, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0)
        {
            std::cerr << "[STCPServer] Bind failed on " << bind_ip << ":" << port << "\n";
            stop();
            return false;
        }

        // Start listening for incoming connections
        if (listen(listen_sock_, backlog) < 0)
        {
            std::cerr << "[STCPServer] Listen failed.\n";
            stop();
            return false;
        }

        std::cout << "[STCPServer] Listening on " << bind_ip << ":" << port << "...\n";
        return true;
    }

    /**
     * @brief Accepts an incoming client connection and optionally extracts its IPv4 address.
     */
    STCPConnection STCPServer::accept_client(std::string *client_ip_out) const
    {
        if (listen_sock_ == kInvalidSocket)
            return STCPConnection{};

        sockaddr_in client_addr{};
#ifdef _WIN32
        int client_len = sizeof(client_addr);
#else
        socklen_t client_len = sizeof(client_addr);
#endif

        stcp_socket_t client_sock = accept(
            listen_sock_, reinterpret_cast<sockaddr *>(&client_addr), &client_len);
        
        if (client_sock == kInvalidSocket)
        {
            std::cerr << "[STCPServer] Accept failed.\n";
            return STCPConnection{};
        }

        if (client_ip_out)
        {
            char ip_buf[INET_ADDRSTRLEN]{};
            inet_ntop(AF_INET, &client_addr.sin_addr, ip_buf, sizeof(ip_buf));
            *client_ip_out = ip_buf;
        }

        return STCPConnection(client_sock);
    }

    /**
     * @brief Closes the listening socket and resets listen_sock_.
     */
    void STCPServer::stop()
    {
        close_listen_socket(listen_sock_);
        listen_sock_ = kInvalidSocket;
    }

} // namespace Concurrency::Process