/*
 * CoMOverSupportPolygonControlBase.hpp
 *
 *  Created on: Oct 7, 2014
 *      Author: dario
 */

#ifndef LOCO_COMOVERSUPPORTPOLYGONCONTROLBASE_HPP_
#define LOCO_COMOVERSUPPORTPOLYGONCONTROLBASE_HPP_

#include "tinyxml.h"

#include <Eigen/Core>
#include "loco/common/LegGroup.hpp"
#include "loco/common/TorsoBase.hpp"
#include "loco/common/TerrainModelBase.hpp"
#include "loco/common/TypeDefs.hpp"

namespace loco {

class CoMOverSupportPolygonControlBase {
 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  CoMOverSupportPolygonControlBase(LegGroup* legs);
  virtual ~CoMOverSupportPolygonControlBase();

  virtual void advance(double dt) = 0;

  /*! Gets the error vector from the center of all feet to the desired weighted location of the center of all feet in world coordinates
   * @param legs  references to the legs
   * @return error vector expressed in world frame
   */
  virtual const loco::Position& getPositionWorldToDesiredCoMInWorldFrame() const = 0;

  /*! Loads the parameters from the XML object
   * @param hParameterSet   handle
   * @return  true if all parameters could be loaded
   */
  bool loadParameters(TiXmlHandle &hParameterSet);

  /*! Stores the current paramters in the XML object
   * @param hParameterSet   handle
   * @return  true if all parameters could be loaded
   */
  bool saveParameters(TiXmlHandle &hParameterSet);

  /*! Computes an interpolated version of the two support polygon settings passed in as parameters.
   *  if t is 0, the current setting is set to supportPolygon1, 1 -> supportPolygon2, and values in between
   *  correspond to interpolated parameter set.
   * @param supportPolygon1
   * @param supportPolygon2
   * @param t   interpolation parameter
   * @return  true if successful
   */
  bool setToInterpolated(const CoMOverSupportPolygonControlBase& supportPolygon1, const CoMOverSupportPolygonControlBase& supportPolygon2, double t);

 protected:
  Position positionWorldToDesiredCoMInWorldFrame_;

  LegGroup* legs_;
  //! this is the minimum weight any leg can have... if this is zero,then the COM will try to be right at center of the support polygon [0,1]
  double minSwingLegWeight_;

  //! this is the point in the stance phase when the body should start shifting away from the leg... when the stance phase is 1, the leg weight will be minimum
  double startShiftAwayFromLegAtStancePhase_;

  //! this is the point in the swing phase when the body should start shifting back towards the leg... when the swing phase is 1, the weight is back full on the leg
  double startShiftTowardsLegAtSwingPhase_;

  double lateralOffset_;
  double headingOffset_;

};

} /* namespace loco */


#endif /* LOCO_COMOVERSUPPORTPOLYGONCONTROLBASE_HPP_ */