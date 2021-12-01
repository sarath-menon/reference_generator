
#include "grasper.h"
#include "safety_checks.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

// to set parameters from yaml file
void Grasper::set_parameters(const std::string path) {
  // Safety check, see if file exists
  //std::cout<<"iam here";
  safety_checks::yaml_file_check(path);

  // Load yaml file containing gains
  YAML::Node parameters_yaml = YAML::LoadFile(path);

  // set time parameters
  dt_ = parameters_yaml["dt"].as<float>();
  delay_time_ = parameters_yaml["delay_time"].as<int>();

  startPoint_completion_time_ = 
    parameters_yaml["startPoint_completion_time"].as<float>();
  startPoint_wait_swoop_ = 
    parameters_yaml["startPoint_wait_swoop"].as<int>();
  
  swoop_completion_time_ = 
    parameters_yaml["swoop_completion_time"].as<float>();
  swoop_wait_mid_ = 
    parameters_yaml["swoop_wait_mid"].as<int>();

  // set thresholds
  xy_threshold_ = parameters_yaml["xy_threshold"].as<float>();
  z_threshold_ = parameters_yaml["z_threshold"].as<float>();

  // set object name
  object_name_ = parameters_yaml["object_name"].as<std::string>();
  quad_name_ = parameters_yaml["quad_name"].as<std::string>();
  topic_prefix_ = parameters_yaml["topic_prefix"].as<std::string>();
}

// to load waypoints from csv file
void Grasper::load_setpoints(const std::string path) {
  // Safety check, see if file exists
  safety_checks::yaml_file_check(path);

  // create ofstream to read
  std::ifstream csv_file(path);

  // check if the file is open
  if (!csv_file.is_open())
    throw std::runtime_error("Could not open file");

  // to load line from csv
  std::string line;

  while (getline(csv_file, line)) {
    std::stringstream s_stream(line);

    for (int i = 0; i < 4; i++) {
      if (s_stream.good()) {
        std::string substr;
        // get succssive substring seperated by comma
        getline(s_stream, substr, ',');

        switch (i) {
        case 0:
          x_setpoint_.push_back(std::stof(substr));
          break;
        case 1:
          y_setpoint_.push_back(std::stof(substr));
          break;
        case 2:
          z_setpoint_.push_back(std::stof(substr));
          break;
        case 3:
          max_reach_time_.push_back(std::stof(substr));
          break;
        }
      }
    }
  }

  // for (int i = 0; i < 4; i++) {
  //   std::cout << "Waypoint: " << i << ": (" << x_setpoint_.at(i) << ","
  //             << y_setpoint_.at(i) << "," << z_setpoint_.at(i)
  //             << ") time:" << max_reach_time_.at(i) << std::endl;
  // }

  csv_file.close();
}
