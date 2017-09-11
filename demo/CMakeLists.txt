cmake_minimum_required (VERSION 3.0.2)
project(Demo CXX)

set(SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/game.cpp
)

add_executable(Demo ${SOURCES} ${HEADERS})
target_link_libraries(Demo
	TidyEngine
	${GLAD_LIBRARIES}
	${GLFW_LIBRARIES}
	${LUAJIT_LIBRARIES}
	${OPENAL_LIBRARIES}
	${VORBISFILE_LIBRARIES}
	${VORBIS_LIBRARIES}
	${OGG_LIBRARIES}
	${FREETYPE2_LIBRARIES}
	${BZIP2_LIBRARIES}
	${ZLIB_LIBRARIES}
	${ASSIMP_LIBRARIES}
)

if (WIN32)
	target_link_libraries(Demo opengl32.lib)
endif ()
