cmake_minimum_required (VERSION 3.2.3)
project(glad)

include_directories(${CMAKE_SOURCE_DIR}/deps/include)

set(SOURCES
	${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/glad.c
)
set(HEADERS
	${HEADERS}
	${CMAKE_SOURCE_DIR}/deps/include/glad/glad.h
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
