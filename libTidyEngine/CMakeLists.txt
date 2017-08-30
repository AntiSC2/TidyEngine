cmake_minimum_required (VERSION 3.2.3)

#Setting up the version number for the engine
set(TidyEngine_VERSION_MAJOR 0)
set(TidyEngine_VERSION_MINOR 2)

configure_file(
	"${CMAKE_BINARY_DIR}/config.hpp.in"
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

if (WIN32)
	if (MSVC)
		set(GLFW_LIBRARIES
			${GLFW_LIBRARIES}
			${CMAKE_SOURCE_DIR}/deps/lib/glfw3dll.lib
		)
		set(OGG_LIBRARIES
			${CMAKE_SOURCE_DIR}/deps/lib/libogg.lib
		)
		set(VORBISFILE_LIBRARIES
			${VORBISFILE_LIBRARIES}
			${CMAKE_SOURCE_DIR}/deps/lib/libvorbisfile.lib
		)
		set(VORBIS_LIBRARIES
			${OPENAL_LIBRARIES}
			${CMAKE_SOURCE_DIR}/deps/lib/libvorbis.lib
		)
		set(FREETYPE2_LIBRARIES
			${FREETYPE2_LIBRARIES}
			${CMAKE_SOURCE_DIR}/deps/lib/freetype.lib
		)
		set(GLAD_LIBRARIES
			${GLAD_LIBRARIES}
			${CMAKE_BINARY_DIR}/glad/Debug/glad.lib
		)
	else ()
		set(GLFW_LIBRARIES
			${GLFW_LIBRARIES}
			${CMAKE_SOURCE_DIR}/deps/lib/libglfw3.a
		)
		set(OGG_LIBRARIES
			${CMAKE_SOURCE_DIR}/deps/lib/libogg.a
		)
		set(VORBISFILE_LIBRARIES
			${VORBISFILE_LIBRARIES}
			${CMAKE_SOURCE_DIR}/deps/lib/libvorbisfile.a
		)
		set(VORBIS_LIBRARIES
			${VORBIS_LIBRARIES}
			${CMAKE_SOURCE_DIR}/deps/lib/libvorbis.a
		)
		set(FREETYPE2_LIBRARIES
			${FREETYPE2_LIBRARIES}
			${CMAKE_SOURCE_DIR}/deps/lib/libfreetype.a
		)
		set(GLAD_LIBRARIES
			${GLAD_LIBRARIES}
			${CMAKE_BINARY_DIR}/glad/libglad.a
		)
	endif ()

	set(ASSIMP_INCLUDE_DIRS
		${ASSIMP_INCLUDE_DIRS}
		${CMAKE_SOURCE_DIR}/deps/assimp/include
	)
	set(ASSIMP_LIBRARIES
		${ASSIMP_LIBRARIES}
		${CMAKE_SOURCE_DIR}/deps/libs/libassimp.dll
	)
	set(GLFW_INCLUDE_DIRS
		${GLFW_INCLUDE_DIRS}
		${CMAKE_SOURCE_DIR}/deps/glfw/include
	)
	set(FREEIMAGE_INCLUDE_DIRS
		${FREEIMAGE_INCLUDE_DIRS}
		${CMAKE_SOURCE_DIR}/deps/FreeImage/Source
	)
	set(FREEIMAGE_LIBRARIES
		${FREEIMAGE_LIBRARIES}
		${CMAKE_SOURCE_DIR}/deps/FreeImage.lib
	)
	set(LUAJIT_INCLUDE_DIRS
		${LUAJIT_INCLUDE_DIRS}
		${CMAKE_SOURCE_DIR}/deps/luajit-2.0/src
	)
	set(LUAJIT_LIBRARIES
		${LUAJIT_LIBRARIES}
		${CMAKE_SOURCE_DIR}/deps/lib/lua51.dll
	)
	set(OPENAL_INCLUDE_DIRS
		${OPENAL_INCLUDE_DIRS}
		${CMAKE_SOURCE_DIR}/deps/openal-soft/include
	)
	set(OPENAL_LIBRARIES
		${OPENAL_LIBRARIES}
		${CMAKE_SOURCE_DIR}/deps/lib/OpenAL32.lib
	)
	set(OGG_INCLUDE_DIRS
		${CMAKE_SOURCE_DIR}/deps/ogg/include
	)
	set(VORBIS_INCLUDE_DIRS
		${VORBIS_INCLUDE_DIRS}
		${CMAKE_SOURCE_DIR}/deps/vorbis/include
	)
	set(FREETYPE2_INCLUDE_DIRS
		${FREETYPE2_INCLUDE_DIRS}
		${CMAKE_SOURCE_DIR}/deps/freetype2/include
	)
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

target_include_directories(TidyEngine PUBLIC ${CMAKE_SOURCE_DIR}/deps/glm ${CMAKE_SOURCE_DIR}/deps)
target_include_directories(TidyEngine PUBLIC ${GLFW_INCLUDE_DIRS})
target_include_directories(TidyEngine PUBLIC ${FREEIMAGE_INCLUDE_DIRS})
target_include_directories(TidyEngine PUBLIC ${LUAJIT_INCLUDE_DIRS})
target_include_directories(TidyEngine PUBLIC ${OPENAL_INCLUDE_DIRS})
target_include_directories(TidyEngine PUBLIC ${OGG_INCLUDE_DIRS})
target_include_directories(TidyEngine PUBLIC ${VORBIS_INCLUDE_DIRS})
target_include_directories(TidyEngine PUBLIC ${FREETYPE2_INCLUDE_DIRS})
target_include_directories(TidyEngine PUBLIC ${ASSIMP_INCLUDE_DIRS})
target_include_directories(TidyEngine INTERFACE .)

if (WIN32)
	target_link_libraries(${PROJECT_NAME} opengl32.lib)
endif ()
