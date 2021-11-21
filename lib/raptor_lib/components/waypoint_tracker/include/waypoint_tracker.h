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
  std::vector<float> max_reach_time_{};

public:
  // Positions limits to attain to be consodered reached
  cpp_msg::Position pos_thresholds_;

  // maximum time allowed for grasping
  float max_grasp_time_{};

  // Pointer to motion controller
private:
  std::unique_ptr<MotionController> motion_ctrl;

public:
  void load_waypoints(const std::string path);

  void set_parameters(const std::string path);
};