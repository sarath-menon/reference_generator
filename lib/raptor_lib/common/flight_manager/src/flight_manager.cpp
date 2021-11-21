#include "flight_manager.h"

FlightManager::FlightManager(std::unique_ptr<Raptor> raptor_ptr_) {}

void FlightManager::register_dds(const DefaultParticipant *dp) {

  // create waypoint tracker
  wp_tracker = std::make_unique<WaypointTracker>(dp);

  raptor_ptr_ = std::move(raptor_ptr_);
};