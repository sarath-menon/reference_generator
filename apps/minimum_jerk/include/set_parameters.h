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
  params::x_start = setpoint_yaml["x_start"].as<float>();
  params::y_start = setpoint_yaml["y_start"].as<float>();
  params::z_start = setpoint_yaml["z_start"].as<float>();

  // Set end
  params::x_mid = setpoint_yaml["x_mid"].as<float>();
  params::y_mid = setpoint_yaml["y_mid"].as<float>();
  params::z_mid = setpoint_yaml["z_mid"].as<float>();

  // Set end
  params::x_final = setpoint_yaml["x_final"].as<float>();
  params::y_final = setpoint_yaml["y_final"].as<float>();
  params::z_final = setpoint_yaml["z_final"].as<float>();

  params::mid_velocity = setpoint_yaml["mid_velocity"].as<float>();

  // Set dt
  params::dt = setpoint_yaml["dt"].as<float>(); // [constant]

  // Define how gravity lies in our coordinate system
  Vec3 gravity = Vec3(0, 0, -9.81); //[m/s**2]

  // maneuuver duration
  params::duration = 1.0;
}
