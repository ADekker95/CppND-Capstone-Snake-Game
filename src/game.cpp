#include "game.h"
#include <iostream>
#include "SDL.h"
#include <vector>
#include <thread>

Game::Game(std::size_t grid_width, std::size_t grid_height, std::size_t allowed_score_delta)
    : snake(grid_width, grid_height),
      snake2(grid_width, grid_height),
	  allowed_score_delta(allowed_score_delta),
	  engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)){
  // initialize snakes at random position
  snake.PlaceSnakeHead(random_w(engine), random_h(engine));
  snake2.PlaceSnakeHead(random_w(engine), random_h(engine));
  PlaceFood();
}

// Calculate score difference between the two scores
void Game::CalculateScoreDelta(Snake const &snake1, Snake const &snake2) {
	score_delta = abs(snake.score - snake2.score);
} 


void Game::Run(Controller const &controller1, Controller const &controller2, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  
  while (running) {
    if (score_delta > static_cast<int>(allowed_score_delta)) return;
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
 	std::vector<std::thread> threads;
    
    // we need to use std::ref to pass references to a function launched in a thread 
    // use emplace back instead of push back (would create copy and we do not want that)
    for (std::size_t i = 0; i<2; i++){
      if (i == 0){
        threads.emplace_back(std::thread(&Controller::HandleInput, controller1, std::ref(running), std::ref(snake)));
      }
      else if (i == 1){
        threads.emplace_back(std::thread(&Controller::HandleInput, controller2, std::ref(running), std::ref(snake2)));
      }
    }
    
    // unite the flow of execution threads
    for (auto &t : threads)
        t.join();
    
    Update();
    // if one snake has died during update, the game must stop
    if (!snake.alive || !snake2.alive) {
      running = false;
    }
    CalculateScoreDelta(snake, snake2);
    renderer.Render(snake, snake2, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(snake, snake2, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) && !snake2.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive || !snake2.alive) return;

  // also we must stop the game if a snake has died during update
  snake.Update(snake2);
  if (!snake.alive) return;
  snake2.Update(snake);
  if (!snake2.alive) return;
  
  int new_x_snake = static_cast<int>(snake.head_x);
  int new_y_snake = static_cast<int>(snake.head_y);
  int new_x_snake2 = static_cast<int>(snake2.head_x);
  int new_y_snake2 = static_cast<int>(snake2.head_y);

  // Check if there's food over here
  if (food.x == new_x_snake && food.y == new_y_snake) {
    snake.score++;
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
    PlaceFood();
  }
  else if (food.x == new_x_snake2 && food.y == new_y_snake2) {
    snake2.score++;
    // Grow snake and increase speed.
    snake2.GrowBody();
    snake2.speed += 0.02;
    PlaceFood();
  }
  
}

int Game::GetWinningSnake() const {
    if (snake.score > snake2.score){
      return 1; 
    }
    else{
      return 2;
	}
}
    
int Game::GetScore() const { return std::max(snake.score, snake2.score); }
int Game::GetSize() const { return std::max(snake.size, snake2.size); }
