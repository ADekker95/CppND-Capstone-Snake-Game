#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(std::size_t grid_width, std::size_t grid_height)
      : grid_width(grid_width),
        grid_height(grid_height) {}

  
  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  float head_x;
  float head_y;
  // instead of a game score, each snake now has a score
  int score{0};
  bool alive{true};
  std::vector<SDL_Point> body;
  void SetHead(float x, float y);


 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;

};

#endif
