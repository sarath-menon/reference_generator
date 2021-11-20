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
  // minimum position difference to start grasping
  float xy_threshold_{};
  float z_threshold_{};

  // Indicates whether target position has been reached or not
  bool x_reach_flag{};
  bool y_reach_flag{};
  bool z_reach_flag{};
  bool all_reach_flag{};

  // Containers to store waypoints
  std::vector<float> x_waypoint_{};
  std::vector<float> y_waypoint_{};
  std::vector<float> z_waypoint_{};
  std::vector<float> max_reach_time_{};

public:
  // Positions limits to attain to be consodered reached
  cpp_msg::Position pos_thresholds_;

  // maximum time allowed for grasping
  float max_grasp_time_{};

  /// Getter function
  const cpp_msg::Position &pos_thresholds() const { return pos_thresholds_; }

  /// Getter function
  const float &xy_threshold() const { return xy_threshold_; }

  /// Getter function
  const float &z_threshold() const { return z_threshold_; }

  /// Getter function
  const float &max_grasp_time() const { return max_grasp_time_; }

public:
  void load_waypoints(const std::string path);

  void set_parameters(const std::string path);
};