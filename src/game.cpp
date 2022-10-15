#include "game.h"
#include <iostream>
#include "SDL.h"
#include <cmath>
#include <algorithm>
#include <vector>
#include <thread>

// Game constructor, initialize food and snakes at random places
Game::Game(std::size_t grid_width, std::size_t grid_height, std::size_t nSnakes):
    engine(dev()),
    random_w(0, static_cast<int>(grid_width - 1)),
    random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
  for (std::size_t ns = 0; ns < nSnakes; ns++){
  	snakes.push_back(Snake(grid_width, grid_height));
  }  
  // Initialize snakes at random position in grid
  PlaceSnakes(nSnakes);
}

void Game::Run(Controller const &controller1, Controller const &controller2, Renderer &renderer, std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  
  int score_delta = Game::CalculateScoreDelta();
    
  // game stops if not running or score_delta is > 2 
  while (running and score_delta < 2) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop. 
    std::vector<std::thread> threads;
    
    // we need to use std::ref to pass references to a function launched in a thread 
    for (std::vector<Snake>::size_type i = 0; i != snakes.size(); i++){
      if (i == 0){
        // use emplace back instead of push back (would create copy and we do not want that)
        threads.emplace_back(std::thread(&Controller::HandleInput, controller1, std::ref(running), std::ref(snakes[i])));
      }
      else {
        threads.emplace_back(std::thread(&Controller::HandleInput, controller2, std::ref(running), std::ref(snakes[i])));
      }
    }
    
    // unite the flow of execution threads
    for (auto &t : threads)
        t.join();
    
    Update();
    score_delta = Game::CalculateScoreDelta();
    renderer.Render(snakes, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      // display scores of each snake
      renderer.UpdateWindowTitle(snakes, frame_count);
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
    // Check that the location is not occupied by a snake item before placing food.
    for (auto &s:snakes) {
      if (!s.SnakeCell(x, y)) {
        food.x = x;
        food.y = y;
        return;
      }
    }
  }
}


void Game::PlaceSnakes(std::size_t nSnakes) {
  // initialize snakes for the game, each at random position in grid
  for (std::size_t i; i<nSnakes; i++){
    float x = random_w(engine);
    float y = random_h(engine);    
  	snakes[i].SetHead(x, y);
  }  
}

// Calculate score difference between the two scores
int Game::CalculateScoreDelta() const {
	return abs(snakes[0].score - snakes[1].score);
} 

void Game::Update() {
  // if any of the snakes is dead return
  for (auto &s:snakes) {
    if (!s.alive) return;

    s.Update();

    int new_x = static_cast<int>(s.head_x);
    int new_y = static_cast<int>(s.head_y);

    // Check if there's food over here
    if (food.x == new_x && food.y == new_y) {
      s.score++;
      // Grow snake and increase speed.
      s.GrowBody();
      s.speed += 0.02;
    }
  }
  // we want only one food piece for all the snakes per update
  PlaceFood();  
}
                    
// Return index of winning snake 
int Game::GetIndexWinningSnake() const { 
   auto result = std::max_element(snakes.begin(), snakes.end(), [](const Snake &a, const Snake &b)
        {
          return std::abs(a.score) < std::abs(b.score);
       });
   return std::distance(snakes.begin(), result);
}

int Game::GetScoreWinningSnake(int index) const { return snakes[index].score; }
int Game::GetSizeWinningSnake(int index) const { return snakes[index].size; }
