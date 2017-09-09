cmake_minimum_required (VERSION 3.0.2)
project (TidyEngine CXX)
set(CMAKE_CXX_STANDARD 17)

if (WIN32)
	option(BUILD_EXTERNAL_DEPENDENCIES "Build all the required dependencies with the engine" TRUE)
else ()
	option(BUILD_EXTERNAL_DEPENDENCIES "Build all the required dependencies with the engine" FALSE)
endif()

add_subdirectory("${CMAKE_SOURCE_DIR}/deps/glad")
if (BUILD_EXTERNAL_DEPENDENCIES)
	include(ExternalProject)

	ExternalProject_Add(assimp
		GIT_SUBMODULES ${CMAKE_SOURCE_DIR}deps/assimp
		PREFIX ${CMAKE_SOURCE_DIR}deps/assimp
		SOURCE_DIR ${CMAKE_SOURCE_DIR}/deps/assimp
		INSTALL_DIR ${CMAKE_SOURCE_DIR}/deps/install
		CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/deps/install
	)
	ExternalProject_Add(freetype2
		GIT_SUBMODULES "deps/freetype2"
		SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/freetype2"
		INSTALL_DIR ${CMAKE_SOURCE_DIR}/deps/install
		CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/deps/install
	)
	ExternalProject_Add(glfw
		GIT_SUBMODULES "deps/glfw"
		SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/glfw"
		INSTALL_DIR ${CMAKE_SOURCE_DIR}/deps/install
		CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/deps/install
	)
	ExternalProject_Add(ogg
		GIT_SUBMODULES "deps/ogg"
		SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/ogg"
		INSTALL_DIR ${CMAKE_SOURCE_DIR}/deps/install
		CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/deps/install
	)
	ExternalProject_Add(openal-soft
		GIT_SUBMODULES "deps/openal-soft"
		SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/openal-soft"
		INSTALL_DIR ${CMAKE_SOURCE_DIR}/deps/install
		CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/deps/install
	)
	ExternalProject_Add(vorbis 
		DEPENDS ogg
		GIT_SUBMODULES "deps/vorbis"
		SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/vorbis"
		INSTALL_DIR ${CMAKE_SOURCE_DIR}/deps/install
		CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/deps/install
	)

	add_library(ASSIMP STATIC IMPORTED)
	set_property(TARGET ASSIMP PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/deps/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}assimp-vc140-mt${CMAKE_STATIC_LIBRARY_SUFFIX})

	add_library(FREETYPE2 STATIC IMPORTED)
	set_property(TARGET FREETYPE2 PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/deps/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}freetyped${CMAKE_STATIC_LIBRARY_SUFFIX})

	add_library(GLFW STATIC IMPORTED)
	set_property(TARGET GLFW PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/deps/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}glfw3${CMAKE_STATIC_LIBRARY_SUFFIX})

	add_library(LUAJIT STATIC IMPORTED)
	set_property(TARGET LUAJIT PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/deps/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}luajit${CMAKE_STATIC_LIBRARY_SUFFIX})

	add_library(LUA STATIC IMPORTED)
	set_property(TARGET LUA PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/deps/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}lua51${CMAKE_STATIC_LIBRARY_SUFFIX})

	add_library(OGG STATIC IMPORTED)
	set_property(TARGET OGG PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/deps/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}ogg${CMAKE_STATIC_LIBRARY_SUFFIX})

	add_library(OPENAL STATIC IMPORTED)
	set_property(TARGET OPENAL PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/deps/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}OpenAL32${CMAKE_STATIC_LIBRARY_SUFFIX})

	add_library(VORBIS STATIC IMPORTED)
	set_property(TARGET VORBIS PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/deps/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}vorbis${CMAKE_STATIC_LIBRARY_SUFFIX})

	add_library(VORBISFILE STATIC IMPORTED)
	set_property(TARGET VORBISFILE PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/deps/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}vorbisfile${CMAKE_STATIC_LIBRARY_SUFFIX})
elseif (APPLE)
	message("MACOSX: Not yet supported!")
elseif (UNIX)
	find_package(PkgConfig REQUIRED)
	pkg_search_module(ASSIMP REQUIRED assimp)
	pkg_search_module(GLFW REQUIRED glfw3)
	pkg_search_module(FREEIMAGE REQURIED freeimage)
	pkg_search_module(LUAJIT REQUIRED luajit)
	pkg_search_module(OPENAL REQUIRED openal)
	pkg_search_module(OGG REQUIRED ogg)
	pkg_search_module(VORBIS REQUIRED vorbis)
	pkg_search_module(VORBISFILE REQUIRED vorbisfile)
	pkg_search_module(FREETYPE2 REQUIRED freetype2)
	set(GLAD_LIBRARIES
		${GLAD_LIBRARIES}
		-ldl
		${CMAKE_BINARY_DIR}/deps/glad/libglad.a
	)
endif ()

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
target_include_directories(TidyEngine
	PUBLIC
	(
		${CMAKE_SOURCE_DIR}/deps/install/include/freetype2
		${CMAKE_SOURCE_DIR}/deps/install/include/AL
		${CMAKE_SOURCE_DIR}/deps/install/include
		${CMAKE_SOURCE_DIR}/deps/glm
		${CMAKE_SOURCE_DIR}/deps
		${GLFW_INCLUDE_DIRS}
		${FREEIMAGE_INCLUDE_DIRS}
		${LUAJIT_INCLUDE_DIRS}
		${OPENAL_INCLUDE_DIRS}
		${OGG_INCLUDE_DIRS}
		${VORBIS_INCLUDE_DIRS}
		${FREETYPE2_INCLUDE_DIRS}
		${ASSIMP_INCLUDE_DIRS}
		${CMAKE_SOURCE_DIR}/libTidyEngine
	)
)

option(BUILD_DEMO "Build a demo along side the engine" TRUE)
if (BUILD_DEMO)
	add_subdirectory("${CMAKE_SOURCE_DIR}/demo")
endif ()
