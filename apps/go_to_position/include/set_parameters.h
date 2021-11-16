#pragma once
#include "parameters_list.h"
#include "safety_checks.h"
#include <string>
#include <yaml-cpp/yaml.h>

inline void set_parameters(const std::string setpoint_path) {
  // Safety check, see if file exists
  safety_checks::yaml_file_check(setpoint_path);

  // Load yaml file containing gains
  YAML::Node setpoint_yaml = YAML::LoadFile(setpoint_path);

  // Set setpoints
  parameters::x_position = setpoint_yaml["x_position"].as<float>();
  parameters::y_position = setpoint_yaml["y_position"].as<float>();
  parameters::z_position = setpoint_yaml["z_position"].as<float>();

  // Set dt
  parameters::dt = setpoint_yaml["dt"].as<float>(); // [constant]
}