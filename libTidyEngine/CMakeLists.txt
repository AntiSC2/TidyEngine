cmake_minimum_required (VERSION 3.2.3)
project (TidyEngine)

set (TidyEngine_VERSION_MAJOR 0)
set (TidyEngine_VERSION_MINOR 2)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in"
    "${PROJECT_BINARY_DIR}/config.hpp"
)

set(SOURCE
        ${SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/core.cpp}
        ${CMAKE_CURRENT_SOURCE_DIR}/screen.cpp}
)
set(HEADERS
        ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/core.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/screen.hpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE} ${HEADERS})