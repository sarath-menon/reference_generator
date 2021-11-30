#include <chrono>
#include <cstdlib>
#include <future>

#include "QuadPositionCmdPubSubTypes.h"
#include "default_participant.h"
#include "default_publisher.h"
#include "grasper.h"
#include "paths.h"
#include "quadcopter_msgs/msgs/QuadPositionCmd.h"

int main() {
  Grasper grasper;

  grasper.set_parameters(paths::parameters_path);
  grasper.load_setpoints(paths::setpoint_list_path);
  bool result;
  // GRASPING OBJECT FROM STAND
  // taking off via pos_ctrl_interface

  // grabbing object
  result = grasper.go_near_object(0.0, 0.0, 1.0, 5, false, "box");   // 6.5
  result = grasper.go_near_object(0.0, 0.0, 0.5, 4, true, "box");    // 6.5
  result = grasper.go_near_object(0.0, 0.0, 0.20, 4, false, "box");  // 6.5
  result = grasper.departure(1.0, 4, false);  // leaving after grabbing

  // drop object
  result = grasper.go_to_pos(0, false);
  // going back to stand
  result = grasper.go_near_object(0.0, 0.0, 1.0, 5, false, "stand");  // 6.5
  result = grasper.go_near_object(0.0, 0.0, 0.2, 4, true, "stand");   // 6.5
  result = grasper.go_near_object(0.0, 0.0, 0.0, 4, false, "stand");  // 6.5
  // result = grasper.go_near_object(0.0, 0.0, 1.0, 5, false, "box");

  // ON GROUND

  // bool result = grasper.go_near_object(0.0, 0.0, 1.0, 6.5,false);
  // result = grasper.go_near_object(0.0, 0.0, 0.5, 4,true);
  // result = grasper.go_near_object(0.0, 0.0, 0.01, 5,false);
  // result = grasper.departure(1.0,4.0,false);
  // result = grasper.go_to_pos(0);

  // ON TABLE

  // bool result = grasper.go_near_object(0.0, 0.0, 0.5, 6.5,false);
  // result = grasper.go_near_object(0.0, 0.0, 0.01, 5,false);
  // result = grasper.departure(1.5,4.0,false);
  // result = grasper.go_to_pos(1);
}

// WORKING GRABBING
//  // grabbing object
//   result = grasper.go_near_object(0.0, 0.0, 1.0, 4, true, "box");    // 6.5
//   result = grasper.go_near_object(0.0, 0.0, 0.5, 4, false, "box");   // 6.5
//   result = grasper.go_near_object(0.0, 0.0, 0.20, 4, false, "box");  // 6.5
//   result = grasper.departure(1.0, 4, false);  // leaving after grabbing

//   // drop object
//   result = grasper.go_to_pos(0, false);
//   // going back to stand
//   result = grasper.go_near_object(0.0, 0.0, 1.0, 4, true, "stand");   // 6.5
//   result = grasper.go_near_object(0.0, 0.0, 0.2, 4, false, "stand");  // 6.5
//   result = grasper.go_near_object(0.0, 0.0, 0.0, 4, false, "stand");  // 6.5
//   // result = grasper.go_near_object(0.0, 0.0, 1.0, 5, false, "box");
