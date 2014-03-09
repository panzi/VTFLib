cmake_minimum_required(VERSION 2.8)

project(VTFLib)

set(VTFLIB_MAJOR_VERSION 1)
set(VTFLIB_MINOR_VERSION 3)
set(VTFLIB_PATCH_VERSION 2)

set(VTFLIB_NAME VTFLib${VTFLIB_MAJOR_VERSION}${VTFLIB_MINOR_VERSION})
set(VTFLIB_VERSION ${VTFLIB_MAJOR_VERSION}.${VTFLIB_MINOR_VERSION}.${VTFLIB_PATCH_VERSION})

# ---- options ----------------------------------------------------------------
option(USE_NVDXT "(Windows only) VTF creation requires nvDXTLib and has been
tested with version 8.31.1127.1645, availible here:
http://developer.nvidia.com/object/dds_utilities_legacy.html" OFF)

# ---- compiler flags ---------------------------------------------------------
if(MSVC)
	# Force to always compile with W4
	if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	# Update if necessary
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic -Werror -O2")
endif()

if(USE_NVDXT AND ${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	add_definitions(-DUSE_NVDXT)
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	# big file support (files > 2GB). makes off_t 64bit even on 32bit platforms and makes fseeko/ftello available.
	set(VTFLIB_PC_CFLAGS "-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE")
	add_definitions(${VTFLIB_PC_CFLAGS})
endif()

# for config.h
include_directories("${PROJECT_BINARY_DIR}/src")

# ---- pkg config -------------------------------------------------------------
# for CMAKE_INSTALL_LIBDIR:
include(GNUInstallDirs)

# from libpng
# Set a variable with CMake code which:
# Creates a symlink from src to dest (if possible) or alternatively
# copies if different.
macro(vtflib_generate_symlink_code CODE SRC DEST WORKING_DIR)
	if(WIN32 AND NOT CYGWIN)
		set(_vtflib_gsc_message "Copying ${SRC} to ${DEST} if needed")
		set(_vtflib_gsc_operation "copy_if_different")
	else()
		set(_vtflib_gsc_message "Symlinking ${SRC} to ${DEST}")
		set(_vtflib_gsc_operation "create_symlink")
	endif()

	set(${CODE} "
		message(STATUS \"${_vtflib_gsc_message}\")
		execute_process(COMMAND \${CMAKE_COMMAND} -E ${_vtflib_gsc_operation}
			\"${SRC}\" \"${DEST}\" WORKING_DIRECTORY \"${WORKING_DIR}\")
		")
endmacro()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/VTFLib.pc.in
	${CMAKE_CURRENT_BINARY_DIR}/${VTFLIB_NAME}.pc @ONLY)

vtflib_generate_symlink_code(VTFLIB_PC_INSTALL_CODE
	${VTFLIB_NAME}.pc
	VTFLib.pc
	${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/pkgconfig)

install(FILES
	${CMAKE_CURRENT_BINARY_DIR}/${VTFLIB_NAME}.pc
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
install(CODE ${VTFLIB_PC_INSTALL_CODE})

# ---- sub directories --------------------------------------------------------
add_subdirectory(src)

# ---- uninstall target -------------------------------------------------------
configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
	IMMEDIATE @ONLY)

add_custom_target(uninstall
	COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")
