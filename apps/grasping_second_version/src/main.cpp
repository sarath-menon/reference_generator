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
  grasper.load_setpoints(paths::setpoint_list_path);

  // // old working
  // bool result = grasper.go_to_pos(0);
  // result = grasper.go_to_pos(1);
  // result = grasper.go_to_pos(2);

  // new automatic
  bool result = grasper.go_near_object(0.0, 0.0, 0.5, 10);

  // grasping step
  result = grasper.go_near_object(0.0, 0.0, 0.5, 10);

  // Delay for grasping
  //  Delay for quad to catch up
  std::this_thread::sleep_for(std::chrono::seconds(2));

  result = grasper.go_to_pos(4);
  result = grasper.go_to_pos(5);
}
