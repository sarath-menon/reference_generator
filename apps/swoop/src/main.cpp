
#include "grasper.h"
#include "paths.h"

int main() {
  Grasper grasper;
  // shorter enumerations for convenience
  Grasper::ctrl_type mueller_ctrl = Grasper::ctrl_type::mueller;
  Grasper::ctrl_type px4_ctrl = Grasper::ctrl_type::px4;

  grasper.set_parameters(paths::parameters_path);
  grasper.load_waypoints(paths::waypoints_path);
  bool result{};

  // Track waypoints
  result = grasper.go_to_waypoint(0, mueller_ctrl);
  result = grasper.go_to_waypoint(1, mueller_ctrl);
  result = grasper.go_to_waypoint(2, mueller_ctrl);

  // // Track waypoints
  // result = grasper.go_to_waypoint(0, mueller_ctrl);
  // result = grasper.go_to_waypoint(1, mueller_ctrl);
}
