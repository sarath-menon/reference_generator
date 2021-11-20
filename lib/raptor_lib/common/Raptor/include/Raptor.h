#pragma once

#include "MocapPubSubTypes.h"
#include "QuadPositionCmdPubSubTypes.h"
#include "default_participant.h"
#include "default_publisher.h"
#include "default_subscriber.h"
#include "geometry_msgs/msgs/Position.h"
#include "quadcopter_msgs/msgs/QuadPositionCmd.h"
#include "sensor_msgs/msgs/Mocap.h"
#include <cmath>
#include <cstring>

class Raptor {

public:
  Raptor(eprosima::fastdds::dds::DomainParticipant *participant);
  ~Raptor();

private:
  // raptor pose
  cpp_msg::Mocap pose_{};

  // quad position command
  cpp_msg::QuadPositionCmd cmd_{};

  // fastdds publishers and subscribers
private:
  // quadcopter pose subscriber
  DDSSubscriber<idl_msg::MocapPubSubType, cpp_msg::Mocap> *pose_sub;

  // Create publisher with msg type
  DDSPublisher *cmd_pub;

private:
  std::string name_{};

public:
  /// Getter function
  const std::string &name() const { return name_; }

public:
  // Intitiliaze the flight manager
  static void initialize();

  // Register a new raptor in the flight manager
  static void add_raptor(const std::string name);

  // Register a new object in the flight manager
  static void add_object(const std::string name);
};