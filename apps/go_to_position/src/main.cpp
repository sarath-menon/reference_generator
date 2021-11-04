#include "QuadPositionCmdPubSubTypes.h"
#include "default_participant.h"
#include "default_publisher.h"
#include "paths.h"
#include "quadcopter_msgs/msgs/QuadPositionCmd.h"
#include "set_parameters.h"
#include <chrono>
#include <cstdlib>
#include <future>

int main() {

  // Set parameters
  set_parameters(paths::setpoint_path);

  // econds to milliseconds
  const int delay_time = parameters::dt * 1000;

  // Quadcopter position msg
  cpp_msg::QuadPositionCmd pos_cmd{};

  // Create participant. Arguments-> Domain id, QOS name
  DefaultParticipant dp(0, "quad_reference_publisher");

  // Create publisher with msg type
  DDSPublisher position_pub(idl_msg::QuadPositionCmdPubSubType(), "pos_cmd",
                            dp.participant());

  // Initialize publisher
  position_pub.init();

  // Set position
  pos_cmd.position.x = parameters::x_position;
  pos_cmd.position.y = parameters::y_position;
  pos_cmd.position.z = parameters::z_position;

  for (int i = 0; i < 300; i++) {
    // for (;;) {
    // Go to center
    position_pub.publish(pos_cmd);
    // // Delay for quad to catch up
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));
  }
}
