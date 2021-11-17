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

class Grasper {
public:
  Grasper();
  ~Grasper();

private:
  // Current state
  cpp_msg::Mocap current_pose_{};

  // Current state
  cpp_msg::Position desired_pos_{};

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
public:
  // time to complete grasping manueuver
  float grasping_time_{};

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

public:
  /// Getter function
  const cpp_msg::Mocap &current_pose() const { return current_pose_; }

  /// Getter function
  const cpp_msg::Position &desired_pos() const { return desired_pos_; }

  /// Getter function
  const float &dt() const { return dt_; }

  /// Getter function
  const float &xy_threshold() const { return xy_threshold_; }

  /// Getter function
  const float &z_threshold() const { return z_threshold_; }

  /// Getter function
  const float &grasping_time() const { return grasping_time_; }

public:
  /// Setter function
  bool go_to_pos();

public:
  void set_parameters(const std::string path);

  void set_setpoints(const std::string path, const int index);
};