#include "grasper.h"

/// go to target position  with max time limit as reaching thresholds
bool Grasper::go_to_pos(const cpp_msg::Position &current_pos,
                        const cpp_msg::Position &target_pos,
                        const cpp_msg::Position &pos_thresholds,
                        const float max_time) {

  // initialize time counter
  float t_counter{};

  while (t_counter < max_time) {

    // incrment time cointer
    t_counter += dt_;

    x_reach_flag = check_reached(current_pos.x, target_pos.x, pos_thresholds.x);
    y_reach_flag = check_reached(current_pos.y, target_pos.y, pos_thresholds.y);
    z_reach_flag = check_reached(current_pos.z, target_pos.z, pos_thresholds.z);

    // std::cout << "Reached flags: " << x_reach_flag << '\t' << y_reach_flag
    //           << '\t' << z_reach_flag << std::endl;

    // exit if position has been reached
    if (x_reach_flag && y_reach_flag && z_reach_flag == true) {
      std::cout << "Target position has been reached" << std::endl;
      return true;
      break;
    }

    // Send positon cmd if position not reached
    else {
      // Set pos cmd
      quad_pos_cmd.position.x = target_pos.x;
      quad_pos_cmd.position.y = target_pos.y;
      quad_pos_cmd.position.z = target_pos.z;

      // position_pub->publish(quad_pos_cmd);

      //  Delay for quad to catch up
      std::this_thread::sleep_for(std::chrono::milliseconds(delay_time_));

      std::cout << "Setpoint: " << target_pos.x << '\t' << target_pos.y << '\t'
                << target_pos.z << std::endl;
    }
  }

  // if this line reached, then target coudln't be reached in given time
  return false;
}
