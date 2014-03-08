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

#include "Error.h"

using namespace VTFLib::Diagnostics;

CError::CError()
{
	this->cErrorMessage = 0;
}

CError::~CError()
{
	delete []this->cErrorMessage;
}

vlVoid CError::Clear()
{
	delete []this->cErrorMessage;
	this->cErrorMessage = 0;
}

const vlChar *CError::Get() const
{
	return this->cErrorMessage != 0 ? this->cErrorMessage : "";
}

vlVoid CError::SetFormatted(const vlChar *cFormat, ...)
{
	vlChar cBuffer[2048];

	va_list ArgumentList;
	va_start(ArgumentList, cFormat);
	vsnprintf(cBuffer, sizeof(cBuffer), cFormat, ArgumentList);
	va_end(ArgumentList);

	this->Set(cBuffer, vlFalse);
}
