/*
 * JointControllerStarlETH.hpp
 *
 *  Created on: Apr 2, 2014
 *      Author: gech
 */

#ifndef LOCO_JOINTCONTROLLERSTARLETH_HPP_
#define LOCO_JOINTCONTROLLERSTARLETH_HPP_

#include "loco/joint_control/JointControllerBase.hpp"
#include <kindr/phys_quant/PhysicalQuantitiesEigen.hpp>
#include <loco/common/TypeDefsStarlETH.hpp>
#include "RobotModel.hpp"



namespace loco {

class JointControllerStarlETH : public JointControllerBase {
 public:

  typedef kindr::phys_quant::eigen_impl::VectorTypeless<double, 12> JointVector;
 public:
  JointControllerStarlETH(robotModel::RobotModel* robotModel);
  virtual ~JointControllerStarlETH();

  virtual bool initialize(double dt);
  virtual bool advance(double dt);

  const JointTorques& getJointTorques() const;

  void setJointControlGainsHAA(double kp, double kd);
  void setJointControlGainsHFE(double kp, double kd);
  void setJointControlGainsKFE(double kp, double kd);
  void setMaxTorqueHAA(double maxTorque);
  void setMaxTorqueHFE(double maxTorque);
  void setMaxTorqueKFE(double maxTorque);

  virtual bool loadParameters(const TiXmlHandle& handle);

  virtual void setIsClampingTorques(bool sClamping);

  virtual void setDesiredJointPositionsInVelocityControl(const robotModel::VectorAct& positions);
  void setJointPositionLimitsFromDefaultConfiguration(const Eigen::Vector3d& jointMinPositionsForLegInDefaultConfiguration,
                                                                          const Eigen::Vector3d& jointMaxPositionsForLegInDefaultConfiguration,
                                                                          const bool isLegInDefaultConfiguration[]);

  const JointVector& getJointMaxPositions() const;
  const JointVector& getJointMinPositions() const;
 protected:
  robotModel::RobotModel* robotModel_;
  bool isClampingTorques_;
  JointTorques jointTorques_;
  //! desired positions used in the low-level velocity control mode
  robotModel::VectorAct desPositionsInVelocityControl_;
  robotModel::VectorActM desJointModesPrevious_;

  JointVector jointPositionControlProportionalGains_;
  JointVector jointPositionControlDerivativeGains_;
  JointVector jointVelocityControlProportionalGains_;
  JointVector jointVelocityControlDerivativeGains_;
  JointTorques jointMaxTorques_;
  JointVector jointMaxPositions_;
  JointVector jointMinPositions_;
  bool isLegInDefaultConfiguration_[4];
};

} /* namespace loco */

#endif /* LOCO_JOINTCONTROLLERSTARLETH_HPP_ */
