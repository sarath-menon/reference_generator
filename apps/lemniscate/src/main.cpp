#include "include_helper.h"

int main() {
  // Quadcopter position msg
  cpp_msg::QuadPositionCmd pos_msg{};

  // set lemniscate parameters
  set_parameters(paths::lemniscate_prm);

  // Create participant. Arguments-> Domain id, QOS name
  DefaultParticipant dp(0, "quad_reference_publisher");

  // Create publisher with msg type
  DDSPublisher position_pub(idl_msg::QuadPositionCmdPubSubType(), "pos_cmd",
                            dp.participant());

  // Initialize publisher
  position_pub.init();

  // Go to circle start point
  pos_msg.position.z = prm::altitude;
  pos_msg.position.x = prm::a;
  position_pub.publish(pos_msg);

  // Delay for quad to catch up
  std::this_thread::sleep_for(std::chrono::seconds(5));

  Timer t;

  // start timer
  t.start();

  while (t.sec() < 10.0) {

    // position control
    pos_msg.position.x =
        (prm::a * cos(prm::omega * t)) / (1.0 + pow(sin(prm::omega * t), 2));

    pos_msg.position.y = (prm::a * cos(prm::omega * t) * sin(prm::omega * t)) /
                         (1.0 + pow(sin(prm::omega * t), 2));

    // Delay for quad to catch up
    std::this_thread::sleep_for(std::chrono::milliseconds(20));

    position_pub.publish(pos_msg);
  }
}
