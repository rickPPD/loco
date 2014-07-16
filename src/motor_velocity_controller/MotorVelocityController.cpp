/*
 * MotorVelocityController.cpp
 *
 *  Created on: Jul 14, 2014
 *      Author: labstudent
 */

#include "loco/motor_velocity_controller/MotorVelocityController.hpp"

namespace loco {

MotorVelocityController::MotorVelocityController(
    robotModel::RobotModel *robotModel, LegGroup* legs) {
  robotModel_ = robotModel;
  legs_ = legs;
}

MotorVelocityController::~MotorVelocityController() {

}

// No parameters for now
bool MotorVelocityController::loadParameters(const TiXmlHandle &handle) {

  return true;
}

bool MotorVelocityController::initialize(double dt) {

  // Make sure the robot is on the ground and did not jump before
  // If true, the robot is in INIT state
  if (legs_->getLeftForeLeg()->isGrounded()
      && legs_->getRightForeLeg()->isGrounded()
      && legs_->getLeftHindLeg()->isGrounded()
      && legs_->getRightForeLeg()->isGrounded() && state_ != State::APEX) {
    state_ = State::INIT;
  }

  LegBase* leftForeLeg = legs_->getLeftForeLeg();
  leftForeInitJointPositions_ = leftForeLeg->getMeasuredJointPositions();

//  for (int i = 0; i < leftForeInitJointPositions_.size(); i++) {
//    std::cout << leftForeInitJointPositions_[i] << std::endl;
//  }

  return true;
}

/**
 * Sets GaussianKernelJumpPropagator to follow.
 */
void MotorVelocityController::setTrajectoryFollower(
    GaussianKernelJumpPropagator trajectoryFollower) {
  trajectoryFollower_ = trajectoryFollower;
}

/**
 * Enables joint velocity control when set.
 */
void MotorVelocityController::setInVelocityMode(bool isInVelocityMode) {
  inVelocityMode_ = isInVelocityMode;
}

void MotorVelocityController::advance(double dt) {
  Eigen::Vector3d velocities;

  if (inVelocityMode_) {
    // Different joint types with indices 0, 1, 2 respectively (in this order).
    updateState();

    if (state_ == LIFTOFF || state_ == State::INIT) {
      velocities(0) = trajectoryFollower_.predict(0);
      velocities(1) = trajectoryFollower_.predict(1);
      velocities(2) = trajectoryFollower_.predict(2);

      robotModel_->act().setVelOfLeg(velocities, 0);
      robotModel_->act().setVelOfLeg(velocities, 1);
      robotModel_->act().setVelOfLeg(-velocities, 2);
      robotModel_->act().setVelOfLeg(-velocities, 3);
    } else if (state_ == State::APEX || state_ == State::TOUCHDOWN) {
//      std::cout << "PositionMode" << std::endl;
      robotModel::VectorActM positionMode;
      positionMode.fill(robotModel::AM_Position);

      robotModel_->act().setPosOfLeg(leftForeInitJointPositions_,0);
      robotModel_->act().setPosOfLeg(leftForeInitJointPositions_, 1);
      robotModel_->act().setPosOfLeg(-leftForeInitJointPositions_, 2);
      robotModel_->act().setPosOfLeg(-leftForeInitJointPositions_, 3);

//      std::cout << "PositionMode! " << state_ << std::endl;
    }
  }
}

/**
 * Keeps track of current state of jump.
 * Jump occurs in the following phases:
 * INIT -> LIFTOFF -> APEX -> TOUCHDOWN
 */
void MotorVelocityController::updateState() {
  if (legs_->getLeftForeLeg()->getStateLiftOff()->isNow()
      && legs_->getRightForeLeg()->getStateLiftOff()->isNow()
      && legs_->getLeftHindLeg()->getStateLiftOff()->isNow()
      && legs_->getRightHindLeg()->getStateLiftOff()->isNow()
      && state_ == State::INIT) {

    state_ = State::LIFTOFF;

  } else if (!legs_->getLeftForeLeg()->isGrounded()
      && !legs_->getLeftHindLeg()->isGrounded()
      && !legs_->getRightHindLeg()->isGrounded()
      && !legs_->getRightForeLeg()->isGrounded()
      && state_ == State::LIFTOFF) {

    state_ = State::APEX;

  } else if (legs_->getLeftForeLeg()->isGrounded()
      && legs_->getRightForeLeg()->isGrounded()
      && legs_->getLeftHindLeg()->isGrounded()
      && legs_->getRightForeLeg()->isGrounded() && state_ == State::APEX) {

    state_ = State::TOUCHDOWN;
  }
}
} /* namespace loco */
