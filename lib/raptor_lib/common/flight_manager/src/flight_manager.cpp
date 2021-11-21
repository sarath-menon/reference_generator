#include "flight_manager.h"

FlightManager::FlightManager(Raptor &raptor) {}

void FlightManager::register_dds(const DefaultParticipant *dp) {

  // create waypoint tracker
  wp_tracker = std::make_unique<WaypointTracker>(dp);
};