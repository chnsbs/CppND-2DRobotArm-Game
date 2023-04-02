#include "controller.h"
#include "SDL.h"
#include "robot.h"
#include <iostream>

void Controller::HandleInput(bool &running, Robot &robot) const {
  SDL_Event e;
  const Uint8 *state = SDL_GetKeyboardState(NULL);

  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
      // Joint 1
      if (state[SDL_SCANCODE_LEFT]) {
        robot.IncreaseJointAngle(2);
        // robot.LogJointAngles();
      }
      if (state[SDL_SCANCODE_RIGHT]) {
        robot.DecreaseJointAngle(2);
        // robot.LogJointAngles();
      }

      // Joint 2
      if (state[SDL_SCANCODE_UP]) {
        robot.IncreaseJointAngle(1);
        // robot.LogJointAngles();
      }
      if (state[SDL_SCANCODE_DOWN]) {
        robot.DecreaseJointAngle(1);
        // robot.LogJointAngles();
      }
    }
  }
}