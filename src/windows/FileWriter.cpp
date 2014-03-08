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
#include "FileWriter.h"

using namespace VTFLib;
using namespace VTFLib::IO::Writers;

vlBool CFileWriter::Open()
{
	this->Close();

	this->hFile = CreateFile(this->cFileName, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(this->hFile == INVALID_HANDLE_VALUE)
	{
		this->hFile = NULL;

		LastError.Set("Error opening file.", vlTrue);

		return vlFalse;
	}

	return vlTrue;
}

vlVoid CFileWriter::Close()
{
	if(this->hFile != NULL)
	{
		CloseHandle(this->hFile);
		this->hFile = NULL;
	}
}

vlSSize CFileWriter::GetStreamSize() const
{
	if(this->hFile == NULL)
	{
		return 0;
	}

	return GetFileSize(this->hFile, NULL);
}

vlSSize CFileWriter::GetStreamPointer() const
{
	if(this->hFile == NULL)
	{
		return 0;
	}

	return (vlSSize)SetFilePointer(this->hFile, 0, NULL, FILE_CURRENT);
}

vlSSize CFileWriter::Seek(vlOffset lOffset, VLSeekMode uiMode)
{
	if(this->hFile == NULL)
	{
		return 0;
	}

	return (vlSSize)SetFilePointer(this->hFile, lOffset, NULL, (vlUInt)uiMode);
}

vlBool CFileWriter::Write(vlChar cChar)
{
	if(this->hFile == NULL)
	{
		return vlFalse;
	}

	vlULong ulBytesWritten = 0;

	if(!WriteFile(this->hFile, &cChar, 1, &ulBytesWritten, NULL))
	{
		LastError.Set("WriteFile() failed.", vlTrue);
	}

	return ulBytesWritten == 1;
}

vlSize CFileWriter::Write(vlVoid *vData, vlSize uiBytes)
{
	if(this->hFile == NULL)
	{
		return 0;
	}

	vlULong ulBytesWritten = 0;

	if(!WriteFile(this->hFile, vData, uiBytes, &ulBytesWritten, NULL))
	{
		LastError.Set("WriteFile() failed.", vlTrue);
	}

	return (vlSize)ulBytesWritten;
}
