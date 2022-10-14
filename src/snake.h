#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  //Initalize the snake at a random place
  Snake(std::size_t grid_width, std::size_t grid_height, int start_head_x, int start_head_y)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(start_head_x),
        head_y(start_head_y) {}

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  // instead of a game score, each snake now has a score
  int score{0};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif
