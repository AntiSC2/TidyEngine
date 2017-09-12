cmake_minimum_required (VERSION 3.0.2)
project(glad)

include_directories(${CMAKE_SOURCE_DIR}/deps)

set(SOURCES
	${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/glad.c
)
set(HEADERS
	${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/glad.h
)

add_library(glad STATIC ${SOURCES} ${HEADERS})
