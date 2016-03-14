cmake_minimum_required (VERSION 3.2.3)
project (TidyEngine)

#Setting up the version number for the engine
set (TidyEngine_VERSION_MAJOR 0)
set (TidyEngine_VERSION_MINOR 2)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in"
    "${CMAKE_BINARY_DIR}/config.hpp"
)
include_directories(${CMAKE_BINARY_DIR})

set(SOURCE
        ${SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/core.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/screen.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/render2d.cpp
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
)
set(HEADERS
        ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/core.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/screen.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/render2d.hpp
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
)

if(WIN32)
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
endif()

if(APPLE)

elseif(UNIX)
	find_package(PkgConfig REQUIRED)
	pkg_search_module(GLFW REQUIRED glfw3)
	pkg_search_module(GLEW REQUIRED glew)
	pkg_search_module(FREEIMAGE REQURIED freeimage)
endif()

include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${FREEIMAGE_INCLUDE_DIRS})

add_library(${PROJECT_NAME} STATIC ${SOURCE} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES}
				      ${GLEW_LIBRARIES}
				      ${FREEIMAGE_LIBRARIES})

if(WIN32)
	target_link_libraries(${PROJECT_NAME} opengl32.lib)
endif()
