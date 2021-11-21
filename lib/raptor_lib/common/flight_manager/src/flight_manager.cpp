#include "flight_manager.h"

FlightManager::FlightManager(Raptor &raptor) {}

void FlightManager::register_dds(
    eprosima::fastdds::dds::DomainParticipant *participant) {

  // create waypoint tracker
  wp_tracker = std::make_unique<WaypointTracker>(participant);
};