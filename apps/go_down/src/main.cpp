#include "QuadAttitudeCommandPubSubTypes.h"
#include "default_participant.h"
#include "default_publisher.h"
#include "quadcopter_msgs/msgs/QuadAttitudeCommand.h"
#include <chrono>
#include <cstdlib>
#include <future>

int main() {
  // Quadcopter position msg
  cpp_msg::QuadAttitudeCommand att_msg{};

  // Create participant. Arguments-> Domain id, QOS name
  DefaultParticipant dp(0, "quad_reference_publisher");

  // Create publisher with msg type
  DDSPublisher att_pub(idl_msg::QuadAttitudeCommandPubSubType(), "attitude_cmd",
                            dp.participant());

  // Initialize publisher
  att_pub.init();

  constexpr static float starting_height = 1.5;
  constexpr static float stop_height = 0.5;

  constexpr static float motor_max_thrust = 8.986;
  constexpr static float quad_max_thrust = motor_max_thrust*4;
  constexpr static float hover_thrust = 9.81/quad_max_thrust;


  constexpr static float start_thrust = 0.26;
  constexpr static float stop_thrust = 0.245;

  // Starting at hover thrust
  att_msg.thrust = start_thrust;
  att_msg.pitch = 0.0;
  att_msg.yaw = 0.0;
  att_msg.roll = 0.0;
  att_pub.publish(att_msg);

  // Delay for quad to catch up
  std::this_thread::sleep_for(std::chrono::seconds(3));

  std::cout<<"Starting to lower thrust"<<std::endl;

  while (att_msg.thrust>stop_thrust) {

    // COmpute x,y coordinates
    // std::cout << "Timestep:" << i << '\n';
    att_msg.thrust -= 0.005;

    // Delay for quad to catch up
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout<<"Thrust"<<att_msg.thrust<<std::endl;

    att_pub.publish(att_msg);
  }

   // Increase to hover thrust again
  att_msg.thrust = 0.26;
  att_msg.pitch = 0.0;
  att_msg.yaw = 0.0;
  att_msg.roll = 0.0;
  att_pub.publish(att_msg);

  std::cout<<"Hovering again"<<att_msg.thrust<<std::endl;

   // Delay for quad to catch up
  std::this_thread::sleep_for(std::chrono::seconds(8));

  std::cout<<"Kill now"<<att_msg.thrust<<std::endl;


}
