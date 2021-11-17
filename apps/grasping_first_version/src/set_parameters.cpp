
#include "grasper.h"
#include "safety_checks.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

void Grasper::set_parameters(const std::string path) {
  // Safety check, see if file exists
  safety_checks::yaml_file_check(path);

  // Load yaml file containing gains
  YAML::Node setpoint_yaml = YAML::LoadFile(path);

  // Set setpoints
  dt_ = setpoint_yaml["dt"].as<float>();
  delay_time_ = int(dt_ * 1000);

  xy_threshold_ = setpoint_yaml["xy_threshold"].as<float>();
  z_threshold_ = setpoint_yaml["z_threshold"].as<float>();

  grasping_time_ = setpoint_yaml["grasping_time"].as<float>(); // [constant]

  // Set target setpoints
}

// void Grasper::set_setpoints(const std::string path) {

//   // Safety check, see if file exists
//   safety_checks::yaml_file_check(path);

//   // Load yaml file containing gains
//   YAML::Node setpoint_yaml = YAML::LoadFile(path);

//   desired_pos_.x = setpoint_yaml["x_desired"].as<float>(); // [constant]
//   desired_pos_.y = setpoint_yaml["y_desired"].as<float>(); // [constant]
//   desired_pos_.z = setpoint_yaml["z_desired"].as<float>(); // [constant]
// }

void Grasper::set_setpoints(const std::string path, const int index) {
  // Safety check, see if file exists
  safety_checks::yaml_file_check(path);

  // create ofstream to read
  std::ifstream csv_file(path);

  // check if the file is open
  if (!csv_file.is_open())
    throw std::runtime_error("Could not open file");

  // get line from file
  std::vector<float> x_ref;
  std::vector<float> y_ref;
  std::vector<float> z_ref;
  std::vector<float> time;
  std::vector<float> data;
  std::string line;

  while (getline(csv_file,line)) {
    std::stringstream s_stream(line);
    while (s_stream.good()) {
      std::string substr;
      getline(s_stream, substr, ','); // get first string delimited by comma
      std::cout << "Substr:" << substr<< std::endl;
      data.push_back(std::stof(substr));
    }
  }

  std::cout << "Size:" << data.size()<< std::endl;

  for (int i = 0; i < data.size(); i+=4) {
    std::cout << i << ": (" << data.at(i) << "," << data.at(i + 1) << ","
              << data.at(i + 2) << ") time:" << data.at(i + 3) << std::endl;

              
  }



  csv_file.close();
}
