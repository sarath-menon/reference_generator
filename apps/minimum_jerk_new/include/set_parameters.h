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

  // Set start
  parameters::x_start = setpoint_yaml["x_start"].as<float>();
  parameters::y_start = setpoint_yaml["y_start"].as<float>();
  parameters::z_start = setpoint_yaml["z_start"].as<float>();

  // Set end
  parameters::x_mid = setpoint_yaml["x_mid"].as<float>();
  parameters::y_mid = setpoint_yaml["y_mid"].as<float>();
  parameters::z_mid = setpoint_yaml["z_mid"].as<float>();

  // Set end
  parameters::x_final = setpoint_yaml["x_final"].as<float>();
  parameters::y_final = setpoint_yaml["y_final"].as<float>();
  parameters::z_final = setpoint_yaml["z_final"].as<float>();

  parameters::mid_velocity = setpoint_yaml["mid_velocity"].as<float>();

  // Set dt
  parameters::dt = setpoint_yaml["dt"].as<float>(); // [constant]
  parameters::completion_time = setpoint_yaml["completion_time"].as<float>(); // [constant]
  
}

inline void set_quad_parameters(const std::string quad_path) {

// Safety check, see if file exists
  safety_checks::yaml_file_check(quad_path);

  // Load yaml file containing gains
  YAML::Node quad_yaml = YAML::LoadFile(quad_path);

// Set quadcopter properties
  parameters::motor_thrust_max = quad_yaml["motor_thrust_max"].as<float>();
  parameters::motor_thrust_min = quad_yaml["motor_thrust_min"].as<float>();

  parameters::quad_thrust_max = parameters::motor_thrust_max*4;
  parameters::quad_thrust_min = parameters::motor_thrust_min*4;
}