#pragma once

inline bool check_reached(const float &current_pos, const float &desired_pos,
                          const float &threshold) {
  // Compute position difference
  float pos_diff = abs(current_pos - desired_pos);

  if (pos_diff <= threshold) {
    return true;
  } else {
    return false;
  }
}
