#include "QuadPositionCmdPubSubTypes.h"
#include "default_participant.h"
#include "default_publisher.h"
#include "quadcopter_msgs/msgs/QuadPositionCmd.h"
#include <chrono>
#include <cstdlib>
#include <future>

// Step size in degrees
constexpr static float step_size = 0.1;

// center angle in degrees
float theta = 0;

// Radius of circle to be tracked (in meters)
constexpr static float radius = 1.5;

// Local center
constexpr static float center_x = 0;
constexpr static float center_y = 0;

// constant altitude
constexpr static float const_altitude = 1.5;

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

  // Go to circle start point
  pos_msg.position.z = const_altitude;
  pos_msg.position.x = 1;
  position_pub.publish(pos_msg);

  // Delay for quad to catch up
  std::this_thread::sleep_for(std::chrono::seconds(5));

  for (int i = 0; i < 3601; i++) {

    // COmpute x,y coordinates
    // std::cout << "Timestep:" << i << '\n';
    pos_msg.position.x = center_x + radius * cos(theta);
    pos_msg.position.y = center_y + radius * sin(theta);

    theta += step_size;

    // Delay for quad to catch up
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    position_pub.publish(pos_msg);
  }
}
