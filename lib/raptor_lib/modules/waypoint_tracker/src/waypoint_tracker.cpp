#include "waypoint_tracker.h"

WaypointTracker::WaypointTracker(
    eprosima::fastdds::dds::DomainParticipant *participant) {

  // create motion controller
  motion_ctrl = std::make_unique<MotionCtrl>(participant);
};
