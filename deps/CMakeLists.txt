cmake_minimum_required (VERSION 3.2.3)

include(ExternalProject)

ExternalProject_Add(assimp
	GIT_SUBMODULES ${CMAKE_SOURCE_DIR}deps/assimp
	PREFIX ${CMAKE_SOURCE_DIR}deps/assimp
	SOURCE_DIR ${CMAKE_SOURCE_DIR}/deps/assimp
	INSTALL_DIR ${CMAKE_SOURCE_DIR}/deps/install
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/deps/install
)
if (MSVC)
	ExternalProject_Add(FreeImage
		SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/FreeImage"
		BUILD_COMMAND "MSBUILD.exe FreeImage.2013.vcxproj /property:Configuration=Realese /p:PlatformToolset=v141"
		INSTALL_DIR ${CMAKE_SOURCE_DIR}/deps/install
		CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/deps/install
	)
else ()
	ExternalProject_Add(FreeImage
		SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/FreeImage"
		BUILD_COMMAND "make"
		INSTALL_DIR ${CMAKE_SOURCE_DIR}/deps/install
		CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/deps/install
	)
endif()
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
ExternalProject_Add(luajit-2.0
	GIT_SUBMODULES "deps/luajit-2.0"
	SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/luajit-2.0"
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