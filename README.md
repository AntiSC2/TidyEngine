# TidyEngine
TidyEngine is a game engine that was created for making games in a C++ framework. V0.2 moved away from SDL2 and instead uses GLFW for window and input handling. It uses glad and GLFW for fast modern OpenGL rendering. It also uses the FreeImage library, which is licensed under the FIPL, for bitmap loading and for audio it uses OpenAL as a backend and libogg for loading audio files. Right now the only scripting that is supported is Lua scripting.

# Features
- All rendering is done through modern OpenGL
- Fully cross-platform, only uses standard C++ and cross-platform libraries
- Entity management based on the ECS architecture
- Lua scripting

# Build instructions
Here is all the dependencies you need for building the engine:

- CMake, used for building the project
- assimp, used for 3D mesh loading
- GLFW, used for handling windows and the input
- glad, used for OpenGL rendering. (glad is already included in this repository)
- glm, used for vectors and matrixes
- stb_image.h, used for bitmap loading
- OpenAL, used for audio
- libogg & libvorbis, used for loading sound samples
- LuaJIT, used for Lua scripting
- Freetype2, used for font loading and rendering

<h3>Linux Instructions</h3>

- Clone the repository using the `git clone https://github.com/AntiSC2/TidyEngine.git` command.
- Install all the dependencies listed above.
- Change directory to the `TidyEngine/bin` folder.
- Run the command `cmake -Wdev ..`.
- Run `make` inside the `bin` folder to build the project.
- Both a 2D demo and a 3D demo will be built by default. This can be disabled with `-DBUILD_DEMO2D` and  `-DBUILD_DEMO3D` respectively.
- Copy the shaders from the `shaders` folder to the working directory you are using to run the demos.

<h3>Windows Instructions with Visual Studio</h3>

- Clone the repository using the `git clone https://github.com/AntiSC2/TidyEngine.git` command or other method.
- Run CMake with the source directory set to the top-level directory and the binary directory set to the `bin` folder.
- Set Visual Studio as the target compiler in CMake.
- `BUILD_EXTERNAL_DEPENDENCIES` also generates build files for all dependencies, except for luajit, if set to `TRUE`. Luajit still needs manual compiling and moving of files. See http://luajit.org/install.html for more information.
- Generate the build files.
- Open up the generated ALL_BUILD.vcproj and build the project.
- By default this will also build most of the dependencies.

# License
TidyEngine is under the LGPL v3. Certain files under the `bin/` folder have other licenses applied to them. Please check `LICENSE-ART.md` located under the `bin/` folder for more information.
