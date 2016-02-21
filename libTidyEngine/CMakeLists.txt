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
)
set(HEADERS
        ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/core.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/screen.hpp
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
endif()

if(APPLE)

elseif(UNIX)
	find_package(PkgConfig REQUIRED)
	pkg_search_module(GLFW REQUIRED glfw3)

endif()

include_directories(${GLFW_INCLUDE_DIRS})

add_library(${PROJECT_NAME} STATIC ${SOURCE} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES})
