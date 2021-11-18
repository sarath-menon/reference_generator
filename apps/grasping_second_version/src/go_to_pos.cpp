#include "grasper.h"

/// Setter function
bool Grasper::go_to_pos(const int index) {

  // time counter
  float t_counter{};
  std::cout << "Setpoint: " << setpoint(index).x << '\t' << setpoint(index).y
            << '\t' << setpoint(index).z << std::endl;

  while (t_counter < max_reach_time_.at(index)) {

    t_counter += dt_;

    //  Delay for quad to catch up
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_time_));

    // offset due to position interface
    constexpr static float x_offset = 0.5;
    constexpr static float y_offset = 0.5;

    x_reach_flag = check_reached(quad_pose_.pose.position.x,
                                 setpoint(index).x + x_offset, xy_threshold_);
    // * (-1.0) because of different coordinates (mocap_pose and setpoint)
    y_reach_flag =
        check_reached(quad_pose_.pose.position.y,
                      (setpoint(index).y + y_offset) * (-1.0), xy_threshold_);
    z_reach_flag = check_reached(quad_pose_.pose.position.z, setpoint(index).z,
                                 z_threshold_);

    // std::cout << "Reached flags: " << x_reach_flag << '\t' << y_reach_flag
    //           << '\t' << z_reach_flag << std::endl;

    // exit if position has been reached
    if (x_reach_flag && y_reach_flag && z_reach_flag == true) {
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
