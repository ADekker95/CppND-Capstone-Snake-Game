#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "snake.h"
#include "SDL.h"

class Controller {
 public:
  // Connect user defined control keys to the right private variables 
  Controller(const SDL_Keycode up, const SDL_Keycode down, const SDL_Keycode left, const SDL_Keycode right):
      _Up(up),
      _Down(down),
      _Left(left),
      _Right(right) {}
  
  void HandleInput(bool &running, Snake &snake) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input, Snake::Direction opposite) const;
  // Keys to handle directions of snake 
  SDL_Keycode _Up;
  SDL_Keycode _Down;
  SDL_Keycode _Left;
  SDL_Keycode _Right;
  
};

#endif
