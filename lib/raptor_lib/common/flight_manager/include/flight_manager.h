#pragma once

#include "MocapPubSubTypes.h"
#include "QuadPositionCmdPubSubTypes.h"
#include "default_participant.h"
#include "default_publisher.h"
#include "default_subscriber.h"
#include "geometry_msgs/msgs/Position.h"
#include "quadcopter_msgs/msgs/QuadPositionCmd.h"
#include "raptor.h"
#include "sensor_msgs/msgs/Mocap.h"
#include "waypoint_tracker.h"
#include <cmath>
#include <cstring>

class FlightManager {

public:
  FlightManager(Raptor &raptor);
  ~FlightManager(){};

private:
  std::unique_ptr<WaypointTracker> wp_tracker;

  // fastdds
private:
public:
  // const float &xy_threshold() const { return xy_threshold_; }

public:
  void register_dds(eprosima::fastdds::dds::DomainParticipant *participant);
  void set_parameters(const std::string path);
};