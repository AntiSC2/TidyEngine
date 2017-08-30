cmake_minimum_required (VERSION 3.2.3)
project (TidyEngine CXX)
set(CMAKE_CXX_STANDARD 17)

if (WIN32)
	add_subdirectory("${CMAKE_SOURCE_DIR}/deps")
endif()
add_subdirectory("${CMAKE_SOURCE_DIR}/deps/glad")

option(DEBUG "Add debug flags to the compiler" TRUE)
if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG)
	set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-function -Werror-implicit-function-declaration -Wno-missing-field-initializers ${CMAKE_CXX_FLAGS} -fno-strict-aliasing")
	if (DEBUG)
		set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Wno-unused-function -Werror-implicit-function-declaration -Wno-missing-field-initializers ${CMAKE_CXX_FLAGS} -fno-strict-aliasing")
	endif ()
elseif (MSVC)
	# Disable pointless constant condition warnings
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4127 /wd4201")
endif ()

add_subdirectory("${CMAKE_SOURCE_DIR}/libTidyEngine")

option(BUILD_TEST "Build a test along side the engine" TRUE)
if (BUILD_TEST)
        add_subdirectory("${CMAKE_SOURCE_DIR}/test")
endif ()
