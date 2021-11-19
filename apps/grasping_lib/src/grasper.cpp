#include "grasper.h"

Grasper::Grasper() {
  // Fastdds ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`

  // Create domain participant
  dp = std::make_unique<DefaultParticipant>(0, "grasper");

  // Create  subscriber
  quad_sub = new DDSSubscriber(idl_msg::MocapPubSubType(), &quad_pose_,
                               "mocap_pose", dp->participant());

  // Create  subscriber for object mocap
  object_sub = new DDSSubscriber(idl_msg::MocapPubSubType(), &object_pose_,
                                 "mocap_object_pose", dp->participant());

  // Create position cmd publisher
  position_pub = new DDSPublisher(idl_msg::QuadPositionCmdPubSubType(),
                                  "pos_cmd", dp->participant());

  // initialize  publishers and subscribers
  quad_sub->init();
  object_sub->init();
  position_pub->init();
}

Grasper::~Grasper() {
  delete quad_sub;
  delete object_sub;
  delete position_pub;
}
