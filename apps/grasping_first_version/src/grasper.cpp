#include "grasper.h"

bool check_reached(const float &current_pos, const float &desired_pos,
                   const float &threshold) {
  // Compute position difference
  float pos_diff = abs(current_pos - desired_pos);

  if (pos_diff <= threshold) {
    return true;
  } else {
    return false;
  }
}

Grasper::Grasper() {
  // Fastdds ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`

  // Create domain participant
  dp = std::make_unique<DefaultParticipant>(0, "grasper");

  // Create  subscriber
  mocap_sub = new DDSSubscriber(idl_msg::MocapPubSubType(), &current_pose_,
                                "mocap_pose", dp->participant());

  // initialize  subscriberDefaultParticipant
  mocap_sub->init();

  // Create position cmd publisher
  position_pub = new DDSPublisher(idl_msg::QuadPositionCmdPubSubType(),
                                  "pos_cmd", dp->participant());

  // Initialize position publisher
  position_pub->init();
}

Grasper::~Grasper() {
  delete mocap_sub;
  delete position_pub;
}

/// Setter function
bool Grasper::go_to_pos(const int index) {

  // time counter
  float t_counter{};

  while (t_counter < max_reach_time_.at(index)) {

    t_counter += dt_;

    //  Delay for quad to catch up
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_time_));

    // // Check whether position reached
    // std::cout << "Current pose:" << current_pose_.pose.position.x << '\t'
    //           << current_pose_.pose.position.y << '\t'
    //           << current_pose_.pose.position.z << std::endl;

    x_reach_flag = check_reached(current_pose_.pose.position.x,
                                 setpoint(index).x, xy_threshold_);
    y_reach_flag = check_reached(current_pose_.pose.position.y,
                                 setpoint(index).y, xy_threshold_);
    z_reach_flag = check_reached(current_pose_.pose.position.z,
                                 setpoint(index).z, z_threshold_);

    // std::cout << "Reached flags: " << x_reach_flag << '\t' << y_reach_flag
    //           << '\t' << z_reach_flag << std::endl;

    // exit if position has been reached
    if (x_reach_flag && y_reach_flag && z_reach_flag == true) {
      std::cout << "Target position has been reached";
      return true;
      break;
    }

    // Send positon cmd if positon not reached
    else {
      // Set pos cmd
      quad_pos_cmd.position.x = setpoint(index).x;
      quad_pos_cmd.position.y = setpoint(index).y;
      quad_pos_cmd.position.z = setpoint(index).z;

      std::cout << "Setpoint: " << setpoint(index).x << '\t'
                << setpoint(index).y << '\t' << setpoint(index).z << std::endl;

      // position_pub->publish(quad_pos_cmd);
    }
  }

  // If we reach here, then target coudln't be reached in specified time
  std::cerr << "Setpoint couldn't be reached in given time limit";
  return false;
}
