#pragma once
#include "behaviour.h"
#include "waypoint_tracker.h"

class OverheadGrasp {
public:
  OverheadGrasp();
  ~OverheadGrasp();

public:
  bool grasp_object(const std::string object, const param::ctrl_type type);

public:
  void set_parameters(const std::string path);
};
