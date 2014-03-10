/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#include <sys/stat.h>

#include "../VTFLib.h"
#include "../FileReader.h"

using namespace VTFLib;
using namespace VTFLib::IO::Readers;

vlBool CFileReader::Open()
{
	this->Close();

	this->hFile = fopen(this->cFileName, "rb");

	if(this->hFile == NULL)
	{
		LastError.Set("Error opening file.", vlTrue);

		return vlFalse;
	}

	return vlTrue;
}

vlVoid CFileReader::Close()
{
	if(this->hFile != NULL)
	{
		fclose(this->hFile);
		this->hFile = NULL;
	}
}

vlSSize CFileReader::GetStreamSize() const
{
	if(this->hFile == NULL)
	{
		return 0;
	}

	struct stat buf;

	if(fstat(fileno(this->hFile), &buf) != 0) {
		LastError.Set("fstat() failed.", vlTrue);
		return 0;
	}

	return buf.st_size;
}

vlSSize CFileReader::GetStreamPointer() const
{
	if(this->hFile == NULL)
	{
		return 0;
	}

	vlOffset offset = ftello(this->hFile);
	if(offset < 0)
	{
		LastError.Set("ftello() failed.", vlTrue);
		return 0;
	}

	return offset;
}

vlSSize CFileReader::Seek(vlOffset lOffset, VLSeekMode uiMode)
{
	if(this->hFile == NULL)
	{
		return 0;
	}

	if(fseeko(this->hFile, lOffset, uiMode) != 0) {
		LastError.Set("fseeko() failed.", vlTrue);
		return 0;
	}
	return GetStreamPointer();
}

vlBool CFileReader::Read(vlChar &cChar)
{
	if(this->hFile == NULL)
	{
		return vlFalse;
	}
	
	int byte = fgetc(this->hFile);

	if(byte == EOF)
	{
		LastError.Set("fgetc() failed.", vlTrue);
		return vlFalse;
	}
	else
	{
		cChar = (vlChar)byte;
		return vlTrue;
	}
}

vlSize CFileReader::Read(vlVoid *vData, vlSize uiBytes)
{
	if(this->hFile == NULL)
	{
		return 0;
	}

	if(fread(vData, uiBytes, 1, this->hFile) != 1 && ferror(this->hFile))
	{
		LastError.Set("fread() failed.", vlTrue);
		return 0;
	}
	else
	{
		return uiBytes;
	}
}
