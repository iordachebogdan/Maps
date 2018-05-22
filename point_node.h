#ifndef MAPS_POINT_NODE_H
#define MAPS_POINT_NODE_H

#include "graph_utilities/node.h"

namespace maps {

template <typename T, typename CostFunction>
class PointNode : public Node<T> {
 public:
  PointNode(int, const T&, const T&);
  PointNode(const PointNode&) = default;
  PointNode(PointNode&&) noexcept = default;
  PointNode& operator=(const PointNode&) = default;
  PointNode& operator=(PointNode&&) noexcept = default;
  virtual ~PointNode() = default;

  const T& get_x() const;
  const T& get_y() const;

  T get_distance(const Node<T>&) const override;
 private:
  T x_, y_;
  static CostFunction cost_function_;
};

template <typename T, typename CostFunction>
CostFunction PointNode<T, CostFunction>::cost_function_;

template <typename T, typename CostFunction>
PointNode<T, CostFunction>::PointNode(int id, const T &x, const T &y) :
    Node<T>(id),
    x_(x),
    y_(y) {
};

template <typename T, typename CostFunction>
T PointNode<T, CostFunction>::get_distance(const Node<T> &oth) const {
  const PointNode<T, CostFunction>* oth_ptr;
  if (!(oth_ptr = dynamic_cast< const PointNode<T, CostFunction>* >(&oth))) {
    throw "the nodes between the distance is computed have to be of same type";
  }
  return cost_function_(*this, *oth_ptr);
}

template <typename T, typename CostFunction>
const T& PointNode<T, CostFunction>::get_x() const {
  return x_;
}

template <typename T, typename CostFunction>
const T& PointNode<T, CostFunction>::get_y() const {
  return y_;
}

}

#endif //MAPS_POINT_NODE_H
