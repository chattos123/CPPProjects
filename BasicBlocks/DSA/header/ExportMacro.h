#ifndef EXPORT_MACRO_H
#define EXPORT_MACRO_H

#if defined(_WIN32) || defined(__CYGWIN__)
    #ifdef BUILDING_DSA_DLL
        #define DSA_API __declspec(dllexport)
    #else
        #define DSA_API __declspec(dllimport)
    #endif
#else
    #if __GNUC__ >= 4
        #define DSA_API __attribute__ ((visibility ("default")))
    #else
        #define DSA_API
    #endif
#endif

// 🛡️ Fallback macro alias: Catches any legacy or cached references to DSALIB_API
#ifndef DSALIB_API
    #define DSALIB_API DSA_API
#endif

#endif // EXPORT_MACRO_H