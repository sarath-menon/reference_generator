#include "QuadPositionCmdPubSubTypes.h"
#include "default_participant.h"
#include "default_publisher.h"
#include "quadcopter_msgs/msgs/QuadPositionCmd.h"
#include <chrono>
#include <cstdlib>
#include <future>

// angle in radians
float theta = 0;
float theta_dot = 0.5;
constexpr static float dt = 0.1;
constexpr static int dt_ms = dt * 1000;
constexpr static float a = 1.5;

// Radius of circle to be tracked (in meters)
constexpr static float radius = 0.5;

// Local center
constexpr static float center_x = 0;
constexpr static float center_y = 0;

// constant altitude
constexpr static float const_altitude = 1.5;

// //starting position
// float px=2*a;
// float py=0;
// float pz=0;

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
  pos_msg.position.x = a;
  position_pub.publish(pos_msg);

  // // Delay for quad to catch up
  std::this_thread::sleep_for(std::chrono::seconds(5));

  // for (int i = 0; i < i_max * 2; i++) {
  for (;;) { //(int i = 0; i < i_max * circles_number; i++) {

    // position control
    pos_msg.position.x = (a * cos(theta)) / (1.0 + pow(sin(theta), 2));
    pos_msg.position.y =
        (a * cos(theta) * sin(theta)) / (1.0 + pow(sin(theta), 2));
    // pz=0;

    // incrementing theta
    theta += theta_dot * dt;

    // Delay for quad to catch up
    std::this_thread::sleep_for(std::chrono::milliseconds(dt_ms));

    position_pub.publish(pos_msg);
  }
}
