#include "grasper.h"
// grip_cmd=1 -> gripper opens
// grip_cmd=0 -> gripper closes
bool Grasper::grip(const int grip_msg) {
  if (grip_msg == 0 | grip_msg == 1) {  // check for valid commands
    grip_cmd.position.x = grip_msg;     // define grip command
    gripper_pub->publish(grip_cmd);     // publish grip command
  } else {
    std::cerr << "invalid command" << std::endl;
    return 1;
  }
  return 0;
}