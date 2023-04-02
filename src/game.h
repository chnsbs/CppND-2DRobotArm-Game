#ifndef GAME_H
#define GAME_H
#include "SDL.h"
#include "controller.h"
#include "link.h"
#include "renderer.h"
#include "robot.h"
#include <iostream>
#include <random>

class Game {
public:
  Game(){};
  ~Game(){};
  static double distanceBetweenPoints(SDL_Point point1, SDL_Point point2);
  void Run(Controller const &controller, Renderer &renderer, Robot &robot,
           std::size_t target_frame_duration);
  int GetScore() const { return score; }
  int GetSize() const { return 1; }

private:
  SDL_Point target;
  double distance_to_target_;
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceTarget(double centerX, double centerY, double radius);
  void Update(Robot &robot);
};
#endif