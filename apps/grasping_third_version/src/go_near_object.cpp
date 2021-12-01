#include "grasper.h"

bool Grasper::go_near_object(const float x_ref, const float y_ref,
                             const float z_ref, const float time,
                             const bool pos_flag, std::string target) {
  // time counter
  float t_counter{};
  while (t_counter < time) {
    t_counter += dt_;

    //  Delay for quad to catch up
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_time_));

    // offset due to position interface
    constexpr static float x_offset = 0.5;
    constexpr static float y_offset = 0.5;
    bool x_reach_flag;
    bool y_reach_flag;
    bool z_reach_flag;
    float x_target;
    float y_target;
    float z_target;

    // // Check whether position reached
    std::cout << "quad pose:" << quad_pose_.pose.position.x << '\t'
              << quad_pose_.pose.position.y << '\t'
              << quad_pose_.pose.position.z << std::endl;
    if (target == "stand") {
      // cout for debugging
      std::cout << "stand pose:" << stand_pose_.pose.position.x << '\t'
                << stand_pose_.pose.position.y << '\t'
                << stand_pose_.pose.position.z << std::endl;

      // set flags
      x_reach_flag =
          check_reached(quad_pose_.pose.position.x,
                        stand_pose_.pose.position.x + x_ref, xy_threshold_);
      // * (-1.0) because of different coordinates
      // (mocap_pose and setpoint)
      y_reach_flag =
          check_reached(quad_pose_.pose.position.y,
                        stand_pose_.pose.position.y + y_ref, xy_threshold_);

      z_reach_flag =
          check_reached(quad_pose_.pose.position.z,
                        stand_pose_.pose.position.z + z_ref, z_threshold_);

      // set target positions

      x_target = stand_pose_.pose.position.x;
      y_target = stand_pose_.pose.position.y;
      z_target = stand_pose_.pose.position.z;

    } else if (target == "box") {
      // cout for debugging
      std::cout << "box pose:" << object_pose_.pose.position.x << '\t'
                << object_pose_.pose.position.y << '\t'
                << object_pose_.pose.position.z << std::endl;

      // set flags
      x_reach_flag =
          check_reached(quad_pose_.pose.position.x,
                        object_pose_.pose.position.x + x_ref, xy_threshold_);
      // * (-1.0) because of different coordinates
      // (mocap_pose and setpoint)
      y_reach_flag =
          check_reached(quad_pose_.pose.position.y,
                        object_pose_.pose.position.y + y_ref, xy_threshold_);

      z_reach_flag =
          check_reached(quad_pose_.pose.position.z,
                        object_pose_.pose.position.z + z_ref, z_threshold_);
      // set target positions

      x_target = object_pose_.pose.position.x;
      y_target = object_pose_.pose.position.y;
      z_target = object_pose_.pose.position.z;

    } else {
      std::cout << "invalid object" << std::endl;
      return false;
    }

    // exit if position has been reached
    if (pos_flag && x_reach_flag && y_reach_flag && z_reach_flag == true) {
      std::cout << "Target position has been reached" << std::endl;
      return true;
      break;
    }

    // Send positon cmd if positon not reached
    else {
      // Set pos cmd
      quad_pos_cmd.position.x = (x_target + x_ref) - x_offset;
      quad_pos_cmd.position.y = -(y_target + y_ref) - y_offset;
      quad_pos_cmd.position.z = z_target + z_ref;

      // std::cout << "Setpoint: " <<
      // setpoint(index).x << '\t'
      //          << setpoint(index).y << '\t' <<
      //          setpoint(index).z << std::endl;
      position_pub->publish(quad_pos_cmd);
    }
  }
  // If we reach here, then target coudln't be reached in specified time
  std::cerr << "Setpoint couldn't be reached in given time limit" << std::endl;
  return false;
}
