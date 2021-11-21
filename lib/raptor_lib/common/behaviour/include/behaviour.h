#pragma once

#include "waypoint_tracker.h"
#include <cmath>
#include <cstring>

class Behaviour {

public:
  Behaviour() = default;
  virtual ~Behaviour() = default;

public:
  virtual void start();
  virtual void stop();

public:
  virtual void set_parameters(const std::string path);
};