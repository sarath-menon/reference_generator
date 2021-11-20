#pragma once
#include "paths.h"
#include <filesystem>
#include <string>

namespace paths {

std::filesystem::path folder_path = std::filesystem::current_path();

const std::string abs_path =
    folder_path.u8string() + "/apps/circle/parameters/";

const std::string circle_params = abs_path + "circle.yaml";

const std::string ctrl_params = abs_path + "controller.yaml";
} // namespace paths
