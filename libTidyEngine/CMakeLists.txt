cmake_minimum_required (VERSION 3.0.2)

#Setting up the version number for the engine
set(TidyEngine_VERSION_MAJOR 0)
set(TidyEngine_VERSION_MINOR 2)

configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/config.hpp"
)

file(GLOB TIDYENGINE_SOURCE
	"*.hpp"
	"*.cpp"
)

set(TIDYENGINE_SOURCE ${TIDYENGINE_SOURCE}
	${CMAKE_SOURCE_DIR}/deps/install/include/stb_image.h
)

add_library(TidyEngine STATIC ${TIDYENGINE_SOURCE})
target_link_libraries(TidyEngine
	${GLAD_LIBRARIES}
	${GLFW_LIBRARIES}
	${LUAJIT_LIBRARIES}
	${OPENAL_LIBRARIES}
	${OGG_LIBRARIES}
	${VORBIS_LIBRARIES}
	${VORBISFILE_LIBRARIES}
	${FREETYPE2_LIBRARIES}
	${ASSIMP_LIBRARIES}
)

# Ensure that the external projects are built first
if (BUILD_EXTERNAL_DEPENDENCIES)
	add_dependencies(TidyEngine assimp glfw freetype2 vorbis openal-soft)
endif ()

if (WIN32)
	target_link_libraries(TidyEngine opengl32.lib)
endif ()
