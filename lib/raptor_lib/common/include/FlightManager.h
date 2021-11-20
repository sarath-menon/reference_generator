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

class FlightManager {
public:
  FlightManager();
  ~FlightManager(){};

private:
  // Create doamin participant
  std::unique_ptr<DefaultParticipant> dp;

  // static members
private:
  static int raptor_count_;
  static int object_count_;

public:
  /// Getter function
  const int &raptor_count() const { return raptor_count_; }

  /// Getter function
  const int &object_count() const { return object_count_; }

public:
  // Register a new raptor in the flight manager
  void add_raptor(const std::string name);

  // Register a new object in the flight manager
  void add_object(const std::string name);
};