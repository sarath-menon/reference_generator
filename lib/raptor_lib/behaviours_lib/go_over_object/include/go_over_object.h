#pragma once

#include "behaviour.h"
#include "default_participant.h"
#include "default_publisher.h"
#include "default_subscriber.h"
#include "waypoint_tracker.h"
#include <math.h>

class GoOverObject : public Behaviour {
public:
  GoOverObject();
  ~GoOverObject();

public:
  virtual void start() override{};

  virtual void stop() override{};

public:
  bool go_over_object(const std::string object, const float height,
                      const param::ctrl_type ctrl_type);

public:
  virtual void set_parameters(const std::string path) override;
};