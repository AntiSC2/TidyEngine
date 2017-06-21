cmake_minimum_required (VERSION 3.2.3)
project(TEST)

include_directories(${CMAKE_SOURCE_DIR}/libTidyEngine)
include_directories(${CMAKE_BINARY_DIR})

set(SOURCES
	${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game.cpp
)
set(HEADERS
	${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/game.hpp
)

if (WIN32)
	if (MSVC)
		set(TIDYENGINE_LIBRARIES
			${TIDYENGINE_LIBRARIES}
			${CMAKE_BINARY_DIR}/libTidyEngine/Debug/TidyEngine.lib
		)
		set(BOX2D_LIBRARIES
			${BOX2D_LIBRARIES}
			${CMAKE_SOURCE_DIR}/deps/lib/libBox2D.lib
		)
		set(GLFW_LIBRARIES
			${GLFW_LIBRARIES}
			${CMAKE_SOURCE_DIR}/deps/lib/glfw3dll.lib
		)
		set(OGG_LIBRARIES
			${OGG_LIBRARIES}
			${CMAKE_SOURCE_DIR}/deps/lib/libogg.lib
		)
		set(VORBISFILE_LIBRARIES
			${VORBISFILE_LIBRARIES}
			${CMAKE_SOURCE_DIR}/deps/lib/libvorbisfile.lib
		)
		set(VORBIS_LIBRARIES
			${VORBIS_LIBRARIES}
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
		set(TIDYENGINE_LIBRARIES
			${TIDYENGINE_LIBRARIES}
			${CMAKE_BINARY_DIR}/libTidyEngine/libTidyEngine.a
		)
		set(BOX2D_LIBRARIES
			${BOX2D_LIBRARIES}
			${CMAKE_SOURCE_DIR}/deps/lib/libBox2D.a
		)
		set(GLFW_LIBRARIES
			${GLFW_LIBRARIES}
			${CMAKE_SOURCE_DIR}/deps/lib/libglfw3.a
		)
		set(OGG_LIBRARIES
			${OPENAL_LIBRARIES}
			${CMAKE_SOURCE_DIR}/deps/lib/libogg.a
		)
		set(VORBISFILE_LIBRARIES
			${VORBISFILE_LIBRARIES}
			${CMAKE_SOURCE_DIR}/deps/lib/libvorbisfile.a
		)
		set(VORBIS_LIBRARIES
			${OPENAL_LIBRARIES}
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
		find_package(BZip2 REQUIRED)
		find_package(ZLIB REQUIRED)
	endif ()

	set(GLFW_INCLUDE_DIRS
		${GLFW_INCLUDE_DIRS}
		${CMAKE_SOURCE_DIR}/deps/include/
	)
	set(BOX2D_INCLUDE_DIRS
		${GLFW_INCLUDE_DIRS}
		${CMAKE_SOURCE_DIR}/deps/include/Box2D/
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
		${CMAKE_SOURCE_DIR}/deps/include/AL
	)
	set(OPENAL_LIBRARIES
		${OPENAL_LIBRARIES}
		${CMAKE_SOURCE_DIR}/deps/lib/OpenAL32.lib
	)
	set(OGG_INCLUDE_DIRS
		${OGG_INCLUDE_DIRS}
		${CMAKE_SOURCE_DIR}/deps/include/ogg
	)
	set(VORBIS_INCLUDE_DIRS
		${VORBIS_INCLUDE_DIRS}
		${CMAKE_SOURCE_DIR}/deps/include/vorbis
	)
	set(FREETYPE2_INCLUDE_DIRS
		${FREETYPE2_INCLUDE_DIRS}
		${CMAKE_SOURCE_DIR}/deps/include/freetype
	)
elseif (APPLE)
	message("MACOSX: Not yet supported")
elseif (UNIX)
	find_package(PkgConfig REQUIRED)
	pkg_search_module(GLFW REQUIRED glfw3)
	pkg_search_module(FREEIMAGE REQURIED freeimage)
	pkg_search_module(LUAJIT REQUIRED luajit)
	pkg_search_module(LUAJIT REQUIRED luajit)
	pkg_search_module(OGG REQUIRED ogg)
	pkg_search_module(VORBIS REQUIRED vorbis)
	pkg_search_module(VORBISFILE REQUIRED vorbisfile)
	pkg_search_module(FREETYPE2 REQUIRED freetype2)
	set(TIDYENGINE_LIBRARIES
		${TIDYENGINE_LIBRARIES}
		${CMAKE_BINARY_DIR}/libTidyEngine/libTidyEngine.a
	)
	set(GLAD_LIBRARIES
		${GLAD_LIBRARIES}
		-ldl
		${CMAKE_BINARY_DIR}/glad/libglad.a
	)
	set(BOX2D_LIBRARIES
		${BOX2D_LIBRARIES}
		-lBox2D
	)
endif ()

include_directories(${CMAKE_SOURCE_DIR}/deps/include)
include_directories(${BOX2D_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${FREEIMAGE_INCLUDE_DIRS})
include_directories(${OPENAL_INCLUDE_DIRS})
include_directories(${OGG_INCLUDE_DIRS})
include_directories(${VORBIS_INCLUDE_DIRS})
include_directories(${FREETYPE2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME}
                      ${TIDYENGINE_LIBRARIES}
                      ${GLAD_LIBRARIES}
                      ${GLFW_LIBRARIES}
                      ${FREEIMAGE_LIBRARIES}
                      ${OPENAL_LIBRARIES}
                      ${VORBISFILE_LIBRARIES}
                      ${VORBIS_LIBRARIES}
                      ${OGG_LIBRARIES}
                      ${FREETYPE2_LIBRARIES}
                      ${BZIP2_LIBRARIES}
                      ${ZLIB_LIBRARIES}
                      ${BOX2D_LIBRARIES})

if (WIN32)
	target_link_libraries(${PROJECT_NAME} opengl32.lib)
endif ()
