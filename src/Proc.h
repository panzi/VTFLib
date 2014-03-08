/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#ifndef VTFLIB_PROC_H
#define VTFLIB_PROC_H

#include "stdafx.h"
#include "Error.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum tagVLProc
{
	PROC_READ_CLOSE = 0,
	PROC_READ_OPEN,
	PROC_READ_READ,
	PROC_READ_SEEK,
	PROC_READ_TELL,
	PROC_READ_SIZE,
	PROC_WRITE_CLOSE,
	PROC_WRITE_OPEN,
	PROC_WRITE_WRITE,
	PROC_WRITE_SEEK,
	PROC_WRITE_SIZE,
	PROC_WRITE_TELL,
	PROC_COUNT
} VLProc;

typedef vlVoid (*PReadCloseProc)(vlVoid *);
typedef vlBool (*PReadOpenProc) (vlVoid *);
typedef vlSize (*PReadReadProc)  (vlVoid *, vlSize, vlVoid *);
typedef vlSSize (*PReadSeekProc) (vlOffset, VLSeekMode, vlVoid *);
typedef vlSSize (*PReadSizeProc) (vlVoid *);
typedef vlSSize (*PReadTellProc) (vlVoid *);

typedef vlVoid (*PWriteCloseProc)(vlVoid *);
typedef vlBool (*PWriteOpenProc) (vlVoid *);
typedef vlSize (*PWriteWriteProc) (vlVoid *, vlSize, vlVoid *);
typedef vlSSize (*PWriteSeekProc) (vlOffset, VLSeekMode, vlVoid *);
typedef vlSSize (*PWriteSizeProc) (vlVoid *);
typedef vlSSize (*PWriteTellProc) (vlVoid *);

#ifdef __cplusplus
}
#endif

namespace VTFLib
{
	extern PReadCloseProc pReadCloseProc;
	extern PReadOpenProc pReadOpenProc;
	extern PReadReadProc pReadReadProc;
	extern PReadSeekProc pReadSeekProc;
	extern PReadSizeProc pReadSizeProc;
	extern PReadTellProc pReadTellProc;

	extern PWriteCloseProc pWriteCloseProc;
	extern PWriteOpenProc pWriteOpenProc;
	extern PWriteWriteProc pWriteWriteProc;
	extern PWriteSeekProc pWriteSeekProc;
	extern PWriteSizeProc pWriteSizeProc;
	extern PWriteTellProc pWriteTellProc;
}

#ifdef __cplusplus
extern "C" {
#endif

VTFLIB_API vlVoid vlSetProc(VLProc Proc, vlVoid *pProc);
VTFLIB_API vlVoid *vlGetProc(VLProc Proc);

#ifdef __cplusplus
}
#endif

#endif
