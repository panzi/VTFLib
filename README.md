VTFLib
======

This is a Linux port of [VTFLib](http://nemesis.thewavelength.net/index.php?c=149).

### Setup

	git clone https://github.com/panzi/VTFLib.git
	mkdir VTFLib/build
	cd VTFLib/build
	cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
	make -j`nproc`
	sudo make install

You may use the cmake option `-DUSE_LIBTXC_DXTN=ON`/`OFF` to enable/disable
support for writing S3TC compressed textures.

### Missing Features

There are several features that aren't currently supported by the Linux
version because they depend on a legacy Windows library
([nvDXTLib](http://developer.nvidia.com/object/dds_utilities_legacy.html)).
Such features are:

 * genratig mipmaps
 * resizing textures and generating thumbnails
 * generating normal maps/normal map conversion

However, all read-only features are supported.

### Dependencies

 * [libtxc\_dxtn](http://cgit.freedesktop.org/~mareko/libtxc_dxtn/) for writing S3TC
   compressed textures (optional).

### Documentation

[Doxygen API Reference](http://panzi.github.io/VTFLib/)

### Projects Using VTFLib for Linux

 * [pixbufloader-vtf](https://github.com/panzi/pixbufloader-vtf) - load VTF files in
   Gtk+ applications
 * [qvtf](https://github.com/panzi/qvtf) - load VTF files in Qt applications
 * [KIO Thumbnail VTF Plugin](https://github.com/panzi/KIO-VTF-Thumb-Creator) - show
   thumbnails for VTF files in KDE

### License

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.
