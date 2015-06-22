# TidyEngine
TidyEngine is a game engine that I created for my own use. It's designed to create 2D games. It's licensed under LGPL V3 so feel free to use it if you want. As long as you give credit back and don't hold me liable for anything.

# Features
- Input handling

- Resource management

- Sprites & animation

- Text rendering

- Sound & music

- Object management

- Network handling

# Build instructions
I really appreciate any help I can get. If you want to start contributing to this project you will need to be able to build the engine itself. Here is all the dependencies you need:

- SDL2, used for handling the window and rendering

- SDL2_image, used for loading in textures in various formats

- SDL2_ttf, used for the text renderer

- SDL2_mixer, used for the sound and music

- glm, provides vectors and matrices that follow the OpenGL standard

<h3>Linux Instructions</h3>
- Get the latest build of GCC and make sure to get the right version of the dependencies (32-bit libraries if running on 32-bit etc).
- Make sure that your system can build makefiles
- Simply go to the source folder and run 'make'.
- It should create an executable file in the path: "$HOME/Code/GameEngine/Bin/"

# Presentation
Here's a google slide presentation showing off the general map for this engine.
WIP:https://docs.google.com/presentation/d/1KCC6VAwV4GwIKRrNTNlfntW5TLCluPvbB-OwTJ0mb2Q/edit?usp=sharing
