# TidyEngine
TidyEngine is a game engine that was created for making games in a C++ framework. V0.2 moved away from SDL2 and instead uses GLFW for window and input handling. It also uses glew for fast modern OpenGL rendering. When it comes to loading bitmaps, this project uses the FreeImage open source image library.

# Features
- Full OpenGL support
- Fully cross-platform

# Build instructions
I really appreciate any help I can get. If you want to start contributing to this project you will need to be able to build the engine itself. Here is all the dependencies you need:

- CMake, used for building the project
- GLFW, used for handling windows and the input.
- glew, used for OpenGL rendering.
- glm, used for math when rendering.
- FreeImage, used for bitmap loading.

<h3>Linux Instructions</h3>
- Clone the repository to your computer using the `git clone https://github.com/AntiSC2/TidyEngine.git` command.
- Install all the dependencies listed above.
- Copy the `freeimage.pc` file into your pkgconfig directory. Usually located in `/usr/lib/pkgconfig`. NOTE: YOU WILL NEED ROOT ACCESS TO DO THIS.
- Change directory to the `/path/to/TidyEngine/bin` folder.
- Run the command `cmake -Wdev /path/to/TidyEngine`.
- Run `make` to build the project.
- Before you start the test application, copy over the shaders from `shaders/` folder into the `bin/` folder. Also create a png image that is 2x2 and completly white. Name the image to `default.png`. You can now run the test application from the `bin/` folder with the command `./test/TEST`.

<h3>Windows Instructions with Visual Studio</h3>
- Coming soon

# Presentation
Here's a google slide presentation showing off the general map for this engine.
WIP:https://docs.google.com/presentation/d/1KCC6VAwV4GwIKRrNTNlfntW5TLCluPvbB-OwTJ0mb2Q/edit?usp=sharing

# License
TidyEngine is under the LGPL v3. This software uses the FreeImage open source image library. See http://freeimage.sourceforge.net for details. FreeImage is used under the FIPL, version 1.0. 
