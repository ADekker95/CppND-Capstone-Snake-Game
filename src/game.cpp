#include "game.h"
#include <iostream>
#include "SDL.h"
#include <cmath>

Game::Game(std::size_t grid_width, std::size_t grid_height):
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      engine(dev()),
      {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration, int nSnakes) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  
  // initialize snakes at random position in grid
  for (size_t ns = 0; ns < nSnakes; ns++)
  {
  	snakes.push_back(Snake(grid_width, grid_height, random_w(engine), random_h(engine)));
  }
  
  int score_delta = Game::CalculateScore()
    
  // game stops if not running or score_delta is > 2 
  while (running and score_delta < 2) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snakes);
    Update();
    score_delta = Game::UpdateScore();
    renderer.Render(snakes, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
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
    // TODO should we use smart pointer here?
    for (s:snakes) {
      if (!s.SnakeCell(x, y)) {
        food.x = x;
        food.y = y;
        return;
      }
    }
  }
}

int Game::CalcScoreDelta() {
	return abs(snakes[0].score - snakes[1].score)  
} 
void Game::Update() {
  // if any of the snakes is dead return
  for (s:snakes) {
    if (!s.alive) return;

    s.Update();

    int new_x = static_cast<int>(s.head_x);
    int new_y = static_cast<int>(s.head_y);

    // Check if there's food over here
    if (food.x == new_x && food.y == new_y) {
      score++;
      // Grow snake and increase speed.
      s.GrowBody();
      s.speed += 0.02;
    }
  }
  // we want only one food piece for all the snakes per update
  PlaceFood();  
}
                    
bool CompareScore(a,b){
	return (a.score < b.score);	
}

// Return index of winning snake 
int Game::GetIndexWinningSnake() const { 
  return std::max_element(snakes.begin(), snakes.end(), CompareScore);
}
                    
int Game::GetScoreWinningSnake(int index) const { return snakes[index].score; }
int Game::GetSizeWinningSnake(int index) const { return snakes[index].size; }
