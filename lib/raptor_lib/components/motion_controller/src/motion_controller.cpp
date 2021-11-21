#include "motion_controller.h"

MotionController::MotionController(
    eprosima::fastdds::dds::DomainParticipant *participant) {
  // Fastdds ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`
  // Create  subscriber
  quad_sub = new DDSSubscriber(idl_msg::MocapPubSubType(), &quad_pose_,
                               "mocap_pose", participant);

  // Create position cmd publisher
  position_pub = new DDSPublisher(idl_msg::QuadPositionCmdPubSubType(),
                                  "pos_cmd", participant);

  // initialize  publishers and subscribers
  quad_sub->init();
  position_pub->init();
}

MotionController::~MotionController() {
  delete quad_sub;
  delete position_pub;
}
