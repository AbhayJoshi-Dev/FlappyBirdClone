# FlappyBirdClone
A clone of Flappy Bird created using C++ and [SDL2](https://www.libsdl.org/)
## Compiling
### Windows
Create a folder name 'Dependencies' in the project's root directory, then download [SDL2](https://www.libsdl.org/download-2.0.php), [SDL_Image](https://www.libsdl.org/projects/SDL_image/) development libraries and paste them inside dependencies folder.

Execute the following command in the project's root directory:

Enter 'build.bat action' where action is one of the following:
```
  compile           Will generate make file then compile using the make file.
  clean             Remove all binaries and intermediate binaries and project files.
  codelite          Generate CodeLite project files
  gmake2            Generate GNU makefiles for Linux
  vs2005            Generate Visual Studio 2005 project files
  vs2008            Generate Visual Studio 2008 project files
  vs2010            Generate Visual Studio 2010 project files
  vs2012            Generate Visual Studio 2012 project files
  vs2013            Generate Visual Studio 2013 project files
  vs2015            Generate Visual Studio 2015 project files
  vs2017            Generate Visual Studio 2017 project files
  vs2019            Generate Visual Studio 2019 project files
  xcode4            Generate Apple Xcode 4 project files
```
The compiled ``.exe`` is located in ``./bin``. For it to run, you must copy the ``./res`` folder as well as all ``.dll`` files from your SDL2, SDL_image installation to its directory.
