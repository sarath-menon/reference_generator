#pragma once
#include "parameters_list.h"
#include "safety_checks.h"
#include <yaml-cpp/yaml.h>

inline void set_circle_parameters(const std::string setpoint_path) {
  // Safety check, see if file exists
  safety_checks::yaml_file_check(setpoint_path);

  // Load yaml file containing gains
  YAML::Node circle_yaml = YAML::LoadFile(setpoint_path);

  // load parameters
  prm::step_size = circle_yaml["step_size"].as<float>();
  prm::radius = circle_yaml["radius"].as<float>();

  prm::center_x = circle_yaml["center_x"].as<float>();
  prm::center_y = circle_yaml["center_y"].as<float>();

  prm::altitude = circle_yaml["altitude"].as<float>();
}