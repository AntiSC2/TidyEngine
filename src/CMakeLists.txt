cmake_minimum_required (VERSION 3.2.3)
project (TidyEngine)

#Enable C++11 if the compiler allows it
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

#Add sources
set(SOURCE
   ${SOURCE}
   ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/game.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Components/component.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Components/controller.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Components/sprite.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Components/sprite.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Core/core.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Core/input.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Entities/actor.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Graphics/screen.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Graphics/spritesheet.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/RM/cache.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/RM/sheetcache.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/RM/soundcache.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/RM/texcache.cpp
)
set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/game.h
   ${CMAKE_CURRENT_SOURCE_DIR}/Components/component.h
   ${CMAKE_CURRENT_SOURCE_DIR}/Components/controller.h
   ${CMAKE_CURRENT_SOURCE_DIR}/Components/sprite.h
   ${CMAKE_CURRENT_SOURCE_DIR}/Components/sprite.h
   ${CMAKE_CURRENT_SOURCE_DIR}/Core/core.h
   ${CMAKE_CURRENT_SOURCE_DIR}/Core/input.h
   ${CMAKE_CURRENT_SOURCE_DIR}/Entities/actor.h
   ${CMAKE_CURRENT_SOURCE_DIR}/Graphisc/screen.h
   ${CMAKE_CURRENT_SOURCE_DIR}/Graphics/spritesheet.h
   ${CMAKE_CURRENT_SOURCE_DIR}/RM/cache.h
   ${CMAKE_CURRENT_SOURCE_DIR}/RM/sheetcache.h
   ${CMAKE_CURRENT_SOURCE_DIR}/RM/soundcache.h
   ${CMAKE_CURRENT_SOURCE_DIR}/RM/texcache.h
)

#Add the version number
set (TidyEngine_VERSION_MAJOR 0)
set (TidyEngine_VERSION_MINOR 1)

#Configure a header file to pass the CMake version into the source code
configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)

#SDL2
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDLIMAGE REQUIRED SDL2_image>=2.0.2)
pkg_search_module(SDLMIXER REQUIRED SDL2_mixer>=2.0.0)
pkg_search_module(SDLTTF REQUIRED SDL2_ttf>=2.0.3)

#Add include directories
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_BINARY_DIR}")
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDLIMAGE_INCLUDE_DIRS})
include_directories(${SDLMIXER_INCLUDE_DIRS})
include_directories(${SDLTTF_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDLIMAGE_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDLMIXER_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDLTTF_LIBRARIES})
