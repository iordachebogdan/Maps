#ifndef MAPS_NODE_H
#define MAPS_NODE_H

namespace maps {

template <typename T>
class Node {
 public:
  Node() = default;
  Node(const Node&) = default;
  Node(Node&&) noexcept = default;
  Node& operator=(const Node&) = default;
  Node& operator=(Node&&) noexcept = default;
  virtual ~Node() = default;

  virtual T get_distance(const Node&) const = 0;
};

}

#endif //MAPS_NODE_H
