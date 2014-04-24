// HAL.VS.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "HAL.VS.h"


// This is an example of an exported variable
HALVS_API int nHALVS=0;

// This is an example of an exported function.
HALVS_API int fnHALVS(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see HAL.VS.h for the class definition
CHALVS::CHALVS()
{
	return;
}
