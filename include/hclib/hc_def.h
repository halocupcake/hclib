#ifndef HC_DEF_H
#define HC_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

// if youre using a DLL, define HCLIB_DLL before any hclib headers:
// #define HCLIB_DLL

#if defined(HCLIB_DLL) && (defined(_WIN32) || defined(__CYGWIN__))
#    ifdef HCLIB_EXPORTING
#        ifdef __GNUC__
#            define HC_API __attribute__ ((dllexport))
#        else
#            define HC_API __declspec(dllexport)
#        endif
#    else
#        ifdef __GNUC__
#            define HC_API __attribute__ ((dllimport))
#        else
#            define HC_API __declspec(dllimport)
#        endif
#    endif
#else
#    define HC_API
#endif

#ifdef __cplusplus
}
#endif

#endif // HC_DEF_H
