#include "QuadPositionCmdPubSubTypes.h"
#include "default_participant.h"
#include "default_publisher.h"
#include "quadcopter_msgs/msgs/QuadPositionCmd.h"
#include <chrono>
#include <cstdlib>
#include <future>

int main() {
  // Quadcopter position msg
  cpp_msg::QuadPositionCmd pos_msg{};

  // Create participant. Arguments-> Domain id, QOS name
  DefaultParticipant dp(0, "quad_reference_publisher");

  // Create publisher with msg type
  DDSPublisher position_pub(idl_msg::QuadPositionCmdPubSubType(), "pos_cmd",
                            dp.participant());

  // Initialize publisher
  position_pub.init();

  // Go to center
  pos_msg.position.z = 1;
  position_pub.publish(pos_msg);
  // Delay for quad to catch up
  std::this_thread::sleep_for(std::chrono::seconds(4));

  pos_msg.position.x = 0.5;
  position_pub.publish(pos_msg);
  // Delay for quad to catch up
  std::this_thread::sleep_for(std::chrono::seconds(4));

  pos_msg.position.y = 0.5;
  position_pub.publish(pos_msg);
  // Delay for quad to catch up
  std::this_thread::sleep_for(std::chrono::seconds(4));

  pos_msg.position.x = -0.5;
  position_pub.publish(pos_msg);
  // Delay for quad to catch up
  std::this_thread::sleep_for(std::chrono::seconds(4));

  pos_msg.position.x = 0;
  pos_msg.position.y = 0;
  position_pub.publish(pos_msg);
  // Delay for quad to catch up
  std::this_thread::sleep_for(std::chrono::seconds(4));
}
