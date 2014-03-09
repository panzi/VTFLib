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
#include "MemoryWriter.h"

using namespace VTFLib;
using namespace VTFLib::IO::Writers;

CMemoryWriter::CMemoryWriter(vlVoid *vData, vlSize uiBufferSize)
{
	this->bOpened = vlFalse;

	this->vData = vData;
	this->uiBufferSize = uiBufferSize;

	this->uiPointer = 0;
	this->uiLength = 0;
}

CMemoryWriter::~CMemoryWriter()
{

}

vlBool CMemoryWriter::Opened() const
{
	return this->bOpened;
}

vlBool CMemoryWriter::Open()
{
	if(vData == 0)
	{
		LastError.Set("Memory stream is null.");
		return vlFalse;
	}

	this->uiPointer = 0;
	this->uiLength = 0;

	this->bOpened = vlTrue;

	return vlTrue;
}

vlVoid CMemoryWriter::Close()
{
	this->bOpened = vlFalse;
}

vlSSize CMemoryWriter::GetStreamSize() const
{
	/*if(!this->bOpened)
	{
		return 0;
	}*/

	return this->uiLength;
}

vlSSize CMemoryWriter::GetStreamPointer() const
{
	if(!this->bOpened)
	{
		return 0;
	}

	return this->uiPointer;
}

vlSSize CMemoryWriter::Seek(vlOffset lOffset, VLSeekMode uiMode)
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
			this->uiPointer = this->uiLength;
			break;
	}

	vlOffset lPointer = (vlOffset)this->uiPointer + lOffset;

	if(lPointer < 0)
	{
		lPointer = 0;
	}

	if(lPointer > (vlOffset)this->uiLength)
	{
		lPointer = (vlOffset)this->uiLength;
	}

	this->uiPointer = (vlSize)lPointer;

	return (vlSSize)this->uiPointer;
}

vlBool CMemoryWriter::Write(vlChar cChar)
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
		*((vlChar *)this->vData + this->uiPointer++) = cChar;

		this->uiLength++;

		return vlTrue;
	}
}

vlSize CMemoryWriter::Write(vlVoid *vData, vlSize uiBytes)
{
	if(!this->bOpened)
	{
		return 0;
	}

	if(this->uiPointer == this->uiBufferSize)
	{
		return 0;
	}
	else if(this->uiPointer + uiBytes > this->uiBufferSize)
	{
		uiBytes = this->uiBufferSize - this->uiPointer;

		memcpy((vlByte *)this->vData + this->uiPointer, vData, uiBytes);

		this->uiLength += uiBytes;

		this->uiPointer = this->uiBufferSize;

		LastError.Set("End of memory stream.");

		return uiBytes;
	}
	else
	{
		memcpy((vlByte *)this->vData + this->uiPointer, vData, uiBytes);

		this->uiLength += uiBytes;

		this->uiPointer += uiBytes;

		return uiBytes;
	}
}
