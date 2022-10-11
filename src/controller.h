#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

// keys to manage snake 1
enum ControlKeys1 {
  SDLK_UP,
  SDLK_DOWN,
  SDLK_LEFT,
  SDLK_RIGHT  
} 

// keys to manage snake 2
enum ControlKeys2 {
  SDLK_w,
  SDLK_a,
  SDLK_s,
  SDLK_d
}

class Controller {
 public:
  void HandleInput(bool &running, Snake &snake) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif
