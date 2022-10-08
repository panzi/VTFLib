include(GenerateExportHeader)

set(vtflib_SRCS
	Error.cpp
	FileReader.cpp
	FileWriter.cpp
	Float16.cpp
	MemoryReader.cpp
	MemoryWriter.cpp
	Proc.cpp
	ProcReader.cpp
	ProcWriter.cpp
	VMTFile.cpp
	VMTGroupNode.cpp
	VMTIntegerNode.cpp
	VMTNode.cpp
	VMTSingleNode.cpp
	VMTStringNode.cpp
	VMTValueNode.cpp
	VMTWrapper.cpp
	VTFFile.cpp
	VTFLib.cpp
	VTFMathlib.cpp
	VTFWrapper.cpp)

set(vtflib_HDRS
	Error.h
	FileReader.h
	FileWriter.h
	Float16.h
	MemoryReader.h
	MemoryWriter.h
	Proc.h
	ProcReader.h
	ProcWriter.h
	Reader.h
	Readers.h
	resource.h
	stdafx.h
	VMTFile.h
	VMTGroupNode.h
	VMTIntegerNode.h
	VMTNode.h
	VMTNodes.h
	VMTSingleNode.h
	VMTStringNode.h
	VMTValueNode.h
	VMTWrapper.h
	VTFDXTn.h
	VTFFile.h
	VTFFormat.h
	VTFLib.h
	VTFMathlib.h
	VTFWrapper.h
	Writer.h
	Writers.h
	"${CMAKE_CURRENT_BINARY_DIR}/config.h")

configure_file(config.h.in "${CMAKE_CURRENT_BINARY_DIR}/config.h" @ONLY)
configure_file(Resource.rc.in "${CMAKE_CURRENT_BINARY_DIR}/Resource.rc" @ONLY)
configure_file(resource.h "${CMAKE_CURRENT_BINARY_DIR}/resource.h" COPYONLY)

if(MSVC)
	add_subdirectory(windows)
elseif(UNIX)
  add_subdirectory(unix)
else()
	add_subdirectory(generic)
endif()

add_compiler_export_flags()
add_library(${VTFLIB_NAME}
	${vtflib_SRCS}
	${vtflib_OS_SRCS}
	${vtflib_HDRS}
	"${CMAKE_CURRENT_BINARY_DIR}/Resource.rc")

if(USE_LIBTXC_DXTN)
	target_link_libraries(${VTFLIB_NAME} ${LIBTXC_DXTN_LIBRARY})
endif()

install(TARGETS ${VTFLIB_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${vtflib_HDRS} DESTINATION "include/${VTFLIB_NAME}")
