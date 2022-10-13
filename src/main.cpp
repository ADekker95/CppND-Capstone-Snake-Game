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

  int nSnakes = 2;
  
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  // we need separate keys to control the snakes 
  std::vector<Controller> controllers(Controller(SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT), Controller(SDLK_w, SDLK_a, SDLK_s, SDLK_d));
  
  Game game(kGridWidth, kGridHeight, nSnakes);
  game.Run(controllers, renderer, kMsPerFrame, &nSnakes);
  std::cout << "Game has terminated successfully!\n";
  // determine winning snake 
  int snakeIndex = game.GetIndexWinningSnake();
  std::cout << "Score: " << game.GetScoreWinningSnake(snakeIndex) << "\n";
  std::cout << "Size: " << game.GetSizeWinningSnake(snakeIndex) << "\n";
  return 0;
}
