#include <chrono>
#include <cstdlib>
#include <future>

#include "QuadPositionCmdPubSubTypes.h"
#include "default_participant.h"
#include "default_publisher.h"
#include "grasper.h"
#include "paths.h"
#include "quadcopter_msgs/msgs/QuadPositionCmd.h"

void swoop(Grasper& grasp, float objx, float objy, float boxx, float boxy) {
  Vec3 gravity = Vec3(0, 0, -9.81);
  // set acc and vel comands to 0
  Vec3 vel0 = Vec3(0, 0, 0);
  Vec3 acc0 = Vec3(0, 0, 0);
  Vec3 velf = Vec3(0, 0, 0);
  Vec3 accf = Vec3(0, 0, 0);

  // swoop first half
  Vec3 pos0 = Vec3(objx - 2.0, objy, 2.0);
  Vec3 posf = Vec3(objx - 0.2, objy, 0.75);
  grasp.go_to_pos_minJerk(pos0, vel0, acc0, posf, velf, accf, gravity, 2);

  grasp.go_to_pos(objx, objy, 0.6, 4, false);
  grasp.go_to_pos(objx, objy, 0.45, 4, false);
  grasp.go_to_pos(objx, objy, 0.6, 2, false);
  // swoop second half
  pos0 = Vec3(objx, objy, 0.75);
  posf = Vec3(objx + 2.0, objy, 2.0);
  grasp.go_to_pos_minJerk(pos0, vel0, acc0, posf, velf, accf, gravity, 2);

  // transfer to box
  pos0 = Vec3(objx + 2.0, objy, 2.0);
  posf = Vec3(boxx + 2.0, boxy, 2.0);
  grasp.go_to_pos_minJerk(pos0, vel0, acc0, posf, velf, accf, gravity, 3);

  // swoop first half
  pos0 = Vec3(boxx + 2.0, boxy, 2.0);
  posf = Vec3(boxx, boxy, 0.75);
  grasp.go_to_pos_minJerk(pos0, vel0, acc0, posf, velf, accf, gravity, 2);

  std::this_thread::sleep_for(std::chrono::milliseconds(2500));

  // swoop second half
  pos0 = Vec3(boxx, boxy, 0.75);
  posf = Vec3(boxx - 1.5, boxy, 2.0);
  grasp.go_to_pos_minJerk(pos0, vel0, acc0, posf, velf, accf, gravity, 2);

  // transfer to object
  pos0 = Vec3(boxx - 1.5, boxy, 2.0);
  posf = Vec3(objx - 2.0, objy, 2.0);
  grasp.go_to_pos_minJerk(pos0, vel0, acc0, posf, velf, accf, gravity, 3);
}

int main() {
  Grasper grasper;
  // box coordinates (0.25, 1)
  // transformed (-0.25,-1.5)

  grasper.set_parameters(paths::parameters_path);
  grasper.load_setpoints(paths::setpoint_list_path);

  Vec3 gravity = Vec3(0, 0, -9.81);
  // set acc and vel comands to 0
  Vec3 vel0 = Vec3(0, 0, 0);
  Vec3 acc0 = Vec3(0, 0, 0);
  Vec3 velf = Vec3(0, 0, 0);
  Vec3 accf = Vec3(0, 0, 0);
  // define msg
  // cpp_msg::Mocap quad_pos = grasper.quad_pose();

  // check for mocap data to avoid getting zeros in the beginning
  grasper.wait_for_data_quad();
  grasper.wait_for_data_object();
  grasper.wait_for_data_stand();
  // go to start

  Vec3 pos0 = Vec3(grasper.quad_pose().pose.position.x,
                   grasper.quad_pose().pose.position.y,
                   grasper.quad_pose().pose.position.z);

  Vec3 posf = Vec3(grasper.object_pose().pose.position.x - 2.0,
                   grasper.object_pose().pose.position.y, 2.0);

  grasper.go_to_pos_minJerk(pos0, vel0, acc0, posf, velf, accf, gravity, 2);
  std::this_thread::sleep_for(std::chrono::milliseconds(1500));

  // swoop
  swoop(grasper, grasper.object_pose().pose.position.x,
        grasper.object_pose().pose.position.y, 0, -1.5);

  ////////GO TO STAND AND LAND
  // to stand
  pos0 = Vec3(grasper.object_pose().pose.position.x - 2.0,
              grasper.object_pose().pose.position.y, 2.0);

  posf = Vec3(grasper.stand_pose().pose.position.x,
              grasper.stand_pose().pose.position.y, 1.5);

  // execute
  std::cout << "Go to homebase" << std::endl;
  grasper.go_to_pos_minJerk(pos0, vel0, acc0, posf, velf, accf, gravity, 2);

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  // land on stand
  grasper.go_to_pos(grasper.stand_pose().pose.position.x,
                    grasper.stand_pose().pose.position.y, 1.5, 5,
                    false);  // 6.5
  grasper.go_to_pos(grasper.stand_pose().pose.position.x,
                    grasper.stand_pose().pose.position.y, 0.75, 5,
                    false);  // 6.5
  grasper.go_to_pos(grasper.stand_pose().pose.position.x,
                    grasper.stand_pose().pose.position.y, 0.2, 3,
                    false);  // 6.5
  grasper.go_to_pos(grasper.stand_pose().pose.position.x,
                    grasper.stand_pose().pose.position.y, 0.0, 3,
                    false);  // 6.5
}
