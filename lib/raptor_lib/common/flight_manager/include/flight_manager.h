#pragma once

#include "MocapPubSubTypes.h"
#include "QuadPositionCmdPubSubTypes.h"
#include "behaviour.h"
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
  FlightManager(const std::string raptor_name);
  ~FlightManager(){};

private:
  // pointer to domain participant
  inline static DefaultParticipant *dp_;

  std::unique_ptr<Raptor> raptor_ptr_;

public:
  // sequence of behavioirs to be executed
  std::vector<std::unique_ptr<Behaviour>> behav_register;

  // waypoint tracker
  std::unique_ptr<WaypointTracker> wp_tracker;

public:
  // register fastdds domain participant
  static void register_dds(DefaultParticipant *dp);

  // Add a behaviours
  void add_behaviour(std::unique_ptr<Behaviour> &&behav);

  void set_parameters(const std::string path);
};