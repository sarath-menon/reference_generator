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
double Tf = 2.0;

double f_min = 5;         //[m/s**2]
double f_max = 25;        //[m/s**2]
double wmax = 20;         //[rad/s]
double minTimeSec = 0.02; //[s]

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
  RapidTrajectoryGenerator traj_1(pos0, vel0, acc0, gravity);

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
  traj_1.SetGoalPosition(posf);
  traj_1.SetGoalVelocity(velf);
  traj_1.SetGoalAcceleration(accf);
  traj_1.Generate(Tf);

  // Set position
  pos_cmd.position.x = parameters::x_start;
  pos_cmd.position.y = parameters::y_start;
  pos_cmd.position.z = parameters::z_start;

  // Publish command
  position_pub.publish(pos_cmd);

  // Delay for quad to catch up
  std::this_thread::sleep_for(std::chrono::seconds(5));

  std::cout << "Starting swooping";

  for (double i = 0; i < Tf; i += parameters::dt) {
    // Set position
    pos_cmd.position.x = traj_1.GetPosition(i).x;
    pos_cmd.position.y = traj_1.GetPosition(i).y;
    pos_cmd.position.z = traj_1.GetPosition(i).z;

    // std::cout << "Timestep:" << i << std::endl;
    // std::cout << "Position:" << '\t' << traj_1.GetPosition(i).x << '\t'
    //           << traj_1.GetPosition(i).y << '\t' << traj_1.GetPosition(i).z
    //           << std::endl;

    // Publish command
    position_pub.publish(pos_cmd);

    // Delay for quad to catch up
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));
  }

  // for (double i = 0.7; i > 0.4; i -= 0.01) {

  //   pos_cmd.position.z = i;
  //   // Publish command
  //   position_pub.publish(pos_cmd);

  //   // Delay for quad to catch up
  //   std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));
  // }
  // std::cout << "Waiting for quad to catch up";
  // Delay for quad to catch up
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  //////////////////////////////////////////////////////////////////
  // Swoop second part
  // Define the trajectory starting state:
  pos0 = Vec3(parameters::x_mid, parameters::y_mid,
              parameters::z_mid); // position
  vel0 = Vec3(0, 0, 0);           // velocity
  acc0 = Vec3(0, 0, 0);           // acceleration

  // define the goal state:
  posf = Vec3(parameters::x_final, parameters::y_final,
              parameters::z_final); // position
  velf = Vec3(0, 0, 0);             // velocity
  accf = Vec3(0, 0, 0);

  // Generate trajectory
  RapidTrajectoryGenerator traj_2(pos0, vel0, acc0, gravity);

  // Generate traj_2ectory
  traj_2.SetGoalPosition(posf);
  traj_2.SetGoalVelocity(velf);
  traj_2.SetGoalAcceleration(accf);
  traj_2.Generate(Tf);

  for (double i = 0; i < Tf; i += parameters::dt) {
    // Set position
    pos_cmd.position.x = traj_2.GetPosition(i).x;
    pos_cmd.position.y = traj_2.GetPosition(i).y;
    pos_cmd.position.z = traj_2.GetPosition(i).z;

    // std::cout << "Timestep:" << i << std::endl;
    // std::cout << "Position:" << '\t' << traj_2.GetPosition(i).x << '\t'
    //           << traj_2.GetPosition(i).y << '\t' <<
    // traj_2.GetPosition(i).z
    //           << std::endl;

  // Publish command
  position_pub.publish(pos_cmd);

    // Delay for quad to catch up
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));
    // std::cout << std::endl;
  }
}
