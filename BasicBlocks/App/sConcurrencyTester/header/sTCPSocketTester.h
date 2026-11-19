/**
 * @file sConcurrencyTester.h
 * @brief ITestRunner implementation for running config-driven TCP client/server tests.
 */

#pragma once

#include "ITestRunner.h"

#include <string>

/**
 * @class sConcurrencyTester
 * @brief Implements ITestRunner to execute STCPServer or STCPClient flows based on config.ini.
 */
class sTCPSocketTester : public ITestRunner
{
public:
    /**
     * @brief Constructs the concurrency tester with a target configuration file path.
     * @param config_path Path to the key=value config file (defaults to "config.ini").
     */
    explicit sTCPSocketTester(std::string config_path = "Concurrency/Socket/config.ini");

    /**
     * @brief Virtual destructor.
     */
    ~sTCPSocketTester() override = default;

    /**
     * @brief Executes all concurrency tests using the configured role, host, and port.
     */
    void RunAllTests() override;

private:
    /**
     * @brief Runs the TCP server or client flow and returns a status code.
     * @return 0 on success, non-zero on configuration or socket error.
     */
    int run_tcp_node() const;

    std::string config_path_; ///< Path to the configuration file.
};