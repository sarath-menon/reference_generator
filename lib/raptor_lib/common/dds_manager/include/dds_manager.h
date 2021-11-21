#pragma once

#include "MocapPubSubTypes.h"
#include "QuadPositionCmdPubSubTypes.h"
#include "default_participant.h"
#include "default_publisher.h"
#include "default_subscriber.h"
#include "geometry_msgs/msgs/Position.h"
#include "quadcopter_msgs/msgs/QuadPositionCmd.h"
#include "sensor_msgs/msgs/Mocap.h"
#include <cmath>
#include <cstring>

class DDSManager {

public:
  DDSManager();
  ~DDSManager(){};

private:
  // Create doamin participant
  std::unique_ptr<DefaultParticipant> dp;

public:
  /// Getter function
  auto participant() const { return dp.get(); }

} inline DDS;