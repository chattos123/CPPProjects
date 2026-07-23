#pragma once

#ifdef SMathLib_EXPORTS
#define SMATHLIB_API __declspec(dllexport)
#else
#define SMATHLIB_API __declspec(dllimport)
#endif

SMATHLIB_API void helloFromDLL();
