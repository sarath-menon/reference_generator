#pragma once

#include "MocapPubSubTypes.h"
#include "QuadPositionCmdPubSubTypes.h"
#include "default_participant.h"
#include "default_publisher.h"
#include "default_subscriber.h"
#include "geometry_msgs/msgs/Position.h"
#include "quadcopter_msgs/msgs/QuadPositionCmd.h"
#include "sensor_msgs/msgs/Mocap.h"
#include <math.h>

class Raptor {
public:
  Raptor(const std::string &name);
  ~Raptor();

private:
  std::string name_{};

public:
  void set_parameters(const std::string path);
};
