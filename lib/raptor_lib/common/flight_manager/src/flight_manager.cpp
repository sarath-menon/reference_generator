#include "flight_manager.h"

FlightManager::FlightManager(std::unique_ptr<Raptor> raptor_ptr_) {
  raptor_ptr_ = std::move(raptor_ptr_);

  wp_tracker = std::make_unique<WaypointTracker>(dp_);
}

void FlightManager::register_dds(DefaultParticipant *dp) { dp_ = dp; };