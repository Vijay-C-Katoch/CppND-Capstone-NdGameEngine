# CPPND: Capstone project ND Game Engine
  
# ND Game Engine : NanoDegree Game Engine  

## Create any 2D game using *ND Game Engine*

Prerequisites
--------------
* CMake 3.7 or later
* Windows
  * Environment variable `SDL2DIR` is set to extracted SDL2 development libraries directory e.g.
    `SDL2DIR=C:\Users\Public\Downloads\SDL2-2.0.16` 
  * Instructions: https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php
  
* Linux
  * SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 


## Build Instructions on platforms
Windows 
--------------
* Default Game build is Asteroids Game. For Snake game provide option -DSNAKE

`cmake -G "Visual Studio 16 2019" -B.\build`
`cmake --build .\build`

* Build or build and install in single step
```
rmdir /q /s build & cmake -G "Visual Studio 16 2019" -B.\build && cmake --build .\build && cmake --install .\build --config Debug
```
* Run
  * build\install\AsteroidsGame.exe

 
* Building Snake game in  single step 
```
rmdir /q /s build & cmake -G "Visual Studio 16 2019" -DSNAKE=ON -B.\build && cmake --build .\build && cmake --install .\build --config Debug
```
* Run
  * build\install\SnakeGame.exe

Linux
--------------
* Default Game build is Asteroids Game. For Snake game provide option -DSNAKE

`rm -rf build && cmake -Bbuild && cmake --build build`

* Build or build and install in single step
```
rm -rf build && cmake -Bbuild && cmake --build build && cmake --install build
```

* Build or build and install Snake Game in single step
```
rm -rf build && cmake -DSNAKE=ON -Bbuild && cmake --build build && cmake --install build
```


## Rubric point addressed
* Compiling and Testing
* Loops, Functions, I/O
* Object Oriented Programming
* Memory Management
  *
* Concurrency
  *
  

# License
* https://github.com/Vijay-C-Katoch/CppND-Capstone-NdGameEngine/blob/main/LICENSE.md


