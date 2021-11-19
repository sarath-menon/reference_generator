#pragma once

#include "MocapPubSubTypes.h"
#include "QuadPositionCmdPubSubTypes.h"
#include "default_participant.h"
#include "default_publisher.h"
#include "default_subscriber.h"
#include "geometry_msgs/msgs/Position.h"
#include "helper.h"
#include "quadcopter_msgs/msgs/QuadPositionCmd.h"
#include "sensor_msgs/msgs/Mocap.h"
#include <math.h>

class Grasper {
public:
  Grasper();
  ~Grasper();

private:
  // Current state
  cpp_msg::Mocap quad_pose_{};

  // position cmd sent to quad
  cpp_msg::QuadPositionCmd quad_pos_cmd{};

public:
  // Create doamin participant
  std::unique_ptr<DefaultParticipant> dp;

  // Motion capture data subscriber
  DDSSubscriber<idl_msg::MocapPubSubType, cpp_msg::Mocap> *mocap_sub;

  // Create publisher with msg type
  DDSPublisher *position_pub;

  // parameter
private:
  // controller sampling time in seconds
  float dt_{};

  // controller sampling time in milliseconds
  int delay_time_{};

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

  // Positions limits to attain to be consodered reached
  cpp_msg::Position pos_thresholds_;

public:
  /// Getter function
  const cpp_msg::Mocap &current_pose() const { return quad_pose_; }

  /// Getter function
  const float &dt() const { return dt_; }

  /// Getter function
  const cpp_msg::Position &pos_thresholds() const { return pos_thresholds_; }

  /// Getter function
  const float &xy_threshold() const { return xy_threshold_; }

  /// Getter function
  const float &z_threshold() const { return z_threshold_; }

public:
  /// Setter function
  bool go_to_pos(const cpp_msg::Position &current_pos,
                 const cpp_msg::Position &target_pos,
                 const cpp_msg::Position &pos_thresholds, const float max_time);

  bool go_to_waypoint(const int index);

public:
  void set_parameters(const std::string path);

  void load_waypoints(const std::string path);
};