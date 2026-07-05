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

#include <sys/stat.h>

#include "../VTFLib.h"
#include "../FileWriter.h"

using namespace VTFLib;
using namespace VTFLib::IO::Writers;

vlBool CFileWriter::Open()
{
	this->Close();

	this->hFile = fopen(this->cFileName, "wb");

	if(this->hFile == NULL)
	{
		LastError.Set("Error opening file.", vlTrue);

		return vlFalse;
	}

	return vlTrue;
}

vlVoid CFileWriter::Close()
{
	if(this->hFile != NULL)
	{
		fclose(this->hFile);
		this->hFile = NULL;
	}
}

vlSSize CFileWriter::GetStreamSize() const
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

vlSSize CFileWriter::GetStreamPointer() const
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

vlSSize CFileWriter::Seek(vlOffset lOffset, VLSeekMode uiMode)
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

vlBool CFileWriter::Write(vlChar cChar)
{
	if(this->hFile == NULL)
	{
		return vlFalse;
	}

	if(fputc(cChar, this->hFile) == EOF)
	{
		LastError.Set("Write() failed.", vlTrue);
		return vlFalse;
	}
	else
	{
		return vlTrue;
	}
}

vlSize CFileWriter::Write(vlVoid *vData, vlSize uiBytes)
{
	if(this->hFile == NULL)
	{
		return 0;
	}

	if (fwrite(vData, uiBytes, 1, this->hFile) != 1 && ferror(this->hFile))
	{
		LastError.Set("Write() failed.", vlTrue);
		return 0;
	}
	else
	{
		return uiBytes;
	}
}
