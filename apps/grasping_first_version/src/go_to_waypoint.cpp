#include "grasper.h"

/// Setter function
bool Grasper::go_to_waypoint(const int index, const ctrl_type type) {

  static cpp_msg::Position waypoint{};
  waypoint.x = x_waypoint_.at(index);
  waypoint.y = y_waypoint_.at(index);
  waypoint.z = z_waypoint_.at(index);

  // load max reaching time
  float max_reach_time = max_reach_time_.at(index);

  // Intiailize position waypoints
  bool status = go_to_pos(quad_pose_.pose.position, waypoint, pos_thresholds_,
                          max_reach_time, type);

  return status;
}
