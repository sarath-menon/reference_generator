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
  Grasper::ctrl_type px4_ctrl = Grasper::ctrl_type::px4;
  Grasper::ctrl_type mueller_ctrl = Grasper::ctrl_type::mueller;

  grasper.set_parameters(paths::parameters_path);
  grasper.load_waypoints(paths::waypoint_list_path);

  // argument: index of waypoint in text file
  bool result = grasper.go_to_waypoint(0, px4_ctrl);
  result = grasper.go_to_waypoint(1, px4_ctrl);
  result = grasper.go_to_waypoint(2, px4_ctrl);

  // Delay for grasping
  // argument: object name, max allowed time
  result = grasper.go_to_object("srl_quad", px4_ctrl);
  std::this_thread::sleep_for(std::chrono::seconds(2));

  result = grasper.go_to_waypoint(4, px4_ctrl);
  result = grasper.go_to_waypoint(5, px4_ctrl);

  // std::cout << "Target status:" << status << std::endl;
}
