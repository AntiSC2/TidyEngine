cmake_minimum_required (VERSION 3.2.3)
project (TEST)

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

if(WIN32)
	set(TIDYENGINE_LIBRARIES
		${TIDYENGINE_LIBRARIES}
		${CMAKE_BINARY_DIR}/libTidyEngine/Debug/TidyEngine.lib
	)
	set(GLFW_INCLUDE_DIRS
		${GLFW_INCLUDE_DIRS}
		${CMAKE_SOURCE_DIR}/deps/include/GLFW
	)
	set(GLFW_LIBRARIES
		${GLFW_LIBRARIES}
		${CMAKE_SOURCE_DIR}/deps/lib/glfw3dll.lib
	)
endif()

include_directories(${GLFW_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${TIDYENGINE_LIBRARIES})