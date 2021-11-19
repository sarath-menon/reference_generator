#include "grasper.h"

bool Grasper::departure(const float z_ref, const float time, const bool pos_flag) {

  // Compensate for positon offset
  //object_pose_.pose.position.x += x_ref;
  //object_pose_.pose.position.y += y_ref;
  //object_pose_.pose.position.z += z_ref;
  const float x_pickup = object_pose_.pose.position.x;
  const float y_pickup = object_pose_.pose.position.y;
  //object_pose_.pose.position.y *= -1.0;

  // time counter
  float t_counter{};
  while (t_counter < time) {

    t_counter += dt_;

    //  Delay for quad to catch up
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_time_));

    // offset due to position interface
    constexpr static float x_offset = 0.5;
    constexpr static float y_offset = 0.5;

    // // Check whether position reached
    // std::cout << "quad pose:" << quad_pose_.pose.position.x << '\t'
    //           << quad_pose_.pose.position.y << '\t'
    //           << quad_pose_.pose.position.z << std::endl;
    // std::cout << "object pose:" << object_pose_.pose.position.x << '\t'
    //           << object_pose_.pose.position.y << '\t'
    //           << object_pose_.pose.position.z << std::endl;

    x_reach_flag = check_reached(quad_pose_.pose.position.x,
                                 x_pickup, xy_threshold_);
    // * (-1.0) because of different coordinates
    // (mocap_pose and setpoint)
    y_reach_flag =
        check_reached(quad_pose_.pose.position.y,
                      y_pickup, xy_threshold_);

    z_reach_flag = check_reached(quad_pose_.pose.position.z,
                                 z_ref, z_threshold_);

    // exit if position has been reached
    if (pos_flag && x_reach_flag && y_reach_flag && z_reach_flag == true) {
      std::cout << "Target position has been reached" << std::endl;
      return true;
      break;
    }

    // Send positon cmd if positon not reached
    else {

      // Set pos cmd
      quad_pos_cmd.position.x = (x_pickup) - x_offset;
      quad_pos_cmd.position.y = -(y_pickup) - y_offset;
      quad_pos_cmd.position.z = z_ref;

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
