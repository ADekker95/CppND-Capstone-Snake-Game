# CPPND: Capstone Snake Game: A game of (two) snakes

This is repo is built from the starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

## Game instructions 
In this Capstone Project, we play with (two) snakes that battle for food. One snakes is controlled by arrows, the other via w,a,s,d. If one snakes earns two points more than the other or a snake runs into itself, the game ends and the score and size of the winning snake is displayed. 

## How 5 rubric points are satisfied:
1. The project demonstrates an understanding of C++ functions and control structures.
The repo consists of for loops and if/else statements. 
2. Classes use appropriate access specifiers for class members.
Each snake has a different set of control keys that directs the snake to go up, down, left or right. These control keys are connected to private variables in the constructor list. 
3. Class constructors utilize member initialization lists.
Snakes are initialized with a member initialized list. Each snake is initialized at a random point instead of the middle of the screen. 
4. The project uses multithreading.
For each snake, a thread is launched to handle the input. 
5. Classes encapsulate behavior.
First, a game would have a score. Now, snakes have a score, so that snake class contains score as an attribute and the game class updates the score of the snakes.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
