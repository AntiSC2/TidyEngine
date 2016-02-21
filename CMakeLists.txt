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
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/core.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Graphics/screen.cpp
)
set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/src/game.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/core.h
   ${CMAKE_CURRENT_SOURCE_DIR}/src/Graphisc/screen.h
)

#Add the version number
set (TidyEngine_VERSION_MAJOR 0)
set (TidyEngine_VERSION_MINOR 2)

#Configure a header file to pass the CMake version into the source code
configure_file(
    "${PROJECT_SOURCE_DIR}/src/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)

#GLFW
IF(WIN32)

    message(STATUS "WIN32")
    LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/deps/lib)
    include_directories(${PROJECT_SOURCE_DIR}/deps/include)
    include_directories(${PROJECT_SOURCE_DIR}/src/)
    include_directories(${PROJECT_BINARY_DIR})

else(WIN32)
    message(STATUS "UNIX")
    include(FindPkgConfig)

    #Add include directories
    include_directories(${PROJECT_SOURCE_DIR}/src/)
    include_directories(${PROJECT_BINARY_DIR})
endif(WIN32)

add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})