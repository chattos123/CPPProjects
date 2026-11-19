/**
 * @file STCPEnvironment.h
 * @addtogroup Concurrency
 * @author Soumyajit C
 * @date 2026
 * @brief RAII wrapper for platform-level TCP/IP socket initialization and teardown.
 * @namespace Concurrency::Process
 */

#pragma once

#include "ExportMacro.h"

namespace Concurrency::Process
{

    /**
     * @class STCPEnvironment
     * @brief Manages Winsock startup/cleanup on Windows and acts as a no-op scope guard on POSIX/Linux.
     *
     * Instantiate once before creating any STCPServer or STCPClient objects.
     * Non-copyable to prevent double WSACleanup calls.
     */
    class CONCURRENT_API STCPEnvironment
    {
    public:
        /**
         * @brief Initializes the underlying socket environment (WSAStartup on Windows).
         */
        STCPEnvironment();

        /**
         * @brief Cleans up the socket environment (WSACleanup on Windows) if initialization succeeded.
         */
        ~STCPEnvironment();

        STCPEnvironment(const STCPEnvironment &) = delete;
        STCPEnvironment &operator=(const STCPEnvironment &) = delete;

        /**
         * @brief Checks whether the socket environment initialized successfully.
         * @return true if sockets are ready to use, false otherwise.
         */
        bool is_ok() const;

    private:
        bool mb_Ok_ = true; ///< Tracks initialization status.
    };

} // namespace Concurrency::Process