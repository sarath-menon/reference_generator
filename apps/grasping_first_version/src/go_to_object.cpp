#include "grasper.h"

/// Setter function
bool Grasper::go_to_object(const std::string object,
                           const float max_reach_time) {

  // check object name
  if (object_pose_.header.id.compare("srl_object") == 0) {

    // Intiailize position targets
    bool status =
        go_to_pos(quad_pose_.pose.position, object_pose_.pose.position,
                  pos_thresholds_, max_reach_time);

    return status;
  } else {
    std::cout << " srl quad object not available" << std::endl;
    return false;
  }
}
