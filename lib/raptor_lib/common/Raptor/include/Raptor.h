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

class Raptor {
public:
  Raptor(eprosima::fastdds::dds::DomainParticipant *participant);
  ~Raptor();

private:
  // Quadcopter position
  cpp_msg::Mocap quad_pose_{};

  // Object position
  cpp_msg::QuadPositionCmd quad_pos_cmd{};

public:
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

public:
  /// Getter function
  const cpp_msg::Mocap &current_pose() const { return quad_pose_; }

  /// Getter function
  const float &dt() const { return dt_; }

public:
  enum class ctrl_type { px4, mueller };

private:
  /// Setter function
  bool go_to_pos(const cpp_msg::Position &current_pos,
                 const cpp_msg::Position &target_pos,
                 const cpp_msg::Position &pos_thresholds, const float max_time,
                 const ctrl_type type);

  cpp_msg::Position muller_controller(const cpp_msg::Position &current_pos,
                                      const cpp_msg::Position &target_pos,
                                      const float max_time, const float dt);

public:
  bool go_to_waypoint(const int index, const ctrl_type type);
  bool go_to_waypoint(const cpp_msg::Position waypoint,
                      const float max_reach_time, const ctrl_type type);

  bool go_over_object(const std::string object, const float height,
                      const ctrl_type type);

  bool grasp_object(const std::string object, const ctrl_type type);

public:
  void set_parameters(const std::string path);
};
