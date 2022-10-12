#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::HandleInput(bool &running, std::vector<<Snake>> &snakes) const {
  SDL_Event e;
  // TODO NOT ELEGANT BUT HOW TO SOLVE THIS
  control_set_snake1.insert(SDLK_UP);
  control_set_snake1.insert(SDLK_DOWN);
  control_set_snake1.insert(SDLK_RIGHT);
  control_set_snake1.insert(SDLK_LEFT);
  control_set_snake2.insert(SDLK_w);
  control_set_snake2.insert(SDLK_a);
  control_set_snake2.insert(SDLK_s);
  control_set_snake2.insert(SDLK_d);
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        // determine snake, arrows for snake 1, wasd for snake 2
        if (control_set_snake1.count(e.key.keysym.sym)){
          snake = snakes[0]
        else: 
          snake = snakes[1]
        }
       
        case (SDLK_UP or SDLK_w):
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case (SDLK_DOWN or SDLK_s):
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case (SDLK_LEFT or SDLK_a):
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case (SDLK_RIGHT or SDLK_d):
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
      }
    }
  }
}
