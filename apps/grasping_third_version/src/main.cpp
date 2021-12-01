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

  // define gravity
  Vec3 gravity = Vec3(0, 0, -9.81);
  // set acc and vel comands to 0
  Vec3 vel0 = Vec3(0,0,0);
  Vec3 acc0 = Vec3(0,0,0);
  Vec3 velf = Vec3(0,0,0);
  Vec3 accf = Vec3(0,0,0);
  // define msg
  cpp_msg::Mocap quad_pos = grasper.quad_pose();

  ////////////////////////////////////////////// go to start location
  // boundary conditions
  // grasper.go_to_pos(1, 1);
  // Vec3 pos0 = Vec3( quad_pos.pose.position.x,
  //                   quad_pos.pose.position.y,
  //                   quad_pos.pose.position.z);

  Vec3 pos0 = Vec3( 2.0, 0.0, 2.0);
  
  Vec3 posf = Vec3( -2.0, 0.0, 2.0);

  //execute
  std::cout << "Go to starting position" << std::endl;
  grasper.go_to_pos_minJerk(pos0, vel0, acc0, posf, velf, accf, gravity, 
                            grasper.startPoint_completion_time());

  std::this_thread::sleep_for(std::chrono::seconds(grasper.startPoint_wait_swoop()/1000));


  ////////////////////////////////////////////// swoop first part
  // boundary conditions
  // quad_pos = grasper.quad_pose();
  // pos0 = Vec3(  quad_pos.pose.position.x,
  //               quad_pos.pose.position.y,
  //               quad_pos.pose.position.z);
  pos0 = Vec3( -2.0, 0.0, 2.0);
  velf = Vec3(0.5,0,0);
  
  posf = Vec3( 0.0, 0.0, 0.7);

  // execute swoop
  std::cout << "Exectue: Swoop first part" << std::endl;
  grasper.go_to_pos_minJerk(pos0, vel0, acc0, posf, velf, accf, gravity, 
                            grasper.swoop_completion_time());

  // std::this_thread::sleep_for(std::chrono::seconds(grasper.swoop_wait_mid()/1000));


  ////////////////////////////////////////////// swoop second part
  // boundary conditions
  // quad_pos = grasper.quad_pose();
  // pos0 = Vec3( quad_pos.pose.position.x,
  //                   quad_pos.pose.position.y,
  //                   quad_pos.pose.position.z);
  pos0 = Vec3( 0.0, 0.0, 0.7);
  velf = Vec3(0,0,0);
  vel0 = Vec3(0.5,0,0);
  posf = Vec3( 2.0, 0.0, 2.0);

  // execute swoop
  std::cout << "Exectue: Swoop second part" << std::endl;
  grasper.go_to_pos_minJerk(pos0, vel0, acc0, posf, velf, accf, gravity, 
                            grasper.swoop_completion_time());



  // GRASPING OBJECT FROM STAND
  // taking off via pos_ctrl_interface

  //  TESTING GRABB
  // while (true) {
  //   result = grasper.grip(1);
  //   std::this_thread::sleep_for(std::chrono::milliseconds(200));
  //   result = grasper.grip(0);
  //   std::this_thread::sleep_for(std::chrono::milliseconds(200));
  // }

  // GRABBING OBJECT
  // result = grasper.go_near_object(0.0, 0.0, 1.0, 5, false, "box");   // 6.5
  // result = grasper.go_near_object(0.0, 0.0, 0.5, 4, true, "box");    // 6.5
  // result = grasper.go_near_object(0.0, 0.0, 0.20, 4, false, "box");  // 6.5
  // result = grasper.departure(1.0, 4, false);  // leaving after grabbing
  // result = grasper.grip(1);
  // // drop object
  // result = grasper.go_to_pos(0, false);
  // // going back to stand
  // result = grasper.go_near_object(0.0, 0.0, 1.0, 5, false, "stand");  // 6.5
  // result = grasper.go_near_object(0.0, 0.0, 0.2, 4, true, "stand");   // 6.5
  // result = grasper.go_near_object(0.0, 0.0, 0.0, 4, false, "stand");  // 6.5
  // // result = grasper.go_near_object(0.0, 0.0, 1.0, 5, false, "box");

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
