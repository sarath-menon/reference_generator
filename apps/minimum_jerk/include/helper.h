#pragma once

#include "RapidTrajectoryGenerator.h"
using namespace RapidQuadrocopterTrajectoryGenerator;

// Two simple helper function to make testing easier
inline const char *GetInputFeasibilityResultName(
    RapidTrajectoryGenerator::InputFeasibilityResult fr) {
  switch (fr) {
  case RapidTrajectoryGenerator::InputFeasible:
    return "Feasible";
  case RapidTrajectoryGenerator::InputIndeterminable:
    return "Indeterminable";
  case RapidTrajectoryGenerator::InputInfeasibleThrustHigh:
    return "InfeasibleThrustHigh";
  case RapidTrajectoryGenerator::InputInfeasibleThrustLow:
    return "InfeasibleThrustLow";
  case RapidTrajectoryGenerator::InputInfeasibleRates:
    return "InfeasibleRates";
  }
  return "Unknown!";
};

inline const char *GetStateFeasibilityResultName(
    RapidTrajectoryGenerator::StateFeasibilityResult fr) {
  switch (fr) {
  case RapidTrajectoryGenerator::StateFeasible:
    return "Feasible";
  case RapidTrajectoryGenerator::StateInfeasible:
    return "Infeasible";
  }
  return "Unknown!";
};