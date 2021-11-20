#include "flight_manager.h"
#include "safety_checks.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

// to load waypoints from csv file
void FlightManager::load_waypoints(const std::string path) {
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
          x_waypoint_.push_back(std::stof(substr));
          break;
        case 1:
          y_waypoint_.push_back(std::stof(substr));
          break;
        case 2:
          z_waypoint_.push_back(std::stof(substr));
          break;
        case 3:
          max_reach_time_.push_back(std::stof(substr));
          break;
        }
      }
    }
  }

  // for (int i = 0; i < 4; i++) {
  //   std::cout << "Waypoint: " << i << ": (" << x_waypoint_.at(i) << ","
  //             << y_waypoint_.at(i) << "," << z_waypoint_.at(i)
  //             << ") time:" << max_reach_time_.at(i) << std::endl;
  // }

  csv_file.close();
}