/*
 * VTFLib
 * Copyright (C) 2014 Mathias Panzenböck

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#include "../VTFLib.h"
#include "../VTFFile.h"
#include "../VMTFile.h"

using namespace VTFLib;

struct LibCallbacks {
	LibCallbacks() {}

	~LibCallbacks() {
		vlShutdown();
	}
};

// gcc actually calls constructors and destructors of global objects in libraries
static LibCallbacks libCallbacks;
