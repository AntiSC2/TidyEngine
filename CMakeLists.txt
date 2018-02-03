cmake_minimum_required (VERSION 3.0.2)
project (TidyEngine CXX)
set(CMAKE_CXX_STANDARD 17)

if (WIN32)
	option(BUILD_EXTERNAL_DEPENDENCIES "Build most of the required dependencies with the engine" TRUE)
else ()
	option(BUILD_EXTERNAL_DEPENDENCIES "Build most of the required dependencies with the engine" FALSE)
endif()

add_subdirectory("${CMAKE_SOURCE_DIR}/deps/glad")
if (BUILD_EXTERNAL_DEPENDENCIES)
	include(ExternalProject)

	ExternalProject_Add(assimp
		GIT_SUBMODULES ${CMAKE_SOURCE_DIR}deps/assimp
		PREFIX ${CMAKE_SOURCE_DIR}/deps/assimp
		SOURCE_DIR ${CMAKE_SOURCE_DIR}/deps/assimp
		INSTALL_DIR ${CMAKE_SOURCE_DIR}/deps/install
		CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/deps/install -DASSIMP_BUILD_ASSIMP_VIEW=OFF -DASSIMP_BUILD_TESTS=OFF
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
endif()

if (WIN32)
	set(ASSIMP_LIBRARIES
		${CMAKE_SOURCE_DIR}/deps/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}assimp-vc140-mt${CMAKE_STATIC_LIBRARY_SUFFIX}
	)
	set(FREETYPE2_LIBRARIES
		${CMAKE_SOURCE_DIR}/deps/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}freetyped${CMAKE_STATIC_LIBRARY_SUFFIX}
	)
	set(GLFW_LIBRARIES 
		${CMAKE_SOURCE_DIR}/deps/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}glfw3${CMAKE_STATIC_LIBRARY_SUFFIX}
	)
	set(LUAJIT_LIBRARIES
		${CMAKE_SOURCE_DIR}/deps/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}lua51${CMAKE_STATIC_LIBRARY_SUFFIX}	
		${CMAKE_SOURCE_DIR}/deps/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}luajit${CMAKE_STATIC_LIBRARY_SUFFIX}
	)
	set(OGG_LIBRARIES
		${CMAKE_SOURCE_DIR}/deps/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}ogg${CMAKE_STATIC_LIBRARY_SUFFIX}
	)
	set(OPENAL_LIBRARIES
		${CMAKE_SOURCE_DIR}/deps/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}OpenAL32${CMAKE_STATIC_LIBRARY_SUFFIX}
	)
	set(VORBIS_LIBRARIES
		${CMAKE_SOURCE_DIR}/deps/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}vorbis${CMAKE_STATIC_LIBRARY_SUFFIX}
	)
	set(VORBISFILE_LIBRARIES
		${CMAKE_SOURCE_DIR}/deps/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}vorbisfile${CMAKE_STATIC_LIBRARY_SUFFIX}
	)
	if (MSVC)
		set(GLAD_LIBRARIES
			${CMAKE_BINARY_DIR}/deps/glad/Debug/glad.lib
		)
	else ()
		set(GLAD_LIBRARIES
			${CMAKE_BINARY_DIR}/deps/glad/libglad.a
		)
	endif ()
elseif (APPLE)
	message("MACOSX: Not yet supported!")
elseif (UNIX)
	find_package(PkgConfig REQUIRED)
	find_package(OpenAL REQUIRED)
	find_package(Freetype REQUIRED)
	pkg_search_module(LUAJIT REQUIRED luajit)
	pkg_search_module(ASSIMP REQUIRED assimp)
	pkg_search_module(GLFW REQUIRED glfw3)
	pkg_search_module(FREEIMAGE REQURIED freeimage)
	pkg_search_module(OGG REQUIRED ogg)
	pkg_search_module(VORBIS REQUIRED vorbis)
	pkg_search_module(VORBISFILE REQUIRED vorbisfile)
	set(GLAD_LIBRARIES
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
if (WIN32)
	target_include_directories(TidyEngine
		PUBLIC
		(
			${CMAKE_SOURCE_DIR}/deps/install/include/freetype2
			${CMAKE_SOURCE_DIR}/deps/install/include/AL
			${CMAKE_SOURCE_DIR}/deps/install/include
			${CMAKE_SOURCE_DIR}/deps/glm
			${CMAKE_SOURCE_DIR}/deps
			${CMAKE_SOURCE_DIR}/libTidyEngine
		)
	)
else ()
	target_include_directories(TidyEngine
		PUBLIC
		(
			${CMAKE_SOURCE_DIR}/deps/install/include
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
endif ()

option(BUILD_DEMO2D "Build a 2D demo along side the engine" TRUE)
if (BUILD_DEMO2D)
	add_subdirectory("${CMAKE_SOURCE_DIR}/2Ddemo")
endif ()

option(BUILD_DEMO3D "Build a 3D demo along side the engine" TRUE)
if (BUILD_DEMO3D)
	add_subdirectory("${CMAKE_SOURCE_DIR}/3Ddemo")
endif ()