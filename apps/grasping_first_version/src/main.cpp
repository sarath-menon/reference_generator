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
  // grasper.set_setpoints(paths::setpoints_path);

  cpp_msg::Position desired_pos;

  // Setting desired pos
  desired_pos.x = 1.0;
  desired_pos.y = 1.0;
  desired_pos.z = 1.5;
  bool status = grasper.set_desired_pos(desired_pos);

  std::cout << "Target status:" << status << std::endl;

  // for (int i = 0; i < 10; i++) {

  //   grasper.mocap_sub->listener->wait_for_data();

  //   std::cout << "x position:" << grasper.current_pose().pose.position.x
  //             << std::endl;
  // }
}
