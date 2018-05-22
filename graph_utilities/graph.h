#ifndef MAPS_GRAPH_H
#define MAPS_GRAPH_H

namespace maps {

template <typename T>
class Graph {
 public:
  Graph() = default;
  Graph(const Graph&) = default;
  Graph(Graph&&) noexcept = default;
  Graph& operator=(const Graph&) = default;
  Graph& operator=(Graph&&) noexcept = default;
  virtual ~Graph() = default;

  virtual bool is_directed() const = 0;
  virtual T get_distance(int, int) const = 0;
};

}

#endif //MAPS_GRAPH_H
