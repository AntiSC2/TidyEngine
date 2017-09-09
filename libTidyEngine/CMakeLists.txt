cmake_minimum_required (VERSION 3.0.2)

#Setting up the version number for the engine
set(TidyEngine_VERSION_MAJOR 0)
set(TidyEngine_VERSION_MINOR 2)

configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/config.hpp"
)

set(SOURCE
	${SOURCE}
	${CMAKE_CURRENT_SOURCE_DIR}/core.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/system.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/screen.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/graphics.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/shader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/texture.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/renderable.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/iomanager.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/cache.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/rect2d.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/renderer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/spriterenderer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/camera.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/input.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/component.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/entity.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/entitymanager.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/sprite.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/luascript.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/audio.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/sample.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/font.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/fontglyph.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mesh.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/modelrenderer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/model.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/material.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/pointlight.cpp
)

add_library(TidyEngine STATIC ${SOURCE})
target_link_libraries(TidyEngine GLFW
                                 glad
                                 LUA
                                 LUAJIT
                                 OPENAL
                                 OGG
                                 VORBIS
                                 VORBISFILE
                                 FREETYPE2
                                 ASSIMP)

# Ensure that the external projects are built first
if (BUILD_EXTERNAL_DEPENDENCIES)
	add_dependencies(TidyEngine assimp glfw freetype2 vorbis openal-soft LUAJIT)
endif ()

if (WIN32)
	target_link_libraries(TidyEngine opengl32.lib)
endif ()
