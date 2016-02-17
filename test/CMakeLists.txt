cmake_minimum_required (VERSION 3.2.3)
project (TEST)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${TIDYENGINE_LIB})