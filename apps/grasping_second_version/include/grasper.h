#pragma once

#include <math.h>

#include "MocapPubSubTypes.h"
#include "QuadPositionCmdPubSubTypes.h"
#include "default_participant.h"
#include "default_publisher.h"
#include "default_subscriber.h"
#include "geometry_msgs/msgs/Position.h"
#include "helper.h"
#include "quadcopter_msgs/msgs/QuadPositionCmd.h"
#include "sensor_msgs/msgs/Mocap.h"

class Grasper {
 public:
  Grasper();
  ~Grasper();

 private:
  // Current state
  cpp_msg::Mocap quad_pose_{};

  // position cmd sent to quad
  cpp_msg::QuadPositionCmd quad_pos_cmd{};

  // object position
  cpp_msg::Mocap object_pose_{};

  // stand position
  cpp_msg::Mocap stand_pose_{};

 public:
  // Create doamin participant
  std::unique_ptr<DefaultParticipant> dp;

  // Motion capture data subscriber for quadcopter
  DDSSubscriber<idl_msg::MocapPubSubType, cpp_msg::Mocap> *mocap_quad_sub;

  // Motion capture data subscriber for grabbed object
  DDSSubscriber<idl_msg::MocapPubSubType, cpp_msg::Mocap> *mocap_object_sub;

  // Motion capture data subscriber for stand
  DDSSubscriber<idl_msg::MocapPubSubType, cpp_msg::Mocap> *mocap_stand_sub;

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

  // Containers to store setpoints
  std::vector<float> x_setpoint_{};
  std::vector<float> y_setpoint_{};
  std::vector<float> z_setpoint_{};
  std::vector<float> max_reach_time_{};

  // object name
  std::string object_name_{};
  std::string quad_name_{};
  // DDS topic prefix
  std::string topic_prefix_{};

 public:
  /// Getter function
  const cpp_msg::Mocap &quad_pose() const { return quad_pose_; }

  /// Getter function
  const cpp_msg::Mocap &object_pose() const { return object_pose_; }

  /// Getter function
  const cpp_msg::Mocap &stand_pose() const { return stand_pose_; }

  /// Getter function
  const float &dt() const { return dt_; }

  /// Getter function
  const float &xy_threshold() const { return xy_threshold_; }

  /// Getter function
  const float &z_threshold() const { return z_threshold_; }

  /// Getter function
  cpp_msg::Position &setpoint(const float index) const {
    static cpp_msg::Position setpoint{};
    setpoint.x = x_setpoint_.at(index);
    setpoint.y = y_setpoint_.at(index);
    setpoint.z = z_setpoint_.at(index);

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
  bool go_to_pos(const int index, const bool pos_flag);

  bool go_near_object(const float x_ref, const float y_ref, const float z_ref,
                      const float time, const bool pos_flag,
                      std::string topic_name);

  bool departure(const float z_ref, const float time, const bool pos_flag);

 public:
  void set_parameters(const std::string path);

  void load_setpoints(const std::string path);
};