#pragma once

#include "behaviour.h"
#include "default_participant.h"
#include "default_publisher.h"
#include "default_subscriber.h"
#include "waypoint_tracker.h"
#include <math.h>

class GoOverObject {
public:
  GoOverObject();
  ~GoOverObject();

public:
  bool go_over_object(const std::string object, const float height,
                      const param::ctrl_type ctrl_type);

public:
  void set_parameters(const std::string path);
};
