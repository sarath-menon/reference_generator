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
bool Grasper::set_desired_pos(const cpp_msg::Position desired_pos) {
  desired_pos_ = desired_pos;

  // time counter
  float t_counter{};

  while (t_counter < grasping_time_) {

    t_counter += dt_;

    //  Delay for quad to catch up
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_time_));

    // Check whether position reached

    x_reach_flag = check_reached(current_pose_.pose.position.x, desired_pos_.x,
                                 xy_threshold_);
    y_reach_flag = check_reached(current_pose_.pose.position.y, desired_pos_.y,
                                 xy_threshold_);
    z_reach_flag = check_reached(current_pose_.pose.position.z, desired_pos_.z,
                                 z_threshold_);

    // exit if position has been reached
    if (x_reach_flag && x_reach_flag && x_reach_flag == true) {
      std::cout << "Target position has been reached";
      return true;
      break;
    }
  }

  // If we reach here, then target coudln't be reached in specified time
  std::cerr << "Target coudln't be reached in specified time";
  return false;
}
