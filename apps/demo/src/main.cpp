
#include "dds_manager.h"
#include "flight_manager.h"
#include "go_over_object.h"
#include "raptor.h"

int main() {

  FlightManager::register_dds(DDS.participant());

  FlightManager fm_1(std::make_unique<Raptor>("selva1"));

  fm_1.add_behaviour(GoOverObject::get());

  fm_1.behav_register.at(0)->start();

  // shorter enumerations for convenience

  // result = grasper.go_to_waypoint(1, mueller_ctrl);
}
