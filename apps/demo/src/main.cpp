
#include "dds_manager.h"
#include "flight_manager.h"
#include "go_over_object.h"
#include "raptor.h"

int main() {

  Raptor raptor_1;

  FlightManager fm_1(raptor_1);
  fm_1.register_dds(DDS.participant());

  auto go_to_pos{std::make_unique<GoOverObject>()};

  fm_1.add_behaviour(std::move(go_to_pos));

  fm_1.bahav_register.at(0)->start();

  // ptr->start();

  // shorter enumerations for convenience

  // result = grasper.go_to_waypoint(1, mueller_ctrl);
}
