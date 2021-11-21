
#include "dds_manager.h"
#include "flight_manager.h"
#include "raptor.h"

int main() {

  Raptor raptor_1;

  FlightManager fm_1(raptor_1);
  fm_1.register_dds(DDS.participant());

  // shorter enumerations for convenience

  // result = grasper.go_to_waypoint(1, mueller_ctrl);
}
