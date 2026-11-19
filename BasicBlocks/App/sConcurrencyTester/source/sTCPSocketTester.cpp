/**
 * @file sTCPSocketTester.cpp
 * @brief Implementation of sTCPSocketTester adhering to the ITestRunner interface.
 */
#include "SConfigParser.h"
#include "STCPClient.h"
#include "STCPConnection.h"
#include "STCPEnvironment.h"
#include "STCPServer.h"
#include "sTCPSocketTester.h"
#include <iostream>
#include <utility>

namespace
{

    /**
     * @brief Executes the TCP server role: binds, accepts one client, receives a message, and replies.
     * @param cfg Validated TCP node configuration.
     * @return 0 on success, 1 on failure.
     */
    int run_server(const Concurrency::Common::STCPNodeConfig &cfg)
    {
        Concurrency::Process::STCPServer server;
        if (!server.start(cfg.host, cfg.port))
        {
            return 1;
        }

        std::string client_ip;
        Concurrency::Process::STCPConnection client = server.accept_client(&client_ip);
        if (!client.is_valid())
        {
            return 1;
        }

        std::cout << "[sConcurrencyTester] Client connected from " << client_ip << "\n";

        std::string msg;
        if (client.receive(msg))
        {
            std::cout << "[sConcurrencyTester] Received: " << msg << "\n";
            client.send_all("ACK from server");
        }

        return 0;
    }

    /**
     * @brief Executes the TCP client role: connects to host:port, sends a message, and reads the reply.
     * @param cfg Validated TCP node configuration.
     * @return 0 on success, 1 on failure.
     */
    int run_client(const Concurrency::Common::STCPNodeConfig &cfg)
    {
        Concurrency::Process::STCPClient client;
        if (!client.connect_to(cfg.host, cfg.port))
        {
            return 1;
        }

        client.send_all("Hello from sConcurrencyTester client!");

        std::string reply;
        if (client.receive(reply))
        {
            std::cout << "[sConcurrencyTester] Server replied: " << reply << "\n";
        }

        return 0;
    }

} // namespace

/**
 * @brief Initializes sTCPSocketTester with the given config file path.
 */
sTCPSocketTester::sTCPSocketTester(std::string config_path)
    : config_path_(std::move(config_path)) {}

/**
 * @brief Runs the concurrency test suite and logs pass/fail status.
 */
void sTCPSocketTester::RunAllTests()
{
    std::cout << "=== Running Concurrency Tests (" << config_path_ << ") ===\n";
    const int rc = run_tcp_node();
    if (rc != 0)
    {
        std::cerr << "[sTCPSocketTester] Test failed with code: " << rc << "\n";
    }
    else
    {
        std::cout << "[sTCPSocketTester] Test completed successfully.\n";
    }
}

/**
 * @brief Parses config_path_, initializes the socket environment, and dispatches to server/client.
 */
int sTCPSocketTester::run_tcp_node() const
{
    Concurrency::Common::SConfigParser parser;
    if (!parser.load(config_path_))
    {
        return 1;
    }

    Concurrency::Common::STCPNodeConfig cfg;
    if (!parser.to_node_config(cfg))
    {
        return 1;
    }

    Concurrency::Process::STCPEnvironment env;
    if (!env.is_ok())
    {
        return 1;
    }

    if (cfg.role == "server")
    {
        return run_server(cfg);
    }
    if (cfg.role == "client")
    {
        return run_client(cfg);
    }

    std::cerr << "[sTCPSocketTester] Unsupported role: " << cfg.role << "\n";
    return 1;
}