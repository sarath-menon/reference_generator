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
  grasper.load_waypoints(paths::mueller_waypoints_path);

  // Step 1: go to starting position
  // argument: index of waypoint in text file
  bool result = grasper.go_to_waypoint(0, mueller_ctrl);

  // Step 2: go to object
  // argument: index of waypoint in text file
  result = grasper.go_to_waypoint(1, mueller_ctrl);

  // Step 2: grasp object
  // argument: object name, max allowed time
  result = grasper.go_to_object("srl_box", px4_ctrl);
  std::this_thread::sleep_for(std::chrono::seconds(2));

  // step 3: drop off object
  result = grasper.go_to_waypoint(2, mueller_ctrl);

  std::cout << "checking";

  // std::cout << "Target status:" << status << std::endl;
}
