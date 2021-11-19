#include "grasper.h"

/// Setter function
bool Grasper::go_over_object(const std::string object, const float height,
                             const ctrl_type type) {

  // check object name
  if (object_pose_.header.id.compare(object) == 0) {

    static cpp_msg::Position setpoint{};
    setpoint.x = object_pose_.pose.position.x;
    setpoint.y = object_pose_.pose.position.y;
    setpoint.z = object_pose_.pose.position.z + height;

    // Intiailize position targets
    bool status = go_to_pos(quad_pose_.pose.position, setpoint, pos_thresholds_,
                            max_grasp_time_, type);

    return status;
  } else {
    std::cout << " srl box object not available" << std::endl;
    return false;
  }
}