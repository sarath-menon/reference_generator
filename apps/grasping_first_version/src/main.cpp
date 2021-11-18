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

  bool result = grasper.go_to_pos(0);

  // std::cout << "Target status:" << status << std::endl;
}
