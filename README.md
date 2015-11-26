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
- Download this repository to your computer. The folder "TidyEngine/" should contain three folders: /bin/, /src/ and /deps/. Because you're on a Linux system you don't have to care about the /deps/ folder.
- Get the latest version of the dependencies and the latest version of CMake.
- Point the "Where is the source code:" in CMake to the folder containing all of the three main folders. NOT THE /SRC/ FOLDER! Point the "Where to build the binaries:" in CMake to the /bin/ folder.
- Choose in CMake the option to build with a UNIX Makefile.
- Click configure and then click generate.
- Navigate to the /bin/ folder and simply run the "make" command.
- The binary should build without a problem if all the dependencies are correctly installed.

<h3>Windows Instructions with Visual Studio</h3>
- Download this repository to your computer. The folder "TidyEngine/" should contain three folders: /bin/, /src/ and /deps/.
- Download the dependencies, make sure to get the correct versions for the SDL library.
- Inside the /deps/ folder there should be two empty folders named "/include/" and "/lib/". If not, create them.
- Place the glm include files in the include folder. It should look like this: /deps/include/glm/"All include files from glm".
- Place all the SDL2 include files in the include folder. It should look like this: /deps/include/SDL2/"All include files from all the SDL libraries".
- Place all the SDL2 lib files in the lib folder. It should look like this: /deps/lib/"All library files from all the SDL libraries".
- Get the latest version of CMake.
- Point the "Where is the source code:" in CMake to the folder containing all of the three main folders. NOT THE /SRC/ FOLDER! Point the "Where to build the binaries:" in CMake to the /bin/ folder.
- Choose in CMake the option to make a Visual Studio project with your version of Visual Studio.
- Click configure and then click generate.
- Navigate to the /bin/ folder and simply open up the project in Visual Studio.
- Place all the .dll files from SDL2 in /bin/Debug folder. If the folder doesn't exist you can just create the folder.
- Run the TidyEngine project. It should compile fine. NOTE: There is a bug with SDL2main library file in Visual Studio which makes it not able to Link properly to the Project. To fix this you need to compile your own version of the SDL2main library.

# Presentation
Here's a google slide presentation showing off the general map for this engine.
WIP:https://docs.google.com/presentation/d/1KCC6VAwV4GwIKRrNTNlfntW5TLCluPvbB-OwTJ0mb2Q/edit?usp=sharing
