#include "game.h"

void Game::Run(Controller const &controller, Renderer &renderer, Robot &robot,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  PlaceTarget(robot.baseX, robot.baseY,
              robot.link1->getLength() + robot.link2->getLength());

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, robot);
    Update(robot);
    renderer.Render(robot, target);

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

SDL_Point randomPositionInCircle(double centerX, double centerY,
                                 double radius) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_real_distribution<> angle_distribution(0, 2 * M_PI);
  std::uniform_real_distribution<> radius_distribution(0, radius);

  double angle = angle_distribution(rng);
  double dist = std::sqrt(radius_distribution(rng)) * radius;

  SDL_Point position;
  position.x = centerX + dist * std::cos(angle);
  position.y = centerY + dist * std::sin(angle);

  return position;
}

void Game::PlaceTarget(double centerX, double centerY, double radius) {

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_real_distribution<> angle_distribution(0, 2 * M_PI);
  std::uniform_real_distribution<> radius_distribution(0, 1);

  double angle = angle_distribution(rng);
  double dist = std::sqrt(radius_distribution(rng)) * radius;

  target.x = centerX + static_cast<int>(dist * std::cos(angle));
  target.y = centerY + static_cast<int>(dist * std::sin(angle));

  std::cout << "Placing the target-> (" << target.x << "," << target.y << ")\n";
}

void Game::Update(Robot &robot) {
  if (!robot.alive)
    return;

  robot.Update();

  distance_to_target_ = Game::distanceBetweenPoints(
      target, SDL_Point{robot.joint3->x, robot.joint3->y});
  // Check if there's target over end effector
  if (distance_to_target_ < 5.0f) {
    score++;
    PlaceTarget(robot.baseX, robot.baseY,
                robot.link1->getLength() + robot.link2->getLength());
  }
}

double Game::distanceBetweenPoints(SDL_Point point1, SDL_Point point2) {
  double dx = point2.x - point1.x;
  double dy = point2.y - point1.y;
  return std::sqrt(dx * dx + dy * dy);
}