#include "QuadPositionCmdPubSubTypes.h"
#include "default_participant.h"
#include "default_publisher.h"
#include "helper.h"
#include "paths.h"
#include "quadcopter_msgs/msgs/QuadPositionCmd.h"
#include "set_parameters.h"
#include <chrono>
#include <cstdlib>
#include <future>

// acceleration

// define the duration:
double Tf = 1.0;

double f_min = 5;         //[m/s**2]
double f_max = 25;        //[m/s**2]
double wmax = 20;         //[rad/s]
double minTimeSec = 0.01; //[s]

// Define how gravity lies in our coordinate system
Vec3 gravity = Vec3(0, 0, -9.81); //[m/s**2]

// Define the state constraints. We'll only check that we don't fly into the
// floor:
Vec3 floorPos = Vec3(0, 0, 0); // any point on the boundary
Vec3 floorNormal =
    Vec3(0, 0, 1); // we want to be in this direction of the boundary

int main() {

  // Set parameters
  set_parameters(paths::setpoint_path);

  // Define the trajectory starting state:
  Vec3 pos0 = Vec3(parameters::x_start, parameters::y_start,
                   parameters::z_start); // position
  Vec3 vel0 = Vec3(0, 0, 0);             // velocity
  Vec3 acc0 = Vec3(0, 0, 0);             // acceleration

  // define the goal state:
  Vec3 posf = Vec3(parameters::x_mid, parameters::y_mid,
                   parameters::z_mid); // position
  Vec3 velf = Vec3(0, 0, 0);           // velocity
  Vec3 accf = Vec3(0, 0, 0);

  // Generate trajectory
  RapidTrajectoryGenerator traj(pos0, vel0, acc0, gravity);

  // seconds to milliseconds
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

  // Generate trajectory
  traj.SetGoalPosition(posf);
  traj.SetGoalVelocity(velf);
  traj.SetGoalAcceleration(accf);
  traj.Generate(Tf);

  // Set position
  pos_cmd.position.x = parameters::x_start;
  pos_cmd.position.y = parameters::y_start;
  pos_cmd.position.z = parameters::z_start;

  // Publish command
  position_pub.publish(pos_cmd);

  // Delay for quad to catch up
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));

  std::cout << "Starting swooping";

  for (double i = 0; i < Tf; i += parameters::dt) {
    // Set position
    pos_cmd.position.x = traj.GetPosition(i).x;
    pos_cmd.position.y = traj.GetPosition(i).y;
    pos_cmd.position.z = traj.GetPosition(i).z;

    std::cout << "Timestep:" << i << std::endl;
    std::cout << "Position:" << '\t' << traj.GetPosition(i).x << '\t'
              << traj.GetPosition(i).y << '\t' << traj.GetPosition(i).z
              << std::endl;

    // Publish command
    position_pub.publish(pos_cmd);

    // Delay for quad to catch up
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));
  }

  std::cout << "Waiting for quad to catch up";
  // Delay for quad to catch up
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));

  //////////////////////////////////////////////////////////////////
  // Swoop second part
  // Define the trajectory starting state:
  pos0 = Vec3(parameters::x_mid, parameters::y_mid,
              parameters::z_mid);              // position
  vel0 = Vec3(parameters::mid_velocity, 0, 0); // velocity
  acc0 = Vec3(0, 0, 0);                        // acceleration

  // define the goal state:
  posf = Vec3(parameters::x_final, parameters::y_final,
              parameters::z_final);            // position
  velf = Vec3(parameters::mid_velocity, 0, 0); // velocity
  accf = Vec3(0, 0, 0);

  // Generate trajectory
  traj.SetGoalPosition(posf);
  traj.SetGoalVelocity(velf);
  traj.SetGoalAcceleration(accf);
  traj.Generate(Tf);

  for (double i = 0; i < Tf; i += parameters::dt) {
    // Set position
    pos_cmd.position.x = traj.GetPosition(i).x;
    pos_cmd.position.y = traj.GetPosition(i).y;
    pos_cmd.position.z = traj.GetPosition(i).z;

    std::cout << "Timestep:" << i << std::endl;
    std::cout << "Position:" << '\t' << traj.GetPosition(i).x << '\t'
              << traj.GetPosition(i).y << '\t' << traj.GetPosition(i).z
              << std::endl;

    // Publish command
    position_pub.publish(pos_cmd);

    // Delay for quad to catch up
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));
  }
}
