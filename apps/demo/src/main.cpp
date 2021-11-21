
#include "dds_manager.h"
#include "flight_manager.h"
#include "go_over_object.h"
#include "raptor.h"

int main() {

  // register domain participant to flight manager
  FlightManager::register_dds(DDS.participant());

  // create a flight manager for "srl_quad" raptor
  FlightManager fm_1(std::make_unique<Raptor>("selva1"));

  // add go over object behaviour to fm_1 flight manager
  fm_1.add_behaviour(GoOverObject::get());

  fm_1.behav_register.at(0)->start();

  // shorter enumerations for convenience

  // result = grasper.go_to_waypoint(1, mueller_ctrl);
}
