/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#ifndef VTFLIB_MEMORYWRITER_H
#define VTFLIB_MEMORYWRITER_H

#include "stdafx.h"
#include "Writer.h"

namespace VTFLib
{
	namespace IO
	{
		namespace Writers
		{
			class CMemoryWriter : public IWriter
			{
			private:
				vlBool bOpened;

				vlVoid *vData;
				vlSize uiBufferSize;

				vlSize uiPointer;
				vlSize uiLength;

			public:
				CMemoryWriter(vlVoid *vData, vlSize uiBufferSize);
				~CMemoryWriter();

			public:
				virtual vlBool Opened() const;

				virtual vlBool Open();
				virtual vlVoid Close();

				virtual vlSSize GetStreamSize() const;
				virtual vlSSize GetStreamPointer() const;

				virtual vlSSize Seek(vlOffset lOffset, VLSeekMode uiMode);

				virtual vlBool Write(vlChar cChar);
				virtual vlSize Write(vlVoid *vData, vlSize uiBytes);
			};
		}
	}
}

#endif
