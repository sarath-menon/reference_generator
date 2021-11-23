#include "grasper.h"

/// go to target position  with max time limit as reaching thresholds
bool Grasper::go_to_pos(const cpp_msg::Position &current_pos,
                        const cpp_msg::Position &target_pos,
                        const cpp_msg::Position &pos_thresholds,
                        const float max_time, const ctrl_type type) {

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
      switch (type) {

      case ctrl_type::px4:
        quad_pos_cmd.position = target_pos;
        break;

      case ctrl_type::mueller:
        quad_pos_cmd.position =
            muller_controller(current_pos, target_pos, max_time, dt_);
        break;

      default:
        exit(0);
      }

      // // Publish pos cmd
      position_pub->publish(quad_pos_cmd);

      //  Delay for quad to catch up
      std::this_thread::sleep_for(std::chrono::milliseconds(delay_time_));

      // std::cout << "time:" << t_counter << std::endl;

      // Logging to console for debugging
      //////////////////////////////////////////////////////////////////////////////////////
      // Check whether position reached
      // std::cout << "quad pose:" << current_pos.x << '\t' << current_pos.y
      //           << '\t' << current_pos.z << std::endl;

      // std::cout << "quad cmd:" << quad_pos_cmd.position.x << '\t'
      //           << quad_pos_cmd.position.y << '\t' << quad_pos_cmd.position.z
      //           << std::endl;

      // std::cout << "pos setpoint:" << target_pos.x << '\t' << target_pos.y
      //           << '\t' << target_pos.z << std::endl;

      // std::cout << std::endl;
    }
  }

  // if this line reached, then target coudln't be reached in given time
  std::cerr << "Setpoint couldn't be reached in time. Please check setup"
            << std::endl;

  return false;
}
