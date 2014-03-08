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

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	add_subdirectory(windows)
else()
	add_subdirectory(unix)
endif()

add_library(vtflib ${vtflib_SRCS})
