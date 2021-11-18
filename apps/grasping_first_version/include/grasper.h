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

  // Containers to store setpoints
  std::vector<float> x_setpoint_;
  std::vector<float> y_setpoint_;
  std::vector<float> z_setpoint_;
  std::vector<float> max_reach_time_;

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
  const std::array<float, 3> &setpoint(const float index) const {

    static std::array<float, 3> setpoint{};
    setpoint[0] = x_setpoint_.at(index);
    setpoint[1] = y_setpoint_.at(index);
    setpoint[2] = z_setpoint_.at(index);

    return setpoint;
  }

  /// Getter function
  const float &max_reach_time(const float index) const {

    static float max_reach_time{};
    max_reach_time = max_reach_time_.at(index);
    return max_reach_time;
  }

public:
  /// Setter function
  bool go_to_pos(const int index);

public:
  void set_parameters(const std::string path);

  void load_setpoints(const std::string path);
};