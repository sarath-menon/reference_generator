#include "grasper.h"

/// Setter function
bool Grasper::go_to_pos(const int index, const bool pos_flag) {
  // time counter
  float t_counter{};
  std::cout << "Setpoint: " << setpoint(index).x << '\t' << setpoint(index).y
            << '\t' << setpoint(index).z << std::endl;

  while (t_counter < max_reach_time_.at(index)) {
    t_counter += dt_;

    //  Delay for quad to catch up
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_time_));

    x_reach_flag = check_reached(quad_pose_.pose.position.x, setpoint(index).x,
                                 xy_threshold_);
    // * (-1.0) because of different coordinates (mocap_pose and setpoint)
    y_reach_flag = check_reached(quad_pose_.pose.position.y, setpoint(index).y,
                                 xy_threshold_);
    z_reach_flag = check_reached(quad_pose_.pose.position.z, setpoint(index).z,
                                 z_threshold_);

    // std::cout << "Reached flags: " << x_reach_flag << '\t' << y_reach_flag
    //           << '\t' << z_reach_flag << std::endl;

    // exit if position has been reached
    if (pos_flag && x_reach_flag && y_reach_flag && z_reach_flag == true) {
      std::cout << "Target position has been reached" << std::endl;
      return true;
      break;
    }

    // Send positon cmd if positon not reached
    else {
      // Set pos cmd
      quad_pos_cmd.position.x = setpoint(index).x;
      quad_pos_cmd.position.y = setpoint(index).y;
      quad_pos_cmd.position.z = setpoint(index).z;

      // std::cout << "Setpoint: " << setpoint(index).x << '\t'
      //          << setpoint(index).y << '\t' << setpoint(index).z <<
      //          std::endl;

      position_pub->publish(quad_pos_cmd);
    }
  }

  // If we reach here, then target coudln't be reached in specified time
  std::cerr << "Setpoint couldn't be reached in given time limit" << std::endl;
  return false;
}

/// overloaded function to also accept xyz values
bool Grasper::go_to_pos(const float x_ref, const float y_ref, const float z_ref,
                        const float time, const bool pos_flag) {
  // time counter
  float t_counter{};
  std::cout << "Setpoint: " << x_ref << '\t' << y_ref << '\t' << z_ref
            << std::endl;

  while (t_counter < time) {
    t_counter += dt_;

    //  Delay for quad to catch up
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_time_));

    x_reach_flag =
        check_reached(quad_pose_.pose.position.x, x_ref, xy_threshold_);
    // * (-1.0) because of different coordinates (mocap_pose and setpoint)
    y_reach_flag =
        check_reached(quad_pose_.pose.position.y, y_ref, xy_threshold_);
    z_reach_flag =
        check_reached(quad_pose_.pose.position.z, z_ref, z_threshold_);

    // std::cout << "Reached flags: " << x_reach_flag << '\t' << y_reach_flag
    //           << '\t' << z_reach_flag << std::endl;

    // exit if position has been reached
    if (pos_flag && x_reach_flag && y_reach_flag && z_reach_flag == true) {
      std::cout << "Target position has been reached" << std::endl;
      return true;
      break;
    }

    // Send positon cmd if positon not reached
    else {
      // Set pos cmd
      quad_pos_cmd.position.x = x_ref;
      quad_pos_cmd.position.y = y_ref;
      quad_pos_cmd.position.z = z_ref;

      // std::cout << "Setpoint: " << x << '\t'
      //          << y << '\t' << z <<
      //          std::endl;

      position_pub->publish(quad_pos_cmd);
    }
  }

  // If we reach here, then target coudln't be reached in specified time
  std::cerr << "Setpoint couldn't be reached in given time limit" << std::endl;
  return false;
}

bool Grasper::go_to_pos_minJerk(const Vec3 pos_init, const Vec3 vel_init,
                                const Vec3 acc_init, const Vec3 pos_fin,
                                const Vec3 vel_fin, const Vec3 acc_fin,
                                const Vec3 g, const float completion_time) {
  // Create trajectory generator
  // RapidTrajectoryGenerator traj(pos_init, vel_init, acc_init, g);
  RapidQuadrocopterTrajectoryGenerator::RapidTrajectoryGenerator traj(
      pos_init, vel_init, acc_init, g);

  // Generate trajectory
  traj.SetGoalPosition(pos_fin);
  traj.SetGoalVelocity(vel_fin);
  traj.SetGoalAcceleration(acc_fin);
  traj.Generate(completion_time);  // completion time

  for (double i = 0; i < completion_time; i += dt_) {
    // Set position
    quad_pos_cmd.position.x = traj.GetPosition(i).x;
    quad_pos_cmd.position.y = traj.GetPosition(i).y;
    quad_pos_cmd.position.z = traj.GetPosition(i).z;

    // DEBUG
    std::cout << "Timestep:" << i << std::endl;
    std::cout << "Position_cmd:" << '\t' << traj.GetPosition(i).x << '\t'
              << traj.GetPosition(i).y << '\t' << traj.GetPosition(i).z
              << std::endl;
    std::cout << "Position_quad:" << '\t' << quad_pose_.pose.position.x << '\t'
              << quad_pose_.pose.position.y << '\t'
              << quad_pose_.pose.position.z << std::endl;

    // Publish command
    position_pub->publish(quad_pos_cmd);

    // Delay for quad to catch up
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_time_));
  }

  bool x_reach_flag =
      check_reached(quad_pose_.pose.position.x, pos_fin[0], xy_threshold_);
  bool y_reach_flag =
      check_reached(quad_pose_.pose.position.y, pos_fin[1], xy_threshold_);

  if (x_reach_flag && y_reach_flag) {
    std::cout << "Target position reached (minJerk): " << std::endl;
    std::cout << "Timesteps: " << completion_time << std::endl
              << "Target Position: " << '\t'
              << traj.GetPosition(completion_time).x << '\t'
              << traj.GetPosition(completion_time).y << '\t'
              << traj.GetPosition(completion_time).z << std::endl;
    return true;
  } else {
    std::cout << "Target position wasn't reached (minJerk)" << std::endl;
    // manually set position cmd to pos_fin
    quad_pos_cmd.position.x = pos_fin[0];
    quad_pos_cmd.position.y = pos_fin[1];
    quad_pos_cmd.position.z = pos_fin[2];

    return false;
  }
}