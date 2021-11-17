
#include "grasper.h"
#include "safety_checks.h"
#include <string>
#include <yaml-cpp/yaml.h>

void Grasper::set_parameters(const std::string path) {
  // Safety check, see if file exists
  safety_checks::yaml_file_check(path);

  // Load yaml file containing gains
  YAML::Node setpoint_yaml = YAML::LoadFile(path);

  // Set setpoints
  dt_ = setpoint_yaml["dt"].as<float>();
  delay_time_ = (int)dt_ * 1000;

  xy_threshold_ = setpoint_yaml["xy_threshold"].as<float>();
  z_threshold_ = setpoint_yaml["z_threshold"].as<float>();

  grasping_time_ = setpoint_yaml["grasping_time"].as<float>(); // [constant]

  // Set target setpoints
}

void Grasper::set_setpoints(const std::string path) {

  // Safety check, see if file exists
  safety_checks::yaml_file_check(path);

  // Load yaml file containing gains
  YAML::Node setpoint_yaml = YAML::LoadFile(path);

  desired_pos_.x = setpoint_yaml["x_desired"].as<float>(); // [constant]
  desired_pos_.y = setpoint_yaml["y_desired"].as<float>(); // [constant]
  desired_pos_.z = setpoint_yaml["z_desired"].as<float>(); // [constant]
}