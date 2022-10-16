#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::PlaceSnakeHead(float x, float y){
  head_x = x;
  head_y = y;
}

void Snake::Update(Snake const &CompetitorSnake) {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell, CompetitorSnake);
  }
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell, Snake const &CompetitorSnake) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  // Due to collision with itself 
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
      std::cout << "Collision with own body \n";
      return;
    }
  }
  
  // Due to collision with the body of other snake 
  for (auto const &item : CompetitorSnake.body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
      std::cout << "Collision with other snake body \n";
      return;
    }
  }
  // Due to collision with the head of the other snake 
  if (current_head_cell.x == static_cast<int>(CompetitorSnake.head_x) && current_head_cell.y == static_cast<int>(CompetitorSnake.head_y)) {
    alive = false;
    std::cout << "Collision with other snake head \n";
    return;
  } 
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}
