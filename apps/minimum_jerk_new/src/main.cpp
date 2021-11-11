#include "include_helper.h"

// Define how gravity lies in our coordinate system
Vec3 gravity = Vec3(0, 0, -9.81); //[m/s**2]
// Define the state constraints. We'll only check that we don't fly into the
// floor:
Vec3 floorPos = Vec3(0, 0, 0); // any point on the boundary
Vec3 floorNormal =
    Vec3(0, 0, 1); // we want to be in this direction of the boundary

// Initial, Final velocity, acceleration zero for all states
Vec3 vel0 = Vec3(0, 0, 0);           // velocity
Vec3 acc0 = Vec3(0, 0, 0);
Vec3 velf = Vec3(0, 0, 0);           // velocity
Vec3 accf = Vec3(0, 0, 0);

int main() {

  // Set parameters
  set_parameters(paths::setpoint_path);

  // seconds to milliseconds
  const int delay_time = parameters::dt * 1000;

  // Quadcopter position msg
  cpp_msg::QuadPositionCmd pos_cmd{};

  // Create participant. Arguments-> Domain id, QOS name
  DefaultParticipant dp(0, "quad_reference_publisher");

  // Create publisher with msg type
  DDSPublisher position_pub(idl_msg::QuadPositionCmdPubSubType(), "pos_cmd",
                            dp.participant());

  // Create mocap subscriber
  DDSSubscriber mocap_sub(idl_msg::MocapPubSubType(), &sub::mocap_msg,
                          "mocap_pose", dp.participant());

  mocap_sub.init();

  // Initialize publisher
  position_pub.init();

  // Set start position
  pos_cmd.position.x = parameters::x_start;
  pos_cmd.position.y = parameters::y_start;
  pos_cmd.position.z = parameters::z_start;

  // Publish command
  position_pub.publish(pos_cmd);

  // Delay for quad to catch up
  std::this_thread::sleep_for(std::chrono::seconds(5));
  std::cout << "Starting swooping";

  // First part of swoop

  // Define the trajectory starting state:
  Vec3 pos0 = Vec3(sub::mocap_msg.pose.position.x,
                sub::mocap_msg.pose.position.y,
                sub::mocap_msg.pose.position.z); // position

  // define the goal state:
  Vec3 posf = Vec3(parameters::x_mid, parameters::y_mid,
                   parameters::z_mid); // position

// Create trajectory generator
  RapidTrajectoryGenerator traj_1(pos0, vel0, acc0, gravity);

  // Generate trajectory
  traj_1.SetGoalPosition(posf);
  traj_1.SetGoalVelocity(velf);
  traj_1.SetGoalAcceleration(accf);
  traj_1.Generate(parameters::completion_time);

  for (double i = 0; i < 50; i += parameters::dt) {
    // Set position
    pos_cmd.position.x = traj_1.GetPosition(i).x;
    pos_cmd.position.y = traj_1.GetPosition(i).y;
    pos_cmd.position.z = traj_1.GetPosition(i).z;

    // std::cout << "Timestep:" << i << std::endl;
    // std::cout << "Position:" << '\t' << traj.GetPosition(i).x << '\t'
    //           << traj.GetPosition(i).y << '\t' << traj.GetPosition(i).z
    //           << std::endl;

    // Publish command
    position_pub.publish(pos_cmd);

    // Delay for quad to catch up
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));
  }

  // Delay for quad to catch up
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  //////////////////////////////////////////////////////////////////
  // Swoop second part

  // Define the trajectory starting state:
    pos0 = Vec3(sub::mocap_msg.pose.position.x,
                sub::mocap_msg.pose.position.y,
                sub::mocap_msg.pose.position.z); // position


  // define the goal state:
    posf = Vec3(parameters::x_final, parameters::y_final,
              parameters::z_final); // position

    // Set parameters
    RapidTrajectoryGenerator traj_2(pos0, vel0, acc0, gravity);
    traj_2.SetGoalPosition(posf);
    traj_2.SetGoalVelocity(velf);
    traj_2.SetGoalAcceleration(accf);

      // Generate trajectory
    traj_2.Generate(parameters::completion_time);
  
  for (int i = 0; i < 50; i ++) {

  // Set position command
   pos_cmd.position.x = traj_2.GetPosition(parameters::dt).x;
   pos_cmd.position.y = traj_2.GetPosition(parameters::dt).y;
   pos_cmd.position.z = traj_2.GetPosition(parameters::dt).z;

    // std::cout << "Timestep:" << i << std::endl;
    // std::cout << "Position:" << '\t' << traj.GetPosition(i).x << '\t'
    //           << traj.GetPosition(i).y << '\t' <<
    // traj.GetPosition(i).z
    //           << std::endl;

    // Publish command
    position_pub.publish(pos_cmd);
 
    // Delay for quad to catch up
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));
    // std::cout << std::endl;
  }
}
