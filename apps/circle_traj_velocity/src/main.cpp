#include "QuadVelocityCmdPubSubTypes.h"
#include "default_participant.h"
#include "default_publisher.h"
#include "quadcopter_msgs/msgs/QuadVelocityCmd.h"
#include <chrono>
#include <cstdlib>
#include <future>
#include <math.h>

// Step size in seconds
constexpr static float dt = 0.1;
constexpr static int dt_ms = dt * 1000;

// angel in radians
float theta = 0;
// angular velocity in rad/s
constexpr static float theta_dot = 1.5;

// Radius of circle to be tracked (in meters)
constexpr static float radius = 0.5;

// Local center
constexpr static float center_x = 0;
constexpr static float center_y = 0;

// constant altitude
constexpr static float const_altitude = 1.5;

int main() {
  // Quadcopter position msg
  cpp_msg::QuadVelocityCmd velocity_msg{};

  // Create participant. Arguments-> Domain id, QOS name
  DefaultParticipant dp(0, "quad_reference_publisher");

  // Create publisher with msg type
  DDSPublisher velocity_pub(idl_msg::QuadVelocityCmdPubSubType(),
                            "velocity_cmd", dp.participant());

  // Initialize publisher
  velocity_pub.init();

  // // Delay for quad to catch up
  // std::this_thread::sleep_for(std::chrono::seconds(5));
  constexpr static int i_max = (2 * M_PI) / (theta_dot * dt);
  constexpr static int circles_number = 4;

  // for (int i = 0; i < i_max * 2; i++) {
  for (int i = 0; i < i_max * circles_number; i++) {

    // COmpute x,y coordinates
    // std::cout << "Timestep:" << i << '\n';
    velocity_msg.velocity.x = -theta_dot * radius * sin(theta);
    velocity_msg.velocity.y = theta_dot * radius * cos(theta);
    velocity_msg.velocity.z = 0;

    theta += (theta_dot * dt);
    std::cout << "Angle:" << theta * 180 / M_PI << std::endl;

    // Delay for quad to catch up
    std::this_thread::sleep_for(std::chrono::milliseconds(dt_ms));

    velocity_pub.publish(velocity_msg);
  }

  // Set velocity to zero at the end
  velocity_msg.velocity.x = 0;
  velocity_msg.velocity.y = 0;
  velocity_msg.velocity.z = 0;
  velocity_pub.publish(velocity_msg);
}