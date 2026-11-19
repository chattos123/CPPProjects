/**
 * @file STCPEnvironment.cpp
 * @author Soumyajit C
 * @date 2026
 * @brief Implementation of STCPEnvironment for Windows (Winsock2) and Linux (POSIX).
 */

#include "STCPEnvironment.h"

#include <iostream>

#ifdef _WIN32
#include <winsock2.h>
#endif

namespace Concurrency::Process
{

    /**
     * @brief Constructs STCPEnvironment and calls WSAStartup(2, 2) on Windows.
     */
    STCPEnvironment::STCPEnvironment()
    {
#ifdef _WIN32
        WSADATA wsa_data{};
        
        mb_Ok_ = (WSAStartup(MAKEWORD(2, 2), &wsa_data) == 0);
        if (!mb_Ok_)
        {
            std::cerr << "[STCP] WSAStartup failed.\n";
        }
#endif
    }

    /**
     * @brief Destroys STCPEnvironment and calls WSACleanup on Windows if initialized.
     */
    STCPEnvironment::~STCPEnvironment()
    {
#ifdef _WIN32
        if (mb_Ok_)
        {
            WSACleanup();
        }
#endif
    }

    /**
     * @brief Returns whether the socket environment is valid.
     * @return true if valid, false otherwise.
     */
    bool STCPEnvironment::is_ok() const
    {
        return mb_Ok_;
    }

} // namespace Concurrency::Process