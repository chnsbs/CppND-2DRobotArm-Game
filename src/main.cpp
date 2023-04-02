#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <iostream>

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGameFieldPadding{20};

  Renderer renderer(kScreenWidth, kScreenHeight, kGameFieldPadding);
  Controller controller;
  Game game;
  Robot robot(100, 150, 320, 320);
  game.Run(controller, renderer, robot, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  return 0;
}