cmake_minimum_required (VERSION 3.2.3)
project (TidyEngine)

#Add the version number
set (TidyEngine_VERSION_MAJOR 0)
set (TidyEngine_VERSION_MINOR 2)

#Configure a header file to pass the CMake version into the source code
configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)

#Add include directories
include_directories("${PROJECT_BINARY_DIR}")

#SDL2
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_image REQUIRED sdl2_image)
pkg_search_module(SDL2_mixer REQUIRED sdl2_mixer)
pkg_search_module(SDL2_ttf REQUIRED sdl2_ttf)
pkg_search_module(gml REQUIRED gml)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(TidyEngine main.cpp)
target_link_libraries(TidyEngine ${SDL2_LIBRARY})
target_link_libraries(TidyEngine ${SDL2_image_LIBRARY})
target_link_libraries(TidyEngine ${SDL2_mixer_LIBRARY})
target_link_libraries(TidyEngine ${SDL2_ttf_LIBRARY})
