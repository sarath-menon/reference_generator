
#include "dds_manager.h"
#include "flight_manager.h"
#include "go_over_object.h"
#include "raptor.h"

int main() {

  // register domain participant to flight manager
  FlightManager::register_dds(DDS.participant());

  // create a flight manager for "srl_quad" raptor
  FlightManager fm_1("srl_quad");

  // // add go over object behaviour to fm_1 flight manager
  // fm_1.wp_tracker->go_to_waypoint();

  // shorter enumerations for convenience
}
