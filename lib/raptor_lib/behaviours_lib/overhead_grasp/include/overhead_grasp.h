#pragma once
#include "behaviour.h"

class OverheadGrasp {
public:
  OverheadGrasp();
  ~OverheadGrasp();

private:
  // Quadcopter position
  cpp_msg::Mocap quad_pose_{};

  // Object position
  cpp_msg::QuadPositionCmd quad_pos_cmd{};

  // parameter
private:
  // controller sampling time in seconds
  float dt_{};

  // controller sampling time in milliseconds
  int delay_time_{};

public:
  /// Getter function
  const cpp_msg::Mocap &current_pose() const { return quad_pose_; }

  /// Getter function
  const float &dt() const { return dt_; }

public:
  enum class ctrl_type { px4, mueller };

public:
  bool go_to_waypoint(const int index, const ctrl_type type);
  bool go_to_waypoint(const cpp_msg::Position waypoint,
                      const float max_reach_time, const ctrl_type type);

  bool go_over_object(const std::string object, const float height,
                      const ctrl_type type);

  bool grasp_object(const std::string object, const ctrl_type type);

public:
  void set_parameters(const std::string path);
};
