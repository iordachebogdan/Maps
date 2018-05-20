#ifndef MAPS_EUCLIDIAN_DISTANCE_H
#define MAPS_EUCLIDIAN_DISTANCE_H

#include <cmath>
#include "point_node.h"

namespace maps {

template <typename T>
class EuclidianDistance {
 public:
  T operator()(const PointNode<T, EuclidianDistance>&,
              const PointNode<T, EuclidianDistance>&);
};

template <typename T>
T EuclidianDistance<T>::operator()(const PointNode<T, EuclidianDistance>
                                    &first,
                                   const PointNode<T, EuclidianDistance>
                                    &second) {
  T x1 = first.get_x(), y1 = first.get_y();
  T x2 = second.get_x(), y2 = second.get_y();
  return static_cast<T>(sqrt( (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) ));
}

}

#endif //MAPS_EUCLIDIAN_DISTANCE_H
