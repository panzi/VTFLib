/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg
 *               2021 MihailNaydenov

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

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

	const long start_pos = ftell(this->hFile);
  int err = (start_pos < 0);
	err |= fseek(this->hFile, 0, SEEK_END);
  const long end_pos = ftell(this->hFile);
  err |= (end_pos < 0);
	const vlSSize file_length = end_pos - start_pos;
	err |= fseek(this->hFile, start_pos, SEEK_SET);

	if(err != 0) {
		LastError.Set("GetStreamSize() failed.", vlTrue);
		return 0;
	}

	return file_length;
}

vlSSize CFileReader::GetStreamPointer() const
{
	if(this->hFile == NULL)
	{
		return 0;
	}

	long offset = ftell(this->hFile);
	if(offset < 0)
	{
		LastError.Set("GetStreamPointer() failed.", vlTrue);
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

	if(fseek(this->hFile, lOffset, uiMode) != 0) {
		LastError.Set("Seek() failed.", vlTrue);
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
		LastError.Set("Read() failed.", vlTrue);
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
		LastError.Set("Read() failed.", vlTrue);
		return 0;
	}
	else
	{
		return uiBytes;
	}
}
