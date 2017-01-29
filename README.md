# TidyEngine
TidyEngine is a game engine that was created for making games in a C++ framework. V0.2 moved away from SDL2 and instead uses GLFW for window and input handling. It also uses glad and GLFW for fast modern OpenGL rendering. It also uses the FreeImage library, which is licensed under the FIPL, for bitmap loading.

# Features
- All rendering is done through modern OpenGL
- Fully cross-platform
- Object management
- Lua scripting

# Build instructions
I really appreciate any help I can get. If you want to start contributing to this project you will need to be able to build the engine itself. Here is all the dependencies you need:

- CMake, used for building the project
- GLFW, used for handling windows and the input.
- glad, used for OpenGL rendering. (glad is already included)
- glm, used for math when rendering.
- FreeImage, used for bitmap loading.
- OpenAL, used for audio
- libogg & libvorbis, used for loading sound samples
- LuaJIT, used for Lua scripting
- Freetype2, used for font rendering

<h3>Linux Instructions</h3>
- Clone the repository to your computer using the `git clone https://github.com/AntiSC2/TidyEngine.git` command.
- Install all the dependencies listed above.
- Copy the `freeimage.pc` file into your pkgconfig directory. Usually located in `/usr/lib/pkgconfig`. NOTE: YOU WILL NEED ROOT ACCESS TO DO THIS.
- Change directory to the `/path/to/TidyEngine/bin` folder.
- Run the command `cmake -Wdev /path/to/TidyEngine`.
- Run `make` to build the project.
- Before you start the test application, copy over the shaders from `shaders/` folder into the `bin/` folder. You can now run the test application from the `bin/` folder with the command `./test/TEST`.

<h3>Windows Instructions with Visual Studio</h3>
- The windows version is working. I just haven't got around to making the instructions for it. Basicly put all the libraries and include files in the `deps` folder. Then run CMake to generate the visual studio project. After that place all the DLLs in the same folder as the binary.

# Presentation
Here's a google slide presentation showing off the general map for this engine.
WIP:https://docs.google.com/presentation/d/1KCC6VAwV4GwIKRrNTNlfntW5TLCluPvbB-OwTJ0mb2Q/edit?usp=sharing

# License
TidyEngine is under the LGPL v3. This software uses the FreeImage open source image library. See http://freeimage.sourceforge.net for details. FreeImage is used under the FIPL, version 1.0. 
