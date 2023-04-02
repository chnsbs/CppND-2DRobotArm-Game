#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t kGameFieldPadding)
    : screen_width(screen_width), screen_height(screen_height),
      kGameFieldPadding(kGameFieldPadding) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Qix CHN", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(const Robot &robot, const SDL_Point &target) {
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render robot links and joints
  std::vector<std::shared_ptr<Link>> links = robot.getLinks();
  std::vector<std::shared_ptr<Joint>> joints = robot.getJoints();

  // Set color for the robot links
  SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);

  for (const std::shared_ptr<Link> &link : links) {
    SDL_RenderDrawLine(sdl_renderer, link->x1, link->y1, link->x2, link->y2);
  }

  // Set color for the robot joints
  SDL_SetRenderDrawColor(sdl_renderer, 0, 255, 0, 255);

  for (const std::shared_ptr<Joint> &joint : joints) {
    SDL_Rect rect;
    rect.x = joint->x - 2; // Adjust based on joint size
    rect.y = joint->y - 2; // Adjust based on joint size
    rect.w = 4;            // Adjust based on joint size
    rect.h = 4;            // Adjust based on joint size
    SDL_RenderFillRect(sdl_renderer, &rect);
  }

  // Render the target point
  SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 0, 255);
  SDL_Rect targetRect;
  targetRect.x = target.x - 2; // Adjust based on target point size
  targetRect.y = target.y - 2; // Adjust based on target point size
  targetRect.w = 4;            // Adjust based on target point size
  targetRect.h = 4;            // Adjust based on target point size
  SDL_RenderFillRect(sdl_renderer, &targetRect);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Robot Score: " + std::to_string(score) +
                    " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
