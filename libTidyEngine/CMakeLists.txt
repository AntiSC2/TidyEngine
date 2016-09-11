cmake_minimum_required (VERSION 3.2.3)
project(TidyEngine)

#Setting up the version number for the engine
set(TidyEngine_VERSION_MAJOR 0)
set(TidyEngine_VERSION_MINOR 2)

configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in"
	"${CMAKE_BINARY_DIR}/config.hpp"
)
include_directories(${CMAKE_BINARY_DIR})

set(SOURCE
	${SOURCE}
	${CMAKE_CURRENT_SOURCE_DIR}/core.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/screen.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/render.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/shader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/error.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/texture.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/renderable.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/batch.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/iomanager.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/cache.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/rect2d.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/renderer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/spriterenderer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/camera2d.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/input.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/object.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/objectmanager.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/sheet.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/sprite.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/vm.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/audio.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/sample.cpp
)
set(HEADERS
	${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/core.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/screen.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/render.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/shader.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/error.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/texture.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/vertex.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/renderable.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/batch.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/iomanager.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/cache.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/rect2d.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/renderer.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/spriterenderer.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/camera2d.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/input.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/object.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/objectmanager.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/sheet.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/sprite.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/vm.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/audio.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/sample.hpp
)

if (WIN32)
	include_directories(${CMAKE_SOURCE_DIR}/deps/include)
	set(GLFW_INCLUDE_DIRS
		${GLFW_INCLUDE_DIRS}
		${CMAKE_SOURCE_DIR}/deps/include/GLFW
	)
	set(GLFW_LIBRARIES
		${GLFW_LIBRARIES}
		${CMAKE_SOURCE_DIR}/deps/lib/glfw3dll.lib
	)
	set(GLEW_INCLUDE_DIRS
		${GLEW_INCLUDE_DIRS}
		${CMAKE_SOURCE_DIR}/deps/include/GL
	)
	set(GLEW_LIBRARIES
		${GLEW_LIBRARIES}
		${CMAKE_SOURCE_DIR}/deps/lib/glew32.lib
	)
	set(FREEIMAGE_INCLUDE_DIRS
		${FREEIMAGE_INCLUDE_DIRS}
		${CMAKE_SOURCE_DIR}/deps/include/FreeImage
	)
	set(FREEIMAGE_LIBRARIES
		${FREEIMAGE_LIBRARIES}
		${CMAKE_SOURCE_DIR}/deps/lib/FreeImage.lib
	)
	set(LUAJIT_INCLUDE_DIRS
		${LUAJIT_INCLUDE_DIRS}
		${CMAKE_SOURCE_DIR}/deps/include/LuaJIT
	)
	set(LUAJIT_LIBRARIES
		${LUAJIT_LIBRARIES}
		${CMAKE_SOURCE_DIR}/deps/lib/lua51.lib
	)
	set(OPENAL_INCLUDE_DIRS
		${OPENAL_INCLUDE_DIRS}
		${CMAKE_SOURCE_DIR}/deps/include/OpenAL
	)
	set(OPENAL_LIBRARIES
		${OPENAL_LIBRARIES}
		${CMAKE_SOURCE_DIR}/deps/lib/OpenAL32.lib
		${CMAKE_SOURCE_DIR}/deps/lib/EFX-Util.lib
	)
	set(OGG_INCLUDE_DIRS
		${OGG_INCLUDE_DIRS}
		${CMAKE_SOURCE_DIR}/deps/include/ogg
	)
	set(OGG_LIBRARIES
		${OPENAL_LIBRARIES}
		${CMAKE_SOURCE_DIR}/deps/lib/libogg.lib
	)
	set(VORBIS_INCLUDE_DIRS
		${VORBIS_INCLUDE_DIRS}
		${CMAKE_SOURCE_DIR}/deps/include/vorbis
	)
	set(VORBIS_LIBRARIES
		${OPENAL_LIBRARIES}
		${CMAKE_SOURCE_DIR}/deps/lib/libvorbis.lib
		${CMAKE_SOURCE_DIR}/deps/lib/libvorbisfile.lib
	)
endif ()

if (APPLE)

elseif (UNIX)
	find_package(PkgConfig REQUIRED)
	pkg_search_module(GLFW REQUIRED glfw3)
	pkg_search_module(GLEW REQUIRED glew)
	pkg_search_module(FREEIMAGE REQURIED freeimage)
	pkg_search_module(LUAJIT REQUIRED luajit)
	pkg_search_module(OPENAL REQUIRED openal)
	pkg_search_module(OGG REQUIRED ogg)
	pkg_search_module(VORBIS REQUIRED vorbis)
	pkg_search_module(VORBISFILE REQUIRED vorbisfile)
endif ()

include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${FREEIMAGE_INCLUDE_DIRS})
include_directories(${LUAJIT_INCLUDE_DIRS})
include_directories(${OPENAL_INCLUDE_DIRS})
include_directories(${OGG_INCLUDE_DIRS})
include_directories(${VORBIS_INCLUDE_DIRS})
include_directories(${VORBISFILE_INCLUDE_DIRS})

add_library(${PROJECT_NAME} STATIC ${SOURCE} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES}
				   ${GLEW_LIBRARIES}
				   ${FREEIMAGE_LIBRARIES}
				   ${LUAJIT_LIBRARIES}
				   ${OPENAL_LIBRARIES}
				   ${OGG_LIBRARIES}
                                   ${VORBIS_LIBRARIES}
                                   ${VORBISFILE_LIBRARIES})

if (WIN32)
	target_link_libraries(${PROJECT_NAME} opengl32.lib)
endif ()
