#include "motion_controller.h"

MotionCtrl::MotionCtrl(DefaultParticipant *dp) {
  // Fastdds ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`
  // Create  subscriber
  quad_sub = new DDSSubscriber(idl_msg::MocapPubSubType(), &quad_pose_,
                               "mocap_pose", dp->participant());

  // Create position cmd publisher
  position_pub = new DDSPublisher(idl_msg::QuadPositionCmdPubSubType(),
                                  "pos_cmd", dp->participant());

  // initialize  publishers and subscribers
  quad_sub->init();
  position_pub->init();
}

MotionCtrl::~MotionCtrl() {
  delete quad_sub;
  delete position_pub;
}
