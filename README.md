# Flappy Bird Clone

A clone of Flappy Bird created using C++ and [SDL2](https://www.libsdl.org/)

## Demo

![](https://i.imgur.com/iadcUDO.gif)

## Build Instructions

- Requirements
  - Git
  - CMake
  - C++ Compiler

- Steps

    ```cmd
    # Clone this project along with submodules
    $ git clone --recursive https://github.com/AbhayJoshi-Dev/FlappyBirdClone

    # Go to project root
    $ cd FlappyBirdClone

    # Pull SDL, SDL_image and SDL_ttf as submodule (if you cloned without --recursive flag)
    $ git submodule update --init --recursive

    # Create a folder for build
    $ mkdir build

    # Go to build folder
    $ cd build

    # Generate project files
    $ cmake ..
    ```

- This will generate project files using default cmake generator for your platform. For example:

  - on `Windows` with `Visual Studio` installed, it will generate a `.sln`
  - on `Linux` with `make` installed, it will generate a `Makefile`
  - on `Mac` with `xcode` installed, it will generate a `.xcodeproj`
