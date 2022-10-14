#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, std::size_t nSnakes);
  void Run(Controller const &controller1, Controller const &controller2, Renderer &renderer, std::size_t target_frame_duration, int nSnakes);
  int GetIndexWinningSnake() const;
  int GetScoreWinningSnake(int index) const;
  int GetSizeWinningSnake(int index) const;
  int CalculateScoreDelta() const;

 private:
  // create a vector of snakes 
  std::vector<Snake> snakes;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  void PlaceFood();
  void Update();
};

#endif
