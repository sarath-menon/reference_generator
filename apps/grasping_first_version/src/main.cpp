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

  grasper.set_parameters(paths::parameters_path);
  grasper.load_waypoints(paths::waypoint_list_path);

  bool result = grasper.go_to_waypoint(0);
  result = grasper.go_to_waypoint(1);
  result = grasper.go_to_waypoint(2);

  // Delay for grasping
  result = grasper.go_to_object("srl_quad", 10);
  std::this_thread::sleep_for(std::chrono::seconds(2));

  result = grasper.go_to_waypoint(4);
  result = grasper.go_to_waypoint(5);

  // std::cout << "Target status:" << status << std::endl;
}
