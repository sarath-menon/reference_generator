
#include "go_over_object.h"
#include "safety_checks.h"
#include <string>
#include <yaml-cpp/yaml.h>

// to set parameters from yaml file
void GoOverObject::set_parameters(const std::string path) {
  // Safety check, see if file exists
  safety_checks::yaml_file_check(path);

  // Load yaml file containing gains
  YAML::Node param_yaml = YAML::LoadFile(path);

  // Set waypoints
  dt_ = param_yaml["dt"].as<float>();
  delay_time_ = int(dt_ * 1000);
}
