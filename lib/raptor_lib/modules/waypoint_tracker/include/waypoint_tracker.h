#pragma once

#include "MocapPubSubTypes.h"
#include "QuadPositionCmdPubSubTypes.h"
#include "default_publisher.h"
#include "default_subscriber.h"
#include "geometry_msgs/msgs/Position.h"
#include "motion_controller.h"
#include "quadcopter_msgs/msgs/QuadPositionCmd.h"
#include "raptor.h"
#include "sensor_msgs/msgs/Mocap.h"
#include <cmath>
#include <cstring>

class WaypointTracker {

public:
  WaypointTracker(eprosima::fastdds::dds::DomainParticipant *participant);
  ~WaypointTracker(){};

private:
  // Containers to store waypoints
  std::vector<float> x_waypoint_{};
  std::vector<float> y_waypoint_{};
  std::vector<float> z_waypoint_{};
  std::vector<float> max_time_{};

public:
  // Positions limits to attain to be consodered reached
  cpp_msg::Position pos_thresholds_;

  // Pointer to motion controller
private:
  std::unique_ptr<MotionCtrl> motion_ctrl;

public:
  bool go_to_waypoint(const int index, const MotionCtrl::type ctrl_type);
  bool go_to_waypoint(const cpp_msg::Position waypoint, const float max_time,
                      const MotionCtrl::type ctrl_type);

public:
  void load_waypoints(const std::string path);

  void set_parameters(const std::string path);
};