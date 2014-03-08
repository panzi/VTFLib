/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#include <string.h>

#include "VTFLib.h"
#include "MemoryReader.h"

using namespace VTFLib;
using namespace VTFLib::IO::Readers;

CMemoryReader::CMemoryReader(const vlVoid *vData, vlSize uiBufferSize)
{
	this->bOpened = vlFalse;

	this->vData = vData;
	this->uiBufferSize = uiBufferSize;
	this->uiPointer = 0;
}

CMemoryReader::~CMemoryReader()
{

}

vlBool CMemoryReader::Opened() const
{
	return this->bOpened;
}

vlBool CMemoryReader::Open()
{
	if(vData == 0)
	{
		LastError.Set("Memory stream is null.");
		return vlFalse;
	}

	this->uiPointer = 0;

	this->bOpened = vlTrue;

	return vlTrue;
}

vlVoid CMemoryReader::Close()
{
	this->bOpened = vlFalse;
}

vlSSize CMemoryReader::GetStreamSize() const
{
	if(!this->bOpened)
	{
		return 0;
	}

	return this->uiBufferSize;
}

vlSSize CMemoryReader::GetStreamPointer() const
{
	if(!this->bOpened)
	{
		return 0;
	}

	return this->uiPointer;
}

vlSSize CMemoryReader::Seek(vlOffset lOffset, VLSeekMode uiMode)
{
	if(!this->bOpened)
	{
		return 0;
	}

	switch(uiMode)
	{
		case SEEK_MODE_BEGIN:
			this->uiPointer = 0;
			break;
		case SEEK_MODE_CURRENT:

			break;
		case SEEK_MODE_END:
			this->uiPointer = this->uiBufferSize;
			break;
	}

	vlOffset lPointer = (vlOffset)this->uiPointer + lOffset;

	if(lPointer < 0)
	{
		lPointer = 0;
	}

	if(lPointer > (vlOffset)this->uiBufferSize)
	{
		lPointer = (vlOffset)this->uiBufferSize;
	}

	this->uiPointer = (vlSize)lPointer;

	return (vlSSize)this->uiPointer;
}

vlBool CMemoryReader::Read(vlChar &cChar)
{
	if(!this->bOpened)
	{
		return vlFalse;
	}

	if(this->uiPointer == this->uiBufferSize)
	{
		LastError.Set("End of memory stream.");

		return vlFalse;
	}
	else
	{
		cChar = *((vlChar *)this->vData + this->uiPointer++);

		return vlTrue;
	}
}

vlSize CMemoryReader::Read(vlVoid *vData, vlSize uiBytes)
{
	if(!this->bOpened)
	{
		return 0;
	}

	if(this->uiPointer == this->uiBufferSize)
	{
		return 0;
	}
	else if(uiBytes > this->uiBufferSize || // <- prevent integer overflow
		this->uiPointer + uiBytes > this->uiBufferSize) // This right?
	{
		uiBytes = this->uiBufferSize - this->uiPointer;

		memcpy(vData, (vlByte *)this->vData + this->uiPointer, uiBytes);

		this->uiPointer = this->uiBufferSize;

		LastError.Set("End of memory stream.");

		return uiBytes;
	}
	else
	{
		memcpy(vData, (vlByte *)this->vData + this->uiPointer, uiBytes);

		this->uiPointer += uiBytes;

		return uiBytes;
	}
}
