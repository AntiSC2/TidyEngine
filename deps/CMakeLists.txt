cmake_minimum_required (VERSION 3.2.3)

include(ExternalProject)

ExternalProject_Add("assimp"
	GIT_SUBMODULES "deps/assimp"
	SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/glfw"
)
if (MSVC)
	ExternalProject_Add("FreeImage"
		SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/FreeImage"
		BUILD_COMMAND "MSBUILD.exe FreeImage.2013.vcxproj /property:Configuration=Realese /p:PlatformToolset=v141"
	)
else ()
	ExternalProject_Add("FreeImage"
		SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/FreeImage"
		BUILD_COMMAND "make"
	)
endif()
ExternalProject_Add("freetype2"
	GIT_SUBMODULES "deps/freetype2"
	SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/freetype2"
)
ExternalProject_Add("glfw"
	GIT_SUBMODULES "deps/glfw"
	SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/glfw"
)
ExternalProject_Add("luajit-2.0"
	GIT_SUBMODULES "deps/luajit-2.0"
	SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/luajit-2.0"
)
ExternalProject_Add("ogg"
	GIT_SUBMODULES "deps/ogg"
	SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/ogg"
)
ExternalProject_Add("openal-soft"
	GIT_SUBMODULES "deps/openal-soft"
	SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/openal-soft"
)
ExternalProject_Add("vorbis" 
	DEPENDS "ogg"
	GIT_SUBMODULES "deps/vorbis"
	SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/vorbis"
)