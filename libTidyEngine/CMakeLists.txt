cmake_minimum_required (VERSION 3.2.3)

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
	${CMAKE_CURRENT_SOURCE_DIR}/error.cpp
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
target_link_libraries(TidyEngine ${GLFW_LIBRARIES}
                                 ${GLAD_LIBRARIES}
                                 ${FREEIMAGE_LIBRARIES}
                                 ${LUAJIT_LIBRARIES}
                                 ${OPENAL_LIBRARIES}
                                 ${OGG_LIBRARIES}
                                 ${VORBIS_LIBRARIES}
                                 ${VORBISFILE_LIBRARIES}
                                 ${FREETYPE2_LIBRARIES}
                                 ${ASSIMP_LIBRARIES})

# Ensure that the external projects are built first
if (MSVC)
	if (BUILD_EXTERNAL_DEPENDENCIES)
		add_dependencies(TidyEngine assimp glfw freetype2 vorbis openal-soft FreeImage luajit-2.0)
	endif ()
endif ()

if (WIN32)
	target_link_libraries(${PROJECT_NAME} opengl32.lib)
endif ()
