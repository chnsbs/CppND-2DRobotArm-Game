#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "robot.h"
#include <vector>

class Renderer {
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t kGameFieldPadding);
  ~Renderer();

  void Render(const Robot &robot, const SDL_Point &target);
  void UpdateWindowTitle(int score, int fps);

private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t kGameFieldPadding;
};

#endif