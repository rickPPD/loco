/*****************************************************************************************
* Software License Agreement (BSD License)
*
* Copyright (c) 2014, Christian Gehring, Péter Fankhauser, C. Dario Bellicoso, Stelian Coros
* All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of Autonomous Systems Lab nor ETH Zurich
*     nor the names of its contributors may be used to endorse or
*     promote products derived from this software without specific
*     prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*/
/*
 * LegBase.cpp
 *
 *  Created on: Feb 25, 2014
 *      Author: gech
 */

#include "loco/common/LegBase.hpp"

namespace loco {

LegBase::LegBase() :
  name_(""),
  links_(nullptr),
  stancePhase_(0.0),
  previousStancePhase_(0.0),
  swingPhase_(0.0),
  previousSwingPhase_(0.0),
  stanceDuration_(0.0),
  swingDuration_(0.0),
  isGrounded_(false),
  wasGrounded_(false),
  shouldBeGrounded_(false),
  isSlipping_(false),
  isSupportLeg_(false),
  isLosingContact_(false),
  didTouchDownAtLeastOnceDuringStance_(false),
  loadFactor_(1.0),
  stateTouchDown_(),
  stateLiftOff_(),
  desiredJointControlModes_(),
  desiredJointPositions_(),
  measuredJointPositions_(),
  measuredJointVelocities_(),
  desiredJointTorques_(),
  measuredJointTorques_(),
  stateSwitcher_(nullptr),
  isInStandConfiguration_(false)
{

}

LegBase::LegBase(const std::string& name, LegLinkGroup* links) :
  name_(name),
  links_(links),
  stancePhase_(0.0),
  previousStancePhase_(0.0),
  swingPhase_(0.0),
  previousSwingPhase_(0.0),
  stanceDuration_(0.0),
  swingDuration_(0.0),
  isGrounded_(false),
  wasGrounded_(false),
  shouldBeGrounded_(false),
  isSlipping_(false),
  isSupportLeg_(false),
  isLosingContact_(false),
  didTouchDownAtLeastOnceDuringStance_(false),
  loadFactor_(1.0),
  stateTouchDown_(),
  stateLiftOff_(),
  desiredJointControlModes_(),
  desiredJointPositions_(),
  measuredJointPositions_(),
  measuredJointVelocities_(),
  desiredJointTorques_(),
  measuredJointTorques_(),
  stateSwitcher_(nullptr),
  isInStandConfiguration_(false)
{

}

LegBase::~LegBase() {

}

LegLinkGroup* LegBase::getLinks() {
  return links_;
}


double LegBase::getStancePhase() const {
  return stancePhase_;
}
double LegBase::getSwingPhase() const {
  return swingPhase_;
}

double LegBase::getStanceDuration() const {
  return stanceDuration_;
}
double LegBase::getSwingDuration() const {
  return swingDuration_;
}

bool LegBase::isSupportLeg() const {
	return isSupportLeg_;
}

void LegBase::setIsSupportLeg(bool isSupportLeg) {
	isSupportLeg_ = isSupportLeg;
}


bool LegBase::didTouchDownAtLeastOnceDuringStance() const {
	return didTouchDownAtLeastOnceDuringStance_;
}

void LegBase::setDidTouchDownAtLeastOnceDuringStance(bool didTouchDownAtLeastOnceDuringStance) {
	didTouchDownAtLeastOnceDuringStance_ = didTouchDownAtLeastOnceDuringStance;
}


void LegBase::setPreviousStancePhase(double previousStancePhase) {
	previousStancePhase_ = previousStancePhase;
}

double LegBase::getPreviousStancePhase() const {
	return previousStancePhase_;
}

void LegBase::setPreviousSwingPhase(double previousSwingPhase) {
	previousSwingPhase_ = previousSwingPhase;
}

double LegBase::getPreviousSwingPhase() const {
	return previousSwingPhase_;
}



bool LegBase::isGrounded() const {
  return isGrounded_;
}

bool LegBase::wasGrounded() const {
  return wasGrounded_;
}

bool LegBase::shouldBeGrounded() const {
  return shouldBeGrounded_;
}

bool LegBase::isAndShouldBeGrounded() const {
  return (isGrounded_ && shouldBeGrounded_);
}

bool LegBase::isSlipping() const {
  return isSlipping_;
}

double LegBase::getDesiredLoadFactor() const
{
  return loadFactor_;
}





void LegBase::setStancePhase(double phase) {
  stancePhase_ = phase;
}

void LegBase::setSwingPhase(double phase) {
  swingPhase_ = phase;
}

void LegBase::setStanceDuration(double duration) {
  stanceDuration_ = duration;
}

void LegBase::setSwingDuration(double duration) {
  swingDuration_ = duration;
}

void LegBase::setIsGrounded(bool isGrounded) {
  isGrounded_ = isGrounded;
}

void LegBase::setWasGrounded(bool wasGrounded) {
  wasGrounded_ = wasGrounded;
}

void LegBase::setShouldBeGrounded(bool shouldBeGrounded) {
  shouldBeGrounded_ = shouldBeGrounded;
}

void LegBase::setIsSlipping(bool isSlipping) {
  isSlipping_ = isSlipping;
}

void LegBase::setDesiredLoadFactor(double loadFactor)
{
  // TODO Check for validity
  loadFactor_ = loadFactor;
}


LegStateTouchDown* LegBase::getStateTouchDown() {
  return &stateTouchDown_;
}


const LegStateTouchDown& LegBase::getStateTouchDown() const {
  return stateTouchDown_;
}


LegStateLiftOff* LegBase::getStateLiftOff() {
  return &stateLiftOff_;
}


const LegStateLiftOff& LegBase::getStateLiftOff() const {
  return stateLiftOff_;
}


void LegBase::setDesiredJointPositions(const JointPositions& jointPositions)
{
  desiredJointPositions_ = jointPositions;
}

void LegBase::setMeasuredJointPositions(const JointPositions& jointPositions)
{
  measuredJointPositions_ = jointPositions;
}

void LegBase::setMeasuredJointVelocities(const JointVelocities& jointVelocities)
{
  measuredJointVelocities_ = jointVelocities;
}

void LegBase::setMeasuredJointTorques(const JointTorques& jointTorques)
{
  measuredJointTorques_ = jointTorques;
}

void LegBase::setDesiredJointTorques(const JointTorques& jointTorques)
{
  desiredJointTorques_ = jointTorques;
}

const LegBase::JointPositions& LegBase::getDesiredJointPositions()  const
{
  return desiredJointPositions_;
}

const LegBase::JointPositions& LegBase::getMeasuredJointPositions()  const
{
  return measuredJointPositions_;
}

const LegBase::JointVelocities& LegBase::getMeasuredJointVelocities()  const
{
  return measuredJointVelocities_;
}

void LegBase::setDesiredJointControlModes(const JointControlModes& jointControlMode)
{
  desiredJointControlModes_ = jointControlMode;
}

const LegBase::JointControlModes& LegBase::getDesiredJointControlModes() const
{
  return desiredJointControlModes_;
}

const LegBase::JointTorques& LegBase::getDesiredJointTorques() const
{
  return desiredJointTorques_;
}

const LegBase::JointTorques& LegBase::getMeasuredJointTorques() const
{
  return measuredJointTorques_;
}


const std::string& LegBase::getName() const {
  return name_;
}

bool LegBase::isLosingContact() const {
	return isLosingContact_;
}

void LegBase::setIsLosingContact(bool isLosingContact) {
	isLosingContact_ = isLosingContact;
}


StateSwitcher* LegBase::getStateSwitcher() const {
  return stateSwitcher_;
}


std::ostream& operator << (std::ostream& out, const LegBase& leg) {
  out << "name: " << leg.getName() << std::endl;
  out << "swing phase: " << leg.getSwingPhase() << std::endl;
  out << "stance phase: " << leg.getStancePhase() << std::endl;
  out << "swing duration: " << leg.getSwingDuration() << std::endl;
  out << "stance duration: " << leg.getStanceDuration() << std::endl;

  out << "is grounded: " << (leg.isGrounded() ? "yes" : "no") << std::endl;
  out << "should be grounded: " << (leg.shouldBeGrounded() ? "yes" : "no") << std::endl;
  out << "was grounded: " << (leg.wasGrounded() ? "yes" : "no") << std::endl;
  out << "is slipping: " << (leg.isSlipping() ? "yes" : "no") << std::endl;

  out << "did touchdown: " << ( leg.getStateTouchDown().isNow() ? "yes" : "no" ) << std::endl;
  out << "       early?: " << ( leg.getStateTouchDown().lastStateWasEarly() ? "yes" : "no" ) << std::endl;
  out << "        late?: " << ( leg.getStateTouchDown().lastStateWasLate() ? "yes" : "no" ) << std::endl;
  out << "most recent occurred at time: " << leg.getStateTouchDown().StateChangedAtTime() << std::endl;

  out << "did liftoff: " << ( leg.getStateLiftOff().isNow() ? "yes" : "no" ) << std::endl;
  out << "most recent occurred at time: " << leg.getStateLiftOff().StateChangedAtTime() << std::endl;

  out << "did touchdown: " << (leg.getStateTouchDown().isNow() ? "yes" : "no") << std::endl;

  return out;
}

const Position& LegBase::getDesiredWorldToFootPositionInWorldFrame() const {
  return positionWorldToDesiredFootInWorldFrame_;
}

void LegBase::setDesireWorldToFootPositionInWorldFrame(const Position& position) {
  positionWorldToDesiredFootInWorldFrame_ = position;
}


void LegBase::setIsInStandConfiguration(bool isInStandConfiguration) {
  isInStandConfiguration_ = isInStandConfiguration;
}

bool LegBase::isInStandConfiguration() const {
  return isInStandConfiguration_;
}


} /* namespace loco */
