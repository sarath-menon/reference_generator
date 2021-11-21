#include "flight_manager.h"

FlightManager::FlightManager(const std::string raptor_name) {

  // create raptor object
  raptor_ptr_ = std::make_unique<Raptor>("selva1");

  // create waypoint tracker
  wp_tracker = std::make_unique<WaypointTracker>(dp_);
}

void FlightManager::register_dds(DefaultParticipant *dp) { dp_ = dp; };