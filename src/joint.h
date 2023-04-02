#ifndef JOINT_H
#define JOINT_H

#include "link.h"

class Joint {
public:
  // Constructor
  Joint(double angle, const Link &parent_link, const Link &child_link)
      : angle_(angle), child_link_(child_link), parent_link_(parent_link) {}

  // Getters and setters
  double getAngle() const { return angle_; }
  void setAngle(double angle) { angle_ = angle; }
  Link getChildLink() { return child_link_; }
  Link getParentLink() { return parent_link_; }
  // public position variables
  // x,y is where the joint is located
  double x;
  double y;

  void IncreaseAngle() { angle_ += angle_increment_; };

  void DecreaseAngle() { angle_ -= angle_increment_; };

private:
  double angle_;
  Link child_link_;
  Link parent_link_;
  double angle_increment_ = 1.0f;
};
#endif