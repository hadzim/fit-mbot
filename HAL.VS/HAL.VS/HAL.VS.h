// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the HALVS_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// HALVS_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HALVS_EXPORTS
#define HALVS_API __declspec(dllexport)
#else
#define HALVS_API __declspec(dllimport)
#endif

// This class is exported from the HAL.VS.dll
class HALVS_API CHALVS {
public:
	CHALVS(void);
	// TODO: add your methods here.
};

extern HALVS_API int nHALVS;

HALVS_API int fnHALVS(void);
