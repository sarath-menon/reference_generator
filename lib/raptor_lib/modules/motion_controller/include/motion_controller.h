#pragma once

#include "MocapPubSubTypes.h"
#include "QuadPositionCmdPubSubTypes.h"
#include "default_publisher.h"
#include "default_subscriber.h"
#include "geometry_msgs/msgs/Position.h"
#include "quadcopter_msgs/msgs/QuadPositionCmd.h"
#include "sensor_msgs/msgs/Mocap.h"
#include <math.h>

class MotionCtrl {
public:
  MotionCtrl(eprosima::fastdds::dds::DomainParticipant *participant);
  ~MotionCtrl();

public:
  // types of setpoint genetratore
  enum class type { px4, mueller };

private:
  // Quadcopter position
  cpp_msg::Mocap quad_pose_{};

  // Object position
  cpp_msg::QuadPositionCmd quad_pos_cmd{};

  // quadcopter pose subscriber
  DDSSubscriber<idl_msg::MocapPubSubType, cpp_msg::Mocap> *quad_sub;

  // Create publisher with msg type
  DDSPublisher *position_pub;

  // parameter
private:
  // controller sampling time in seconds
  float dt_{};

  // controller sampling time in milliseconds
  int delay_time_{};

private:
  // check whether postion has been reached
  bool check_reached(const float &current_pos, const float &desired_pos,
                     const float &threshold);

  // go to target position
  bool go_to_pos(const cpp_msg::Position &current_pos,
                 const cpp_msg::Position &target_pos,
                 const cpp_msg::Position &pos_thresholds, const float max_time,
                 const type ctrl_type);

  cpp_msg::Position muller_controller(const cpp_msg::Position &current_pos,
                                      const cpp_msg::Position &target_pos,
                                      const float max_time, const float dt);

public:
  /// Setter function
  void set_parameters(const std::string path);

public:
  /// Getter function
  const float &dt() const { return dt_; }
};
