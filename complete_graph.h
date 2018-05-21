#ifndef MAPS_COMPLETE_GRAPH_H
#define MAPS_COMPLETE_GRAPH_H

#include "undirected_graph.h"

namespace maps {

template <typename T>
class CompleteGraph : public UndirectedGraph<T> {
 public:
  explicit CompleteGraph(int, const std::vector<Edge<T>*>&);
  CompleteGraph(const CompleteGraph&) = default;
  CompleteGraph(CompleteGraph&&) noexcept = default;
  CompleteGraph& operator=(const CompleteGraph&) = default;
  CompleteGraph& operator=(CompleteGraph&&) noexcept = default;
  virtual ~CompleteGraph() = default;

  T get_distance(int, int) const override;

 private:
  std::vector<std::vector<T>> distance_;
};

template <typename T>
CompleteGraph<T>::CompleteGraph(int node_count,
                                const std::vector<Edge<T>*>& edges) :
    UndirectedGraph<T>(node_count, edges) {
  distance_.resize(static_cast<size_t>(node_count_),
    std::vector<T>(static_cast<size_t>(node_count_)));
  adj_list_.clear();
  for (auto&& it : edges_)
    distance_[it.get_first()][it.get_second()] = it.get_weight();
  edges_.clear();
}

template <typename T>
T CompleteGraph<T>::get_distance(int id_source, int id_destination) const {
  return distance_[id_source][id_destination];
}

}

#endif //MAPS_COMPLETE_GRAPH_H
