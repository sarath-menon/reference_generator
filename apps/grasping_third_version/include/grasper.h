#pragma once

#include <math.h>

#include "MocapPubSubTypes.h"
#include "QuadPositionCmdPubSubTypes.h"
#include "RapidTrajectoryGenerator.h"
#include "Vec3.h"
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
  // Current grip_cmd
  cpp_msg::Mocap quad_pose_{};

  // position cmd sent to quad
  cpp_msg::QuadPositionCmd quad_pos_cmd{};

  // gripper cmd sent to quad
  cpp_msg::QuadPositionCmd grip_cmd{};

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

  // Create publisher with msg type
  DDSPublisher *gripper_pub;

  // parameter
 private:
  // controller sampling time in seconds
  float dt_{};

  // controller sampling time in milliseconds
  int delay_time_{};

  // new parameters
  float startPoint_completion_time_{};
  int startPoint_wait_swoop_{};
  float swoop_completion_time_{};
  int swoop_wait_mid_{};

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
  const int &delay_time() const { return delay_time_; }

  /// Getter function
  const float &startPoint_completion_time() const {
    return startPoint_completion_time_;
  }

  /// Getter function
  const int &startPoint_wait_swoop() const { return startPoint_wait_swoop_; }

  /// Getter function
  const float &swoop_completion_time() const { return swoop_completion_time_; }

  /// Getter function
  const int &swoop_wait_mid() const { return swoop_wait_mid_; }

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
  bool go_to_pos(const float x_ref, const float y_ref, const float z_ref,
                 const float time, const bool pos_flag);

  /**
   * Goes to the given position using minimal jerk algorithm
   *
   * @param[in] pos_init starting position
   * @param[in] vel_init starting velocity
   * @param[in] acc_init starting acceleration
   * @param[in] pos_fin target position
   * @param[in] vel_fin target velocity
   * @param[in] acc_fin target acceleration
   * @param[in] g gravity
   * @returns Bool : Target has been reached ?
   **/
  bool go_to_pos_minJerk(const Vec3 pos_init, const Vec3 vel_init,
                         const Vec3 acc_init, const Vec3 pos_fin,
                         const Vec3 vel_fin, const Vec3 acc_fin, const Vec3 g,
                         const float completion_time);

  bool grip(const int grip_msg);

  bool go_near_object(const float x_ref, const float y_ref, const float z_ref,
                      const float time, const bool pos_flag,
                      std::string topic_name);

  bool departure(const float z_ref, const float time, const bool pos_flag);

 public:
  void set_parameters(const std::string path);

  void load_setpoints(const std::string path);

  bool wait_for_data_quad() {
    // mocap_quad_sub->listener->wait_for_data();
    for (int i = 0; i < 30; i++) {
      float id = quad_pose_.pose.position.x;
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return true;
  }
  bool wait_for_data_object() {
    // mocap_object_sub->listener->wait_for_data();
    for (int i = 0; i < 30; i++) {
      float id = object_pose_.pose.position.x;
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return true;
    return true;
  }
  bool wait_for_data_stand() {
    // mocap_stand_sub->listener->wait_for_data();
    for (int i = 0; i < 30; i++) {
      float id = stand_pose_.pose.position.x;
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return true;
    return true;
  }
};