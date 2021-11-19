#pragma once
#include "paths.h"
#include <filesystem>
#include <string>

namespace paths {

std::filesystem::path folder_path = std::filesystem::current_path();

const std::string abs_path = folder_path.u8string() + "/apps/swoop/parameters/";

const std::string waypoints_path = abs_path + "waypoints.csv";

const std::string parameters_path = abs_path + "parameters.yaml";
} // namespace paths
