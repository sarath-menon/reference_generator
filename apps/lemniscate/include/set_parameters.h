#pragma once
#include "parameters_list.h"
#include "safety_checks.h"
#include <yaml-cpp/yaml.h>

inline void set_parameters(const std::string setpoint_path) {
  // Safety check, see if file exists
  safety_checks::yaml_file_check(setpoint_path);

  // Load yaml file containing gains
  YAML::Node param_yaml = YAML::LoadFile(setpoint_path);

  // load parameters
  prm::a = param_yaml["a"].as<float>();

  prm::omega = param_yaml["omega"].as<float>();

  prm::center_x = param_yaml["center_x"].as<float>();
  prm::center_y = param_yaml["center_y"].as<float>();

  prm::altitude = param_yaml["altitude"].as<float>();
}