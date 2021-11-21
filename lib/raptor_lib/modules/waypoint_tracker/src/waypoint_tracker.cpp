#include "waypoint_tracker.h"

WaypointTracker::WaypointTracker(DefaultParticipant *dp) {

  // create motion controller
  motion_ctrl = std::make_unique<MotionCtrl>(dp);
};
