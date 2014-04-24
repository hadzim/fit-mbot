/*
 * HALAPI.h
 *
 *  Created on: 20.3.2014
 *      Author: JV
 */

#ifndef HALAPI_H_
#define HALAPI_H_


#ifndef HALguard_H_
#define HALguard_H_



#if defined(_WIN32) && defined(_HAL_DLL)
#define HAL_DLL
#endif

#if defined(__WIN32__) && defined(HAL_DLL)
#if defined(_HAL_EXPORTS)
#define HAL_API __declspec(dllexport)
#else
#define HAL_API __declspec(dllimport)
#endif
#endif

#if !defined(HAL_API)
#define HAL_API
#endif

#endif


#endif /* HALAPI_H_ */
