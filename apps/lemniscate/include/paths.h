#pragma once
#include "paths.h"
#include <filesystem>
#include <string>

namespace paths {

std::filesystem::path folder_path = std::filesystem::current_path();

const std::string abs_path =
    folder_path.u8string() + "/apps/lemniscate/parameters/";

const std::string lemniscate_prm = abs_path + "lemniscate.yaml";

const std::string ctrl_prm = abs_path + "controller.yaml";
} // namespace paths
