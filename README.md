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
- GLFW, used for handling windows and the input
- glad, used for OpenGL rendering. (glad is already included in this repository)
- glm, used for vectors and matrixes
- FreeImage, used for bitmap loading
- OpenAL, used for audio
- libogg & libvorbis, used for loading sound samples
- LuaJIT, used for Lua scripting
- Freetype2, used for font loading and rendering

<h3>Linux Instructions</h3>
- Clone the repository using the `git clone https://github.com/AntiSC2/TidyEngine.git` command.
- Install all the dependencies listed above.
- Copy the `freeimage.pc` file into your pkgconfig directory. Usually located in `/usr/lib/pkgconfig`. NOTE: YOU WILL NEED ROOT ACCESS TO DO THIS.
- Change directory to the `/path/to/TidyEngine/bin` folder.
- Run the command `cmake -Wdev /path/to/TidyEngine`.
- Run `make` inside the `bin/` folder to build the project.
- Before you start the test application, copy over the shaders from `shaders/` folder into the `bin/` folder. You can now run the test application from the `bin/` folder with the command `./test/TEST`.

<h3>Windows Instructions with Visual Studio</h3>
- The windows version is working. I just haven't got around to making the instructions for it. Basicly put all the libraries and include files in the `deps` folder. Then run CMake to generate the project files, works with both MinGW and Visual Studio.

# Presentation
Here's a google slide presentation showing off the general architecture for this engine.
WIP:https://docs.google.com/presentation/d/1KCC6VAwV4GwIKRrNTNlfntW5TLCluPvbB-OwTJ0mb2Q/edit?usp=sharing

# License
TidyEngine is under the LGPL v3. This software uses the FreeImage open source image library. See http://freeimage.sourceforge.net for details. FreeImage is used under the FIPL, version 1.0.
