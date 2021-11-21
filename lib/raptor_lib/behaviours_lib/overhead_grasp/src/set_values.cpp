
#include "overhead_grasp.h"
#include "safety_checks.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

// to set parameters from yaml file
void OverheadGrasp::set_parameters(const std::string path) {
  // Safety check, see if file exists
  safety_checks::yaml_file_check(path);

  // Load yaml file containing gains
  YAML::Node param_yaml = YAML::LoadFile(path);

  // // Set waypoints
  // dt_ = param_yaml["dt"].as<float>();
}
