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
	else ()
		set(TIDYENGINE_LIBRARIES
			${TIDYENGINE_LIBRARIES}
			${CMAKE_BINARY_DIR}/libTidyEngine/TidyEngine.lib
		)
	endif ()
	set(GLFW_INCLUDE_DIRS
		${GLFW_INCLUDE_DIRS}
		${CMAKE_SOURCE_DIR}/deps/include/
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
	pkg_search_module(LUAJIT REQUIRED luajit)
	pkg_search_module(OGG REQUIRED ogg)
	pkg_search_module(VORBIS REQUIRED vorbis)
	pkg_search_module(VORBISFILE REQUIRED vorbisfile)
	set(TIDYENGINE_LIBRARIES
		${TIDYENGINE_LIBRARIES}
		${CMAKE_BINARY_DIR}/libTidyEngine/libTidyEngine.a
	)
endif ()

include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${FREEIMAGE_INCLUDE_DIRS})
include_directories(${OPENAL_INCLUDE_DIRS})
include_directories(${OGG_INCLUDE_DIRS})
include_directories(${VORBIS_INCLUDE_DIRS})
include_directories(${VORBISFILE_INCLUDE_DIRS})


add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${TIDYENGINE_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${FREEIMAGE_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${OPENAL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${OGG_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${VORBIS_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${VORBISFILE_LIBRARIES})

if (WIN32)
	target_link_libraries(${PROJECT_NAME} opengl32.lib)
endif ()
