#include "Raptor.h"

Raptor::Raptor(eprosima::fastdds::dds::DomainParticipant
                   *participant) { // Quadcopter position

  // Create  subscriber
  pose_sub = new DDSSubscriber(idl_msg::MocapPubSubType(), &pose_, "mocap_pose",
                               participant);

  // Create position cmd publisher
  cmd_pub = new DDSPublisher(idl_msg::QuadPositionCmdPubSubType(), "pos_cmd",
                             participant);

  // initialize  publishers and subscribers
  pose_sub->init();
  cmd_pub->init();
}

Raptor::~Raptor() {
  delete pose_sub;
  delete cmd_pub;
}