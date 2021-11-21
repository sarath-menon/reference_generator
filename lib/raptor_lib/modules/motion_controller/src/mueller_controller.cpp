#include "motion_controller.h"
#include "mueller_helper.h"
#include <stdlib.h>

/// go to target position  with max time limit as reaching thresholds
cpp_msg::Position
MotionCtrl::muller_controller(const cpp_msg::Position &current_pos,
                              const cpp_msg::Position &target_pos,
                              const float max_time, const float dt) {

  // Define how gravity lies in our coordinate system
  static Vec3 gravity = Vec3(0, 0, -9.81); //[m/s**2]

  // Duration
  static float duration = 1.5;

  // Initial and final accelerations always zero for now
  static Vec3 vel0 = Vec3(0, 0, 0); // intiail velocity
  static Vec3 acc0 = Vec3(0, 0, 0); // intial acceleration
  static Vec3 velf = Vec3(0, 0, 0); // final velocity
  static Vec3 accf = Vec3(0, 0, 0); // final acceleration

  // Define the trajectory starting state
  Vec3 pos0 = Vec3(current_pos.x, current_pos.y,
                   current_pos.z); // position

  // define the goal state:
  Vec3 posf = Vec3(target_pos.x, target_pos.y,
                   target_pos.z); // position

  // Generate trajectory
  RapidTrajectoryGenerator traj(pos0, vel0, acc0, gravity);
  traj.SetGoalPosition(posf);
  traj.SetGoalVelocity(velf);
  traj.SetGoalAcceleration(accf);
  traj.Generate(duration);

  // set target position
  static cpp_msg::Position pos_setpoint{};

  pos_setpoint.x = traj.GetPosition(dt).x;
  pos_setpoint.y = traj.GetPosition(dt).y;
  pos_setpoint.z = traj.GetPosition(dt).z;

  // for (float i = 0.0; i < 1.5; i += 0.02) {
  //   std::cout << "Mueller setpoint:" << '\t' << traj.GetPosition(i).x << '\t'
  //             << traj.GetPosition(i).y << '\t' << traj.GetPosition(i).z
  //             << std::endl;
  // }

  // if this line reached, then target coudln't be reached in given time
  return pos_setpoint;
}
