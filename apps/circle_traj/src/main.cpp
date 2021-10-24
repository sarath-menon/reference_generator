#include "PositionPubSubTypes.h"
#include "default_participant.h"
#include "default_publisher.h"
#include "sensor_msgs/msgs/Mocap.h"
#include <chrono>
#include <cstdlib>
#include <future>

Position offset{};

// Step size in degrees
float step_size = 0.1;

// center angle in degrees
float theta = 0;

// Radius of circle to be tracked (in meters)
const float radius = 0.5;

// Local center
const float center_x = 0;
const float center_y = 0;

// constant altitude
constexpr static float const_altitude = 1.5;

int main() {
  // Message
  Position position{};

  // Create participant. Arguments-> Domain id, QOS name
  DefaultParticipant dp(0, "quare_traj_publisher");

  // Create publisher with msg type
  DDSPublisher position_pub(PositionPubSubType(), "pos_cmd", dp.participant());

  // Initialize publisher
  position_pub.init();

  // Go to circle start point
  position.z(const_altitude);
  position.x(1);
  position_pub.publish(position);

  // Delay for quad to catch up
  std::this_thread::sleep_for(std::chrono::seconds(5));

  for (int i = 0; i < 3601; i++) {

    // COmpute x,y coordinates
    // std::cout << "Timestep:" << i << '\n';
    position.x(center_x + radius * cos(theta));
    position.y(center_y + radius * sin(theta));

    theta += step_size;

    // Delay for quad to catch up
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    position_pub.publish(position);
  }
}
