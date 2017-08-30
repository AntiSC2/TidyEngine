cmake_minimum_required (VERSION 3.2.3)

include(ExternalProject)

ExternalProject_Add("assimp"
	GIT_SUBMODULES "deps/assimp"
	GIT_REPOSITORY "https://github.com/assimp/assimp"
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
	GIT_REPOSITORY "https://git.savannah.gnu.org/git/freetype/freetype2.git"
)
ExternalProject_Add("glfw"
	GIT_SUBMODULES "deps/glfw"
	GIT_REPOSITORY "https://github.com/glfw/glfw"
)
ExternalProject_Add("luajit-2.0"
	GIT_SUBMODULES "deps/luajit-2.0"
	GIT_REPOSITORY "http://repo.or.cz/luajit-2.0.git"
)
ExternalProject_Add("ogg"
	GIT_SUBMODULES "deps/ogg"
	GIT_REPOSITORY "https://git.xiph.org/ogg.git"
)
ExternalProject_Add("openal-soft"
	GIT_SUBMODULES "deps/openal-soft"
	GIT_REPOSITORY "https://github.com/kcat/openal-soft"
)
ExternalProject_Add("vorbis" 
	DEPENDS "ogg"
	GIT_SUBMODULES "deps/vorbis"
	GIT_REPOSITORY "https://git.xiph.org/vorbis.git"
)