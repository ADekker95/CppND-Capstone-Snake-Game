#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, std::size_t allowed_score_delta);
  void Run(Controller const &controller1, Controller const &controller2, Renderer &renderer, std::size_t target_frame_duration);
  int GetWinningSnake() const;
  int GetScore() const;
  int GetSize() const;
  void CalculateScoreDelta(Snake const &snake1, Snake const &snake2);
  // initially the snake have a score difference of 0
  int score_delta{0};
  size_t allowed_score_delta;

 private:
  Snake snake;
  Snake snake2;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  void PlaceFood();
  void Update();
};

#endif
