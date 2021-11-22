#include "QuadPositionCmdPubSubTypes.h"
#include "default_participant.h"
#include "default_publisher.h"
#include "grasper.h"
#include "paths.h"
#include "quadcopter_msgs/msgs/QuadPositionCmd.h"
#include <chrono>
#include <cstdlib>
#include <future>

int main() {
  Grasper grasper;

  grasper.set_parameters(paths::parameters_path);
  grasper.load_setpoints(paths::setpoint_list_path);

  //ON GROUND

  // bool result = grasper.go_near_object(0.0, 0.0, 1.0, 6.5,false);
  // result = grasper.go_near_object(0.0, 0.0, 0.5, 4,true);
  // result = grasper.go_near_object(0.0, 0.0, 0.01, 5,false);
  // result = grasper.departure(1.0,4.0,false);
  // result = grasper.go_to_pos(0);

  //ON TABLE

  // bool result = grasper.go_near_object(0.0, 0.0, 0.5, 6.5,false);
  // result = grasper.go_near_object(0.0, 0.0, 0.01, 5,false);
  // result = grasper.departure(1.5,4.0,false);
  // result = grasper.go_to_pos(1);

}

