#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  std::size_t allowed_score_delta;

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  
  Controller controller1(SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT);
  // wasd is another frequently used set as alternative to arrows
  Controller controller2(SDLK_w, SDLK_s, SDLK_a, SDLK_d);
  
  std::cout << "Determine the point difference when the snake has won \n ";
  std::cout << "Type a positive number: ";
  std::cin >> allowed_score_delta;
  Game game(kGridWidth, kGridHeight, allowed_score_delta);
  game.Run(controller1, controller2, renderer, kMsPerFrame);
  std::cout << "Game has terminated\n";
  if (game.score_delta > static_cast<int>(allowed_score_delta)){
    std::cout << "Snake " << game.GetWinningSnake() << " has won! \n";
    std::cout << "Score of winning snake: " << game.GetScore() << "\n";
    std::cout << "Size of winning snake: " << game.GetSize() << "\n";
  }
  else {
  	std::cout << "Game ended due to collision!\n";    
  }
  return 0;
}
