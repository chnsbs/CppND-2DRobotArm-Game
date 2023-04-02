#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "robot.h"

class Controller {
public:
  void HandleInput(bool &running, Robot &Robot) const;

private:
};

#endif