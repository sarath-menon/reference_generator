#pragma once
#include "paths.h"
#include <filesystem>
#include <string>

namespace paths {

std::filesystem::path folder_path = std::filesystem::current_path();

const std::string abs_path =
    folder_path.u8string() + "/apps/minimum_jerk/parameters/";

const std::string setpoint_path = abs_path + "setpoint.yaml";
} // namespace paths
