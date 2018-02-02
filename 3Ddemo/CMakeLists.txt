cmake_minimum_required (VERSION 3.0.2)
project(3Ddemo CXX)

file(GLOB 3DDEMO_SOURCE
	"*.hpp"
	"*.cpp"
)

add_executable(3Ddemo ${3DDEMO_SOURCE})
target_link_libraries(3Ddemo
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
	target_link_libraries(3Ddemo opengl32.lib)
endif ()
