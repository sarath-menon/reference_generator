#include "grasper.h"

/// Setter function
bool Grasper::go_to_waypoint(const int index,
                             const MotionCtrl::type ctrl_type) {

  static cpp_msg::Position wp{};
  wp.x = x_wp_list.at(index);
  wp.y = y_wp_list.at(index);
  wp.z = z_wp_list.at(index);

  // load max reaching time
  float max_time = max_time_.at(index);

  // Intiailize position waypoints
  bool status = go_to_pos(quad_pose_.pose.position, wp, pos_thresholds_,
                          max_time, ctrl_type);

  return status;
}

bool Grasper::go_to_waypoint(const cpp_msg::Position wp, const float max_time,
                             const ctrl_type type) {

  // Intiailize position waypoints
  bool status = go_to_pos(quad_pose_.pose.position, wp, pos_thresholds_,
                          max_time, ctrl_type);

  return status;
}
