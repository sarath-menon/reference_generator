
#include "QuadPositionCmdPubSubTypes.h"
#include "default_participant.h"
#include "default_publisher.h"
#include "geometry_msgs/msgs/Position.h"
#include "paths.h"
#include "quadcopter_msgs/msgs/QuadPositionCmd.h"
#include "set_circle_parameters.h"
#include "timer.h"

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

  set_circle_parameters(paths::circle_prm);

  // Go to circle start point
  pos_msg.position.z = prm::altitude;
  pos_msg.position.x = 1;
  position_pub.publish(pos_msg);

  // Delay for quad to catch up
  std::this_thread::sleep_for(std::chrono::seconds(5));

  Timer t;

  // start timer
  t.start();

  while (t.sec() < 30.0) {

    // COmpute x,y coordinates
    // std::cout << "Timestep:" << i << '\n';
    pos_msg.position.x = prm::center_x + prm::radius * cos(prm::omega * t);
    pos_msg.position.y = prm::center_y + prm::radius * sin(prm::omega * t);

    // Delay for quad to catch up
    std::this_thread::sleep_for(std::chrono::milliseconds(20));

    position_pub.publish(pos_msg);
  }
}
