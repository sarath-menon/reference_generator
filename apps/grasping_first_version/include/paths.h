#pragma once

#include "paths.h"
#include <string>

namespace paths {
const std::string folder_path = "apps/grasping_first_version/parameters/";

const std::string normal_waypoints_path = folder_path + "normal_waypoints.csv";

const std::string mueller_waypoints_path =
    folder_path + "mueller_waypoints.csv";

const std::string parameters_path = folder_path + "parameters.yaml";
} // namespace paths
