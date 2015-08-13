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
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support.\nPlease use a different C++ compiler.\nNote: The newer visual studio compiler does support C++11 but this message will still appear.")
endif()

#Add sources
set(SOURCE
   ${SOURCE}
   ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/game.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Components/component.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Components/controller.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Components/sprite.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Components/sprite.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/core.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/input.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Entities/actor.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Graphics/screen.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Graphics/spritesheet.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/RM/cache.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/RM/sheetcache.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/RM/soundcache.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/RM/texcache.cpp
)
set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/src/game.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Components/component.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Components/controller.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Components/sprite.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Components/sprite.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/core.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/input.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Entities/actor.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Graphisc/screen.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Graphics/spritesheet.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/RM/cache.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/RM/sheetcache.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/RM/soundcache.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/RM/texcache.h
)

#Add the version number
set (TidyEngine_VERSION_MAJOR 0)
set (TidyEngine_VERSION_MINOR 1)

#Configure a header file to pass the CMake version into the source code
configure_file(
    "${PROJECT_SOURCE_DIR}/src/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)

#SDL2
IF(WIN32)

    message(STATUS "WIN32")
	LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/deps/lib)
    include_directories(${PROJECT_SOURCE_DIR}/deps/include)
    include_directories(${PROJECT_SOURCE_DIR}/src/)
    include_directories(${PROJECT_BINARY_DIR})

    set(SDL2_LIBRARIES
        ${SDL2_LIBRARIES}
        SDL2.lib
        SDL2main.lib
    )

    set(SDLIMAGE_LIBRARIES
        ${SDLIMAGE_LIBRARIES}
        SDL2_image.lib
    )

    set(SDLMIXER_LIBRARIES
        ${SDLMIXER_LIBRARIES}
        SDL2_mixer.lib
    )

    set(SDLTTF_LIBRARIES
        ${SDLTTF_LIBRARIES}
        SDL2_ttf.lib
    )
else(WIN32)
    message(STATUS "UNIX")
    include(FindPkgConfig)
    pkg_search_module(SDL2 REQUIRED sdl2)
    pkg_search_module(SDLIMAGE REQUIRED SDL2_image>=2.0.2)
    pkg_search_module(SDLMIXER REQUIRED SDL2_mixer>=2.0.0)
    pkg_search_module(SDLTTF REQUIRED SDL2_ttf>=2.0.12)

    #Add include directories
    include_directories(${PROJECT_SOURCE_DIR}/src/)
    include_directories(${PROJECT_BINARY_DIR})
    include_directories(${SDL2_INCLUDE_DIRS})
    include_directories(${SDLIMAGE_INCLUDE_DIRS})
    include_directories(${SDLMIXER_INCLUDE_DIRS})
    include_directories(${SDLTTF_INCLUDE_DIRS})
endif(WIN32)

add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDLIMAGE_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDLMIXER_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDLTTF_LIBRARIES})
