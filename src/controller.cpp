#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"
#include "game.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::HandleInput(bool &running, Snake &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } 
    else if (e.type == SDL_KEYDOWN) {
      // use if else statements instead of switch because switch statements not available at both compile time and run time
      if (e.key.keysym.sym == _Up) {
        ChangeDirection(snake, Snake::Direction::kUp, Snake::Direction::kDown);
        break;
      }
      else if (e.key.keysym.sym == _Down){
        ChangeDirection(snake, Snake::Direction::kDown, Snake::Direction::kUp);
        break;
      }
      else if (e.key.keysym.sym == _Left){
        ChangeDirection(snake, Snake::Direction::kLeft, Snake::Direction::kRight);
        break;
      }
      else {
        ChangeDirection(snake, Snake::Direction::kRight, Snake::Direction::kLeft);
        break;
      }
    }
  }
}
