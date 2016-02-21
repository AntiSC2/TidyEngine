cmake_minimum_required (VERSION 3.2.3)
project (TEST)

set(SOURCE
        ${SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp}
        ${CMAKE_CURRENT_SOURCE_DIR}/game.cpp}
)
set(HEADERS
        ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/game.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})