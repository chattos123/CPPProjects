#pragma once

#if defined(_WIN32) || defined(__CYGWIN__)
    #ifdef SMATHLIB_EXPORTS
        #define SMATHLIB_API __declspec(dllexport)
    #else
        #define SMATHLIB_API __declspec(dllimport)
    #endif
#else
    #if __GNUC__ >= 4
        #define SMATHLIB_API __attribute__((visibility("default")))
    #else
        #define SMATHLIB_API
    #endif
#endif

// Function declarations
SMATHLIB_API void helloFromDLL();