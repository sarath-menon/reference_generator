#pragma once

#include "MocapPubSubTypes.h"
#include "QuadPositionCmdPubSubTypes.h"
#include "geometry_msgs/msgs/Position.h"
#include "quadcopter_msgs/msgs/QuadPositionCmd.h"
#include "sensor_msgs/msgs/Mocap.h"
#include <cmath>
#include <cstring>

class Behaviour {

public:
  Behaviour();
  ~Behaviour();

public:
  virtual void start(){};
  virtual void stop(){};

private:
  // Quadcopter position
  cpp_msg::Mocap quad_pose_{};

  // Object position
  cpp_msg::QuadPositionCmd quad_pos_cmd{};

public:
  /// Getter function
  const cpp_msg::Mocap &current_pose() const { return quad_pose_; }

public:
  virtual void set_parameters(const std::string path){};
};