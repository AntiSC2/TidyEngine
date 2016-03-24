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
	if(MSVC)
		set(TIDYENGINE_LIBRARIES
			${TIDYENGINE_LIBRARIES}
			${CMAKE_BINARY_DIR}/libTidyEngine/Debug/TidyEngine.lib
		)
	else()
		set(TIDYENGINE_LIBRARIES
			${TIDYENGINE_LIBRARIES}
			${CMAKE_BINARY_DIR}/libTidyEngine/TidyEngine.lib
		)
	endif()
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
endif()

if(APPLE)

elseif(UNIX)
	find_package(PkgConfig REQUIRED)
	pkg_search_module(GLFW REQUIRED glfw3)
	pkg_search_module(GLEW REQUIRED glew)
	pkg_search_module(FREEIMAGE REQURIED freeimage)
	set(TIDYENGINE_LIBRARIES
		${TIDYENGINE_LIBRARIES}
		${CMAKE_BINARY_DIR}/libTidyEngine/libTidyEngine.a
	)
endif()

include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${FREEIMAGE_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${TIDYENGINE_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${FREEIMAGE_LIBRARIES})

if(WIN32)
	target_link_libraries(${PROJECT_NAME} opengl32.lib)
endif()
