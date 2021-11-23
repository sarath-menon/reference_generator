#include "safety_checks.h"
#include "waypoint_tracker.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

// to set parameters from yaml file
void WaypointTracker::set_parameters(const std::string path) {

  // Safety check, see if file exists
  safety_checks::yaml_file_check(path);

  // Load yaml file containing gains
  YAML::Node param_yaml = YAML::LoadFile(path);
  pos_thresholds_.x = param_yaml["x_threshold"].as<float>();
  pos_thresholds_.y = param_yaml["y_threshold"].as<float>();
  pos_thresholds_.z = param_yaml["z_threshold"].as<float>();
}

// to load waypoints from csv file
void WaypointTracker::load_waypoints(const std::string path) {
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
          x_wp_list.push_back(std::stof(substr));
          break;
        case 1:
          y_wp_list.push_back(std::stof(substr));
          break;
        case 2:
          z_wp_list.push_back(std::stof(substr));
          break;
        case 3:
          max_time_.push_back(std::stof(substr));
          break;
        }
      }
    }
  }

  // for (int i = 0; i < 4; i++) {
  //   std::cout << "Waypoint: " << i << ": (" << x_wp_list.at(i) << ","
  //             << y_wp_list.at(i) << "," << z_wp_list.at(i)
  //             << ") time:" << max_time_.at(i) << std::endl;
  // }

  csv_file.close();
}
