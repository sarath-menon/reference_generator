#include <chrono>
#include <cstdlib>
#include <future>

#include "QuadPositionCmdPubSubTypes.h"
#include "default_participant.h"
#include "default_publisher.h"
#include "grasper.h"
#include "paths.h"
#include "quadcopter_msgs/msgs/QuadPositionCmd.h"

void swoop(Grasper& grasp, Vec3 obj, Vec3 box, Vec3 ps, Vec3 pf) {
  Vec3 gravity = Vec3(0, 0, -9.81);
  // set acc and vel comands to 0
  Vec3 vel0 = Vec3(0, 0, 0);
  Vec3 acc0 = Vec3(0, 0, 0);
  Vec3 velf = Vec3(0, 0, 0);
  Vec3 accf = Vec3(0, 0, 0);

  // swoop first half
  Vec3 pos0 = ps;
  Vec3 posf = Vec3(obj.x - 0.4, obj.y, 0.75);
  grasp.go_to_pos_minJerk(pos0, vel0, acc0, posf, velf, accf, gravity, 2);

  grasp.go_to_pos(obj.x + 0.1, obj.y, 0.6, 4, false);
  grasp.go_to_pos(obj.x + 0.1, obj.y, obj.z, 4, false);
  grasp.go_to_pos(obj.x + 0.1, obj.y, 0.6, 2, false);
  // swoop second half
  pos0 = Vec3(obj.x, obj.y, 0.75);
  posf = Vec3(obj.x + 2.0, obj.y, 2.0);
  grasp.go_to_pos_minJerk(pos0, vel0, acc0, posf, velf, accf, gravity, 2);

  // transfer to box
  pos0 = Vec3(obj.x + 2.0, obj.y, 2.0);
  posf = Vec3(box.x + 2.0, box.y, 2.0);
  grasp.go_to_pos_minJerk(pos0, vel0, acc0, posf, velf, accf, gravity, 3);

  // swoop first half
  pos0 = Vec3(box.x + 2.0, box.y, 2.0);
  posf = Vec3(box.x, box.y, 0.75);
  grasp.go_to_pos_minJerk(pos0, vel0, acc0, posf, velf, accf, gravity, 2);

  std::this_thread::sleep_for(std::chrono::milliseconds(2500));

  // swoop second half
  pos0 = Vec3(box.x, box.y, 0.75);
  posf = Vec3(box.x - 1.5, box.y, 2.0);
  grasp.go_to_pos_minJerk(pos0, vel0, acc0, posf, velf, accf, gravity, 2);

  // transfer to object
  pos0 = Vec3(box.x - 1.5, box.y, 2.0);
  posf = pf;
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
  constexpr float stand_offset = 0.29;
  Vec3 box = Vec3(0, -1.5, 0);
  ///////////FIRST SWOOP
  Vec3 object = Vec3(grasper.object_pose().pose.position.x,
                     grasper.object_pose().pose.position.y - 0.01, 0.45);
  Vec3 start = Vec3(grasper.object_pose().pose.position.x - 2.0,
                    grasper.object_pose().pose.position.y, 2.0);
  Vec3 end =
      Vec3(grasper.object_pose().pose.position.x - 2.0,
           grasper.object_pose().pose.position.y - stand_offset - 0.01, 2.0);
  swoop(grasper, object, box, start, end);
  // ///////////SECOND SWOOP
  object =
      Vec3(grasper.object_pose().pose.position.x,
           grasper.object_pose().pose.position.y - stand_offset - 0.01, 0.45);
  start =
      Vec3(grasper.object_pose().pose.position.x - 2.0,
           grasper.object_pose().pose.position.y - stand_offset - 0.01, 2.0);
  end = Vec3(grasper.object_pose().pose.position.x - 2.0,
             grasper.object_pose().pose.position.y + stand_offset + 0.02, 2.0);
  swoop(grasper, object, box, start, end);
  // ///////////THIRD SWOOP
  object =
      Vec3(grasper.object_pose().pose.position.x,
           grasper.object_pose().pose.position.y + stand_offset + 0.02, 0.45);
  start =
      Vec3(grasper.object_pose().pose.position.x - 2.0,
           grasper.object_pose().pose.position.y + stand_offset + 0.02, 2.0);
  end = Vec3(grasper.object_pose().pose.position.x - 2.0,
             grasper.object_pose().pose.position.y, 2.0);
  swoop(grasper, object, box, start, end);

  ////////GO TO STAND AND LAND
  pos0 = Vec3(grasper.object_pose().pose.position.x - 2.0,
              grasper.object_pose().pose.position.y, 2.0);
  posf = Vec3(grasper.stand_pose().pose.position.x,
              grasper.stand_pose().pose.position.y, 1.5);
  grasper.go_to_pos_minJerk(pos0, vel0, acc0, posf, velf, accf, gravity, 2);

  // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

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
