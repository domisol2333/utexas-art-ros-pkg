/* -*- mode: C++ -*-
 *
 *  Copyright (C) 2011 Austin Robot Technology
 *  License: Modified BSD Software License Agreement
 * 
 *  $Id$
 */

/**  @file

     Nearest backward observer interface.

     @author Michael Quinlan, Jack O'Quin

 */

#ifndef _NEAREST_BACKWARD_OBSERVER_H_
#define _NEAREST_BACKWARD_OBSERVER_H_

#include <art_observers/filter.h>
#include <art_observers/observer.h>

namespace observers
{

/** @brief Nearest backward observer class. */
class NearestBackward: public Observer 
{
public:
  NearestBackward();
  ~NearestBackward();

  virtual art_msgs::Observation
    update(const art_msgs::ArtQuadrilateral &robot_quad,
	   const art_msgs::ArtLanes &local_map,
           const art_msgs::ArtLanes &obstacles);

private:
  std::vector<float> distance_;

  MedianFilter distance_filter_;
  MeanFilter velocity_filter_;

  ros::Time prev_update_;
};

}; // namespace observers

#endif // _NEAREST_BACKWARD_OBSERVER_H_