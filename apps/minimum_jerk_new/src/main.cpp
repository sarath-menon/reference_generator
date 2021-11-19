#include "QuadPositionCmdPubSubTypes.h"
#include "default_participant.h"
#include "default_publisher.h"
#include "grasper.h"
#include "paths.h"
#include "quadcopter_msgs/msgs/QuadPositionCmd.h"
#include <chrono>
#include <cstdlib>
#include <future>

int main() {
  Grasper grasper;
  // shorter enumerations for convenience
  Grasper::ctrl_type mueller_ctrl = Grasper::ctrl_type::mueller;
  Grasper::ctrl_type px4_ctrl = Grasper::ctrl_type::px4;

  grasper.set_parameters(paths::parameters_path);
  grasper.load_waypoints(paths::waypoints_path);
  bool result{};

  // Track waypoints
  result = grasper.go_to_waypoint(0, px4_ctrl);
  result = grasper.go_to_waypoint(1, px4_ctrl);
  result = grasper.go_to_waypoint(2, px4_ctrl);
  result = grasper.go_to_waypoint(3, px4_ctrl);

  // std::cout << "Target status:" << status << std::endl;
}
