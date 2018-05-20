#ifndef MAPS_UNDIRECTED_EDGE_H
#define MAPS_UNDIRECTED_EDGE_H

#include "edge.h"
#include "node.h"

namespace maps {

template <typename T>
class UndirectedEdge : public Edge<T> {
 public:
  UndirectedEdge(const Node*, const Node*);
  UndirectedEdge(const UndirectedEdge&) = default;
  UndirectedEdge(UndirectedEdge&&) noexcept = default;
  UndirectedEdge& operator=(const UndirectedEdge&) = default;
  UndirectedEdge& operator=(UndirectedEdge&&) noexcept = default;
  virtual ~UndirectedEdge() = default;

  bool is_directed() override;
  T get_weight() override;
 private:
  const Node<T> *first_, *second_;
};

template <typename T>
UndirectedEdge<T>::UndirectedEdge(const Node<T> *first, const Node<T> *second) :
    first_(first),
    second_(second) {
}

template <typename T>
bool UndirectedEdge<T>::is_directed() {
  return false;
}

template <typename T>
T UndirectedEdge<T>::get_weight() {
  return first_->get_distance(*second_);
}

}

#endif //MAPS_UNDIRECTED_EDGE_H
