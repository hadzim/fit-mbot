#ifndef TBSServguard_H_
#define TBSServguard_H_



#if defined(_WIN32) && defined(_TBSSERV_DLL)
#define TBSSERV_DLL
#endif

#if defined(__WIN32__) && defined(TBSSERV_DLL)
#if defined(_TBSSERV_EXPORTS)
#define TBSSERV_API __declspec(dllexport)
#else
#define TBSSERV_API __declspec(dllimport)
#endif
#endif

#if !defined(TBSSERV_API)
#define TBSSERV_API
#endif

#endif
