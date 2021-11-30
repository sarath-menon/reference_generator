#include "grasper.h"

Grasper::Grasper() {
  // Fastdds ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`

  // Create domain participant
  dp = std::make_unique<DefaultParticipant>(0, "grasper");

  // Create  subscriber
  mocap_quad_sub = new DDSSubscriber(idl_msg::MocapPubSubType(), &quad_pose_,
                                     "mocap_srl_quad", dp->participant());

  // initialize  subscriberDefaultParticipant
  mocap_quad_sub->init();

  // Create  subscriber for object mocap
  mocap_object_sub =
      new DDSSubscriber(idl_msg::MocapPubSubType(), &object_pose_,
                        "mocap_srl_box", dp->participant());

  // initialize object mocap subscriberDefaultParticipant
  mocap_object_sub->init();

  // Create  subscriber for object mocap
  mocap_stand_sub = new DDSSubscriber(idl_msg::MocapPubSubType(), &stand_pose_,
                                      "mocap_srl_stand", dp->participant());

  // initialize object mocap subscriberDefaultParticipant
  mocap_stand_sub->init();

  // Create position cmd publisher
  position_pub = new DDSPublisher(idl_msg::QuadPositionCmdPubSubType(),
                                  "pos_cmd", dp->participant());

  // Initialize position publisher
  position_pub->init();

  // Create position cmd publisher
  gripper_pub = new DDSPublisher(idl_msg::QuadPositionCmdPubSubType(),
                                 "grip_cmd", dp->participant());

  // Initialize position publisher
  gripper_pub->init();
}

Grasper::~Grasper() {
  delete mocap_quad_sub;
  delete mocap_object_sub;
  delete mocap_stand_sub;
  delete position_pub;
  delete gripper_pub;
}
