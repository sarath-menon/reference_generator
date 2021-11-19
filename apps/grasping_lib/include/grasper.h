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
  // Quadcopter position
  cpp_msg::Mocap quad_pose_{};

  // Object position
  cpp_msg::QuadPositionCmd quad_pos_cmd{};

  // Current state
  cpp_msg::Mocap object_pose_{};

public:
  // Create doamin participant
  std::unique_ptr<DefaultParticipant> dp;

  // quadcopter pose subscriber
  DDSSubscriber<idl_msg::MocapPubSubType, cpp_msg::Mocap> *quad_sub;

  // object pose subscriber
  DDSSubscriber<idl_msg::MocapPubSubType, cpp_msg::Mocap> *object_sub;

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

  // maximum time allowed for grasping
  float max_grasp_time_{};

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

  /// Getter function
  const float &max_grasp_time() const { return max_grasp_time_; }

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

  void load_waypoints(const std::string path);
};