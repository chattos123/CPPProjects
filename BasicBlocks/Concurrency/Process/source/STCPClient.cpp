/**
 * @file STCPClient.cpp
 * @author Soumyajit C
 * @date 2026
 * @brief Implementation of STCPClient connection establishment and stream operations.
 */

#include "STCPClient.h"

#include <iostream>

#ifdef _WIN32
#include <ws2tcpip.h>
namespace
{
    /**
     * @brief Closes a client socket handle on Windows.
     * @param s Socket descriptor to close.
     */
    void close_client_socket(stcp_socket_t s)
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
     * @brief Closes a client socket descriptor on POSIX/Linux.
     * @param s File descriptor to close.
     */
    void close_client_socket(stcp_socket_t s)
    {
        if (s != kInvalidSocket)
            ::close(s);
    }
} // namespace
#endif

namespace Concurrency::Process
{

    /**
     * @brief Destructor that disconnects any active socket connection.
     */
    STCPClient::~STCPClient()
    {
        disconnect();
    }

    /**
     * @brief Creates a TCP socket, parses server_ip, connects to server_ip:port, and stores conn_.
     */
    bool STCPClient::connect_to(const std::string &server_ip, std::uint16_t port)
    {
        disconnect();

        // Create a TCP socket
        stcp_socket_t sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if (sock == kInvalidSocket)
        {
            std::cerr << "[STCPClient] Failed to create socket.\n";
            return false;
        }

        // Prepare the sockaddr_in structure for the target server
        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);

        // Convert the server IP string to binary form
        if (inet_pton(AF_INET, server_ip.c_str(), &addr.sin_addr) <= 0)
        {
            std::cerr << "[STCPClient] Invalid target IP: " << server_ip << "\n";
            close_client_socket(sock);
            return false;
        }

        // Attempt to connect to the server
        std::cout << "[STCPClient] Connecting to " << server_ip << ":" << port << "...\n";
        if (connect(sock, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0)
        {
            std::cerr << "[STCPClient] Connection failed.\n";
            close_client_socket(sock);
            return false;
        }

        //
        conn_ = STCPConnection(sock);
        return true;
    }

    /**
     * @brief Delegates sending all bytes to the underlying STCPConnection.
     */
    bool STCPClient::send_all(const std::string &data) const
    {
        return conn_.send_all(data);
    }

    /**
     * @brief Delegates receiving bytes to the underlying STCPConnection.
     */
    bool STCPClient::receive(std::string &out, std::size_t max_bytes) const
    {
        return conn_.receive(out, max_bytes);
    }

    /**
     * @brief Closes the underlying STCPConnection.
     */
    void STCPClient::disconnect()
    {
        conn_.close();
    }

} // namespace Concurrency::Process