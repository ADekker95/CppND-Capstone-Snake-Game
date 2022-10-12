#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "SDL.h"
#include <set>

class Controller {
 public:
  // TODO how to initialize these sets more elegantly
  // keys to manage snake 1
  std::set<SDL_Keycode> control_set_snake1; // ({SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT});
  // keys to manage snake 2
  std::set<SDL_Keycode> control_set_snake2; // ({SDLK_w, SDLK_a, SDLK_s, SDLK_d}); 
  void HandleInput(bool &running, Snake &snake) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif
