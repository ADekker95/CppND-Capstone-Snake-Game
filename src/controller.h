#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "game.h"
#include "snake.h"
#include "SDL.h"
#include <set>

class Controller {
 public:
  Controller(const SDL_Keycode up, const SDL_Keycode down, const SDL_Keycode left, const SDL_Keycode right):
   	up_(up),
    down_(down),
    left_(left),
    right_(right)
    {
    };
  
  ~Controller();
  void HandleInput(bool &running, Snake &snake) const;

 private:
  SDL_Keycode up_;
  SDL_Keycode down_;
  SDL_Keycode left_;
  SDL_Keycode right_;
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif
