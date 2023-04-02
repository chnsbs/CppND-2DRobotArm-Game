#ifndef LINK_H
#define LINK_H

class Link {
public:
  // Constructor
  Link(double length, bool isBase = false, bool isEndEffector = false)
      : length_(length) {}

  // Getters and setters
  double getLength() const { return length_; }
  void setLength(double length) { length_ = length; }

  // public position variables
  // x1,y1 is where the link is located
  // x2,y3 is where the link ends
  double x1;
  double y1;
  double x2;
  double y2;
  bool isBase;
  bool isEndEffector;

private:
  double length_;
};
#endif