#ifndef ROBOT_H
#define ROBOT_H

#include "joint.h"
#include "link.h"
#include <SDL.h>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>
#define PI 3.14159265

class Robot {
public:
  // Constructor
  Robot(float link1_length, float link2_length, float base_x, float base_y);
  ~Robot();

  // Helper Log
  void LogPositions() const;
  void LogJointAngles() const;

  // Forward kinematics
  void forwardKinematics();

  // Inverse kinematics
  bool inverseKinematics(double x, double y);

  void setBase(double baseX, double baseY);
  std::vector<std::shared_ptr<Link>> getLinks() const {
    return {base_link, link1, link2, end_effector};
  };
  std::vector<std::shared_ptr<Joint>> getJoints() const {
    return {joint1, joint2, joint3};
  };

  void Update();
  void IncreaseJointAngle(int jointIndex);
  void DecreaseJointAngle(int jointIndex);

  bool alive = true;
  std::shared_ptr<Link> base_link;
  std::shared_ptr<Link> link1;
  std::shared_ptr<Link> link2;
  std::shared_ptr<Link> end_effector;
  std::shared_ptr<Joint> joint1;
  std::shared_ptr<Joint> joint2;
  std::shared_ptr<Joint> joint3;
  double baseX;
  double baseY;

private:
};
#endif