/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg
 *               2014      Mathias Panzenböck

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#include "../Error.h"

using namespace VTFLib::Diagnostics;

vlVoid CError::Set(const vlChar *cErrorMessage, vlBool bSystemError)
{
	vlChar cBuffer[2048];
	if(bSystemError)
	{
		LPVOID lpMessage;
		vlUInt uiLastError = GetLastError(); 

		if(FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, uiLastError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&lpMessage, 0, NULL))
		{
			snprintf(cBuffer, sizeof(cBuffer), "Error:\n%s\n\nSystem Error: 0x%.8x:\n%s", cErrorMessage, uiLastError, lpMessage); 

			LocalFree(lpMessage);
		}
		else
		{
			snprintf(cBuffer, sizeof(cBuffer), "Error:\n%s\n\nSystem Error: 0x%.8x.", cErrorMessage, uiLastError); 
		}

		
	}
	else
	{
		snprintf(cBuffer, sizeof(cBuffer), "Error:\n%s", cErrorMessage); 
	}
	
	this->cErrorMessage = new vlChar[strlen(cBuffer) + 1];
	strcpy(this->cErrorMessage, cBuffer);
}
