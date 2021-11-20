
#include "geometry_msgs/msgs/Position.h"
#include "grasper.h"
#include "paths.h"
#include "set_circle_parameters.h"

int main() {

  Grasper grasper;
  // shorter enumerations for convenience
  Grasper::ctrl_type px4_ctrl = Grasper::ctrl_type::px4;

  // set parameters
  grasper.set_parameters(paths::ctrl_prm);
  set_circle_parameters(paths::circle_prm);
  bool result{};

  cpp_msg::Position current_pos;

  for (int i = 0; i < 360; i++) {

    // COmpute x,y coordinates
    // std::cout << "Timestep:" << i << '\n';
    current_pos.x = prm::center_x + prm::radius * cos(prm::theta);
    current_pos.y = prm::center_y + prm::radius * sin(prm::theta);
    current_pos.z = prm::altitude;

    theta += step_size;

    // Track waypoint
    result = grasper.go_to_waypoint(0, px4_ctrl);
  }
}
