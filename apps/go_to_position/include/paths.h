#pragma once
#include <filesystem>

#include "paths.h"
#include <string>

namespace paths {

std::filesystem::path folder_path = std::filesystem::current_path();

const std::string abs_path =
    folder_path.u8string() + "/apps/go_to_position/parameters/";

const std::string setpoint_path = abs_path + "setpoint.yaml";
} // namespace paths
