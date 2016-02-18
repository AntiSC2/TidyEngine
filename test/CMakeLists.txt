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

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} TidyEngine)