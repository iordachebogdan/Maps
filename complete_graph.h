#ifndef MAPS_COMPLETE_GRAPH_H
#define MAPS_COMPLETE_GRAPH_H

#include "undirected_graph.h"

namespace maps {

template <typename T>
class CompleteGraph : public UndirectedGraph<T> {
  typedef Edge<T>* EdgePtr;
 public:
  explicit CompleteGraph(int, const std::vector<EdgePtr>&);
  CompleteGraph(const CompleteGraph&) = default;
  CompleteGraph(CompleteGraph&&) noexcept = default;
  CompleteGraph& operator=(const CompleteGraph&) = default;
  CompleteGraph& operator=(CompleteGraph&&) noexcept = default;
  virtual ~CompleteGraph() = default;

  T get_distance(int, int) const override;

  static bool recognize(int, const std::vector<EdgePtr>&);

 private:
  std::vector<std::vector<T>> distance_;
};

template <typename T>
CompleteGraph<T>::CompleteGraph(int node_count,
                                const std::vector<EdgePtr>& edges) :
    UndirectedGraph<T>(node_count, edges) {
  distance_.resize(static_cast<size_t>(this->node_count_),
    std::vector<T>(static_cast<size_t>(this->node_count_)));
  this->adj_list_.clear();
  for (auto&& it : this->edges_)
    distance_[it.get_first()->get_id()][it.get_second()->get_id()] =
        it.get_weight();
  this->edges_.clear();
}

template <typename T>
T CompleteGraph<T>::get_distance(int id_source, int id_destination) const {
  return distance_[id_source][id_destination];
}

template <typename T>
bool CompleteGraph<T>::recognize(int node_count,
                                 const std::vector<EdgePtr> &edges) {
  for (auto&& it : edges)
    if (it->is_directed())
      return false;
  std::vector< std::vector<bool> > has_edge(static_cast<size_t>(node_count),
    std::vector<bool>(static_cast<size_t>(node_count, false)));
  for (auto&& it : edges) {
    UndirectedEdge<T>* edge = dynamic_cast<UndirectedEdge<T>*>(it);
    has_edge[edge->get_first()->get_id()][edge->get_second()->get_id()] = true;
    has_edge[edge->get_second()->get_id()][edge->get_first()->get_id()] = true;
  }
  for (int first = 0; first < node_count; ++first)
    for (int second = 0; second < node_count; ++second)
      if (first != second && !has_edge[first][second])
        return false;
  return true;
}

}

#endif //MAPS_COMPLETE_GRAPH_H
