#ifndef MAPS_EDGE_H
#define MAPS_EDGE_H

namespace maps {

template<typename T>
class Edge {
 public:
  Edge() = default;
  Edge(const Edge&) = default;
  Edge (Edge&&) noexcept = default;
  Edge& operator=(const Edge&) = default;
  Edge& operator=(Edge&&) noexcept = default;
  virtual ~Edge() = default;

  virtual bool is_directed() = 0;
  virtual T get_weight() = 0;
  virtual Edge* clone() const = 0;
};

}

#endif //MAPS_EDGE_H
