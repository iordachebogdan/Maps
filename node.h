#ifndef MAPS_NODE_H
#define MAPS_NODE_H

namespace maps {

template <typename T>
class Node {
 public:
  explicit Node(int id);
  Node(const Node&) = default;
  Node(Node&&) noexcept = default;
  Node& operator=(const Node&) = default;
  Node& operator=(Node&&) noexcept = default;
  virtual ~Node() = default;

  virtual T get_distance(const Node&) const = 0;

  int get_id() const;

 protected:
  int id_;
};

template <typename T>
Node<T>::Node(int id) : id_(id) {}

template  <typename T>
int Node<T>::get_id() const {
  return id_;
}

}

#endif //MAPS_NODE_H
