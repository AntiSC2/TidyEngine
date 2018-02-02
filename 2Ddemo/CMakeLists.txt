cmake_minimum_required (VERSION 3.0.2)
project(2Ddemo CXX)

file(GLOB 2DDEMO_SOURCE
	"*.hpp"
	"*.cpp"
)

add_executable(2Ddemo ${2DDEMO_SOURCE})
target_link_libraries(2Ddemo
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
	target_link_libraries(2Ddemo opengl32.lib)
endif ()
