#include "flight_manager.h"

void FlightManager::add_behaviour(std::unique_ptr<Behaviour> behav) {
  behav_register.push_back(std::move(behav));
}