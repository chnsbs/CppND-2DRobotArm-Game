#include "robot.h"
#include "iostream"

void Robot::Update() {
  // LogPositions();
  forwardKinematics();
};

Robot::Robot(float link1_length, float link2_length, float base_x, float base_y)
    : base_link(std::make_shared<Link>(0.0)),
      link1(std::make_shared<Link>(link1_length)),
      link2(std::make_shared<Link>(link2_length)),
      end_effector(std::make_shared<Link>(0.0)),
      joint1(std::make_shared<Joint>(0.0, *base_link, *link1)),
      joint2(std::make_shared<Joint>(0.0, *link1, *link2)),
      joint3(std::make_shared<Joint>(0.0, *link2, *end_effector)),
      baseX(base_x), baseY(base_y) {
  base_link->isBase = true;
  end_effector->isEndEffector = true;
};

Robot::~Robot(){};

void Robot::LogPositions() const {
  std::cout << "Positions of links and joints:\n";

  int index = 1;
  for (const auto &link : {base_link, link1, link2, end_effector}) {
    std::cout << "Link " << index << ": (" << link->x1 << ", " << link->y1
              << ") -> (" << link->x2 << ", " << link->y2 << ")\n";
    ++index;
  }

  index = 1;
  for (const auto &joint : {joint1, joint2, joint3}) {
    std::cout << "Joint " << index << ": (" << joint->x << ", " << joint->y
              << ")\n";
    ++index;
  }
}

// Forward kinematics
void Robot::forwardKinematics() {
  // Base_link
  base_link->x1 = baseX;
  base_link->y1 = baseY;
  base_link->x2 = baseX;
  base_link->y2 = baseY;

  // Joint1
  joint1->x = base_link->x2;
  joint1->y = base_link->y2;

  // Link_1
  link1->x1 = joint1->x;
  link1->y1 = joint1->y;
  link1->x2 =
      link1->x1 + link1->getLength() * cos(joint1->getAngle() * PI / 180.0);
  link1->y2 =
      link1->y1 - link1->getLength() * sin(joint1->getAngle() * PI / 180.0);

  // Joint2
  joint2->x = link1->x2;
  joint2->y = link1->y2;

  // Link_2
  link2->x1 = joint2->x;
  link2->y1 = joint2->y;
  link2->x2 =
      link2->x1 + link2->getLength() * cos(joint2->getAngle() * PI / 180.0);
  link2->y2 =
      link2->y1 - link2->getLength() * sin(joint2->getAngle() * PI / 180.0);

  // Joint 3
  joint3->x = link2->x2;
  joint3->y = link2->y2;

  // End Effector
  end_effector->x1 = joint3->x;
  end_effector->y1 = joint3->y;
  end_effector->x2 = joint3->x;
  end_effector->y2 = joint3->y;
};

// Inverse kinematics
bool Robot::inverseKinematics(double x, double y) {
  // TODO
  return true;
};

void Robot::IncreaseJointAngle(int jointIndex) {
  if (jointIndex == 1) {
    joint1->IncreaseAngle();
  } else if (jointIndex == 2) {
    joint2->IncreaseAngle();
  }
};

void Robot::DecreaseJointAngle(int jointIndex) {
  if (jointIndex == 1) {
    joint1->DecreaseAngle();
  } else if (jointIndex == 2) {
    joint2->DecreaseAngle();
  }
};

void Robot::LogJointAngles() const {
  std::vector<std::shared_ptr<Joint>> joints = this->getJoints();

  for (std::size_t i = 0; i < joints.size(); ++i) {
    std::cout << "Joint " << i + 1 << " angle: " << joints[i]->getAngle()
              << " degrees" << std::endl;
  }
}

// Getters and setters
void Robot::setBase(double baseX, double baseY) {
  baseX = baseX;
  baseY = baseY;
};
