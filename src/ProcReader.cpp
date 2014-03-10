/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#include "VTFLib.h"
#include "Proc.h"
#include "ProcReader.h"

#include <limits>

using namespace VTFLib;
using namespace VTFLib::IO::Readers;

CProcReader::CProcReader(vlVoid *pUserData)
{
	this->bOpened = vlFalse;
	this->pUserData = pUserData;
}

CProcReader::~CProcReader()
{
	this->Close();
}

vlBool CProcReader::Opened() const
{
	return this->bOpened;
}

vlBool CProcReader::Open()
{
	this->Close();

	if(pReadOpenProc == 0)
	{
		LastError.Set("pReadOpenProc not set.");
		return vlFalse;
	}

	if(this->bOpened)
	{
		LastError.Set("Reader already open.");
		return vlFalse;
	}

	if(!pReadOpenProc(this->pUserData))
	{
		LastError.Set("Error opening file.");
		return vlFalse;
	}

	this->bOpened = vlTrue;

	return vlTrue;
}

vlVoid CProcReader::Close()
{
	if(pReadCloseProc == 0)
	{
		return;
	}

	if(this->bOpened)
	{
		pReadCloseProc(this->pUserData);
		this->bOpened = vlFalse;
	}
}

vlSSize CProcReader::GetStreamSize() const
{
	if(!this->bOpened)
	{
		return 0;
	}

	if(pReadSizeProc == 0)
	{
		LastError.Set("pReadSizeProc not set.");
		return std::numeric_limits<vlSSize>::max();
	}

	return pReadSizeProc(this->pUserData);
}

vlSSize CProcReader::GetStreamPointer() const
{
	if(!this->bOpened)
	{
		return 0;
	}

	if(pReadTellProc == 0)
	{
		LastError.Set("pReadTellProc not set.");
		return 0;
	}

	return pReadTellProc(this->pUserData);
}

vlSSize CProcReader::Seek(vlOffset lOffset, VLSeekMode uiMode)
{
	if(!this->bOpened)
	{
		return 0;
	}

	if(pReadSeekProc == 0)
	{
		LastError.Set("pReadSeekProc not set.");
		return 0;
	}

	return pReadSeekProc(lOffset, (VLSeekMode)uiMode, this->pUserData);
}

vlBool CProcReader::Read(vlChar &cChar)
{
	if(!this->bOpened)
	{
		return vlFalse;
	}

	if(pReadReadProc == 0)
	{
		LastError.Set("pReadReadProc not set.");
		return vlFalse;
	}

	vlUInt uiBytesRead = pReadReadProc(&cChar, 1, this->pUserData);

	if(uiBytesRead == 0)
	{
		LastError.Set("pReadReadProc() failed.");
	}

	return uiBytesRead == 1;
}

vlSize CProcReader::Read(vlVoid *vData, vlSize uiBytes)
{
	if(!this->bOpened)
	{
		return 0;
	}

	if(pReadReadProc == 0)
	{
		LastError.Set("pReadReadProc not set.");
		return 0;
	}

	vlUInt uiBytesRead = pReadReadProc(vData, uiBytes, this->pUserData);

	if(uiBytesRead == 0)
	{
		LastError.Set("pReadReadProc() failed.");
	}

	return uiBytesRead;
}
