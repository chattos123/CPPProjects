/**
 * @file ExportMacro.h
 * @brief Macro definitions for cross-platform dynamic library export/import symbols.
 * @author Soumyajit C
 * @date 2026
 * 
 * @remark Handles DLL export/import linkage specifications for Windows builds 
 *         (_declspec(dllexport/dllimport)) as well as default symbol visibility 
 *         for GCC/Clang compilers on Posix environments.
 */

#ifndef EXPORT_MACRO_H
#define EXPORT_MACRO_H

#if defined(_WIN32) || defined(__CYGWIN__)
    #ifdef BUILDING_DSA_DLL
        /**
         * @brief Exports public API symbols when compiling the shared DSA dynamic library (.dll).
         */
        #define DSA_API __declspec(dllexport)
    #else
        /**
         * @brief Imports public API symbols when linking against the compiled DSA dynamic library (.dll).
         */
        #define DSA_API __declspec(dllimport)
    #endif
#else
    #if __GNUC__ >= 4
        /**
         * @brief Configures public visibility for symbols in GCC/Clang shared libraries (.so / .dylib).
         */
        #define DSA_API __attribute__ ((visibility ("default")))
    #else
        /**
         * @brief Default fallback definition for legacy compilers.
         */
        #define DSA_API
    #endif
#endif

/**
 * @def DSALIB_API
 * @brief Fallback macro alias to maintain backward compatibility with legacy or cached DSALIB_API references.
 */
#ifndef DSALIB_API
    #define DSALIB_API DSA_API
#endif

#endif // EXPORT_MACRO_H