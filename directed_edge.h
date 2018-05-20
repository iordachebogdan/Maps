#ifndef MAPS_DIRECTED_EDGE_H
#define MAPS_DIRECTED_EDGE_H

#include "edge.h"
#include "node.h"

namespace maps {

template <typename T>
class DirectedEdge : public Edge<T> {
 public:
  DirectedEdge(const Node<T>*, const Node<T>*);
  DirectedEdge(const DirectedEdge&) = default;
  DirectedEdge(DirectedEdge&&) noexcept = default;
  DirectedEdge& operator=(const DirectedEdge&) = default;
  DirectedEdge& operator=(DirectedEdge&&) noexcept = default;
  virtual ~DirectedEdge() = default;

  bool is_directed() override;
  T get_weight() override;

  const Node<T>* get_from() const;
  const Node<T>* get_to() const;
 private:
  const Node<T> *from_, *to_;
};

template <typename T>
DirectedEdge<T>::DirectedEdge(const Node<T> *from, const Node<T> *to) :
    from_(from),
    to_(to) {
}

template <typename T>
bool DirectedEdge<T>::is_directed() {
  return true;
}

template <typename T>
T DirectedEdge<T>::get_weight() {
  return from_->get_distance(*to_);
}

template <typename T>
const Node<T>* DirectedEdge<T>::get_from() const {
  return from_;
}

template <typename T>
const Node<T>* DirectedEdge<T>::get_to() const {
  return to_;
}

}

#endif //MAPS_DIRECTED_EDGE_H
