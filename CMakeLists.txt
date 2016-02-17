cmake_minimum_required (VERSION 3.2.3)
project (TidyEngine)

add_subdirectory("${CMAKE_SOURCE_DIR}/libTidyEngine")
option(BUILD_TEST "Build a test that is using the engine library" TRUE)
if(BUILD_TEST)
        add_subdirectory(test)
endif()