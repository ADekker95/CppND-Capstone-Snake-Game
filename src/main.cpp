#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <vector>

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  // unsigned int for number of snakes in game
  constexpr std::size_t nSnakes = 2;
  
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  // we need separate keys to control the snakes
  Controller controller1(SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT);
  // wasd is another frequently used set as alternative to arrows
  Controller controller2(SDLK_w, SDLK_a, SDLK_s, SDLK_d);
  
  Game game(kGridWidth, kGridHeight, nSnakes);
  // preferably, I would have used the controller instances in a container, because this is not really scalable if we wanted to have more snakes than 2 but I could not make it work
  game.Run(controller1, controller2, renderer, kMsPerFrame, nSnakes);
  std::cout << "Game has terminated successfully!\n";
  
  // determine winning snake 
  int snakeIndex = game.GetIndexWinningSnake();
  // calculate score and size of winning snake
  std::cout << "Score: " << game.GetScoreWinningSnake(snakeIndex) << "\n";
  std::cout << "Size: " << game.GetSizeWinningSnake(snakeIndex) << "\n";
  return 0;
}
