/*
 * VTFLib
 * Copyright (C) 2005-2011 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

// ============================================================
// NOTE: This file is commented for compatibility with Doxygen.
// ============================================================
/*!
	\file stdafx.h
	\brief Application framework header plus VTFLib custom data types.
*/

#ifndef VTFLIB_STDAFX_H
#define VTFLIB_STDAFX_H

#include "config.h"

#if defined(_WIN32) || defined(_WIN64)
#	ifndef __WINDOWS__
#		define __WINDOWS__
#	endif
#endif

#ifdef __WINDOWS__
#	ifdef VTFLIB_EXPORTS
#		define VTFLIB_API __declspec(dllexport)
#	else
#		define VTFLIB_API __declspec(dllimport)
#	endif
#else
#	define VTFLIB_API __attribute__((visibility("default")))
#endif

#ifdef _MSC_VER
#	define VTFLIB_ALIGN16 __declspec(align(16))
#	define VTFLIB_PRINTF(FMT,ARGS)
#else
#	define VTFLIB_ALIGN16 __attribute__((aligned(16)))
#	define VTFLIB_PRINTF(FMT,ARGS) __attribute__((format(printf, FMT, ARGS)))
#endif

// Custom data types
typedef unsigned char	vlBool;				//!< Boolean value 0/1.
typedef char			vlChar;				//!< Single signed character.
typedef unsigned char	vlByte;				//!< Single unsigned byte.
typedef signed short	vlShort;			//!< Signed short floating point value.
typedef unsigned short	vlUShort;			//!< Unsigned short floating point value.
typedef signed int		vlInt;				//!< Signed integer value.
typedef unsigned int	vlUInt;				//!< Unsigned integer value.
typedef signed long		vlLong;				//!< Signed long number.
typedef unsigned long	vlULong;			//!< Unsigned long number.
typedef float			vlSingle;			//!< Floating point number
typedef double			vlDouble;			//!< Double number
typedef void			vlVoid;				//!< Void value.

typedef vlSingle		vlFloat;			//!< Floating point number (same as vlSingled).

#define vlFalse			0
#define vlTrue			1

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdarg.h>

#ifdef __cplusplus
#	include <cstdint>
#else
#	include <stdint.h>
#endif

#ifdef __WINDOWS__
typedef vlLong				vlOffset;		//!< Seek offset.
typedef vlUInt				vlSSize;		//!< File size.
typedef vlUInt				vlSize;			//!< General size.


typedef unsigned __int8		vlUInt8;
typedef unsigned __int16	vlUInt16;
typedef unsigned __int32	vlUInt32;
typedef unsigned __int64	vlUInt64;

#	if _MSC_VER >= 1400
#		define _CRT_SECURE_NO_WARNINGS
#		define _CRT_NONSTDC_NO_DEPRECATE
#	endif

#	define WIN32_LEAN_AND_MEAN
#	include <windows.h>

#	define vlFile HANDLE

#	ifndef strcasecmp
#		define strcasecmp stricmp
#	endif

#else

typedef off_t	vlOffset;
typedef off_t	vlSSize;
typedef size_t	vlSize;

typedef int8_t  vlUInt8;
typedef int16_t vlUInt16;
typedef int32_t vlUInt32;
typedef int64_t vlUInt64;

typedef FILE*	vlFile;

#endif

#if !defined(_MSC_VER) || _MSC_VER >= 1600 // Visual Studio 2010
#	define STATIC_ASSERT(condition, message) static_assert(condition, message)
#else
#	define STATIC_ASSERT(condition, message) typedef char __C_ASSERT__[(condition) ? 1 : -1]
#endif

typedef enum tagVLSeekMode
{
#ifdef __WINDOWS__
	SEEK_MODE_BEGIN = FILE_BEGIN,
	SEEK_MODE_CURRENT = FILE_CURRENT,
	SEEK_MODE_END = FILE_END
#else
	SEEK_MODE_BEGIN = SEEK_SET,
	SEEK_MODE_CURRENT = SEEK_CUR,
	SEEK_MODE_END = SEEK_END
#endif
} VLSeekMode;

#endif
