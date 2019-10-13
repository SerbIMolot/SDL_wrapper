SDL_gpu, a library for making hardware-accelerated 2D graphics easy.
by Jonathan Dearborn

SDL_gpu is licensed under the terms of the MIT License.
See LICENSE.txt for details of the usage license granted to you for this code.


=============
LATEST SOURCE
=============

SDL_gpu is hosted on Github (https://github.com/grimfang4/sdl-gpu).  You can check out the latest version of the source code with Git:
git clone https://github.com/grimfang4/sdl-gpu.git sdl-gpu


============
DEPENDENCIES
============

SDL 1.2 or SDL 2.0 (www.libsdl.org)
A rendering backend
	Currently implemented:
		OpenGL 1.1, 2.0, 3.0, 4.0
		OpenGL ES 1.1, 2.0, 3.0


========
BUILDING
========

SDL_gpu uses CMake (www.cmake.org) to coordinate the library build process.  CMake is available as a GUI program or on the command line.

For Linux/UNIX systems, run CMake in the base directory:
cmake -G "Unix Makefiles"
make
sudo make install

For Linux/UNIX systems, changing the default installation directory can be done like so:
cmake -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX=/usr

For Windows systems, you can use cmake-gui and select appropriate options in there (warning: cmake-gui is messy!).


===================
INCLUDING / LINKING
===================

Add the include for SDL_gpu.h to your sources.  Link to SDL_gpu (libSDL_gpu.a) or SDL2_gpu (if you use SDL2).


=============
DOCUMENTATION
=============

Documentation is automatically generated with Doxygen (http://sourceforge.net/projects/doxygen).
Pre-generated documentation is hosted by DinoMage Games:
http://dinomage.com/reference/SDL_gpu/





