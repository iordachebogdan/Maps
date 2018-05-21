#ifndef MAPS_DAGRAPH_H
#define MAPS_DAGRAPH_H

#include "directed_graph.h"

namespace maps {

template <typename T>
class DAGraph : public DirectedGraph<T> {
  typedef Edge<T>* EdgePtr;
 public:
  explicit DAGraph(int, const std::vector<EdgePtr>&);
  DAGraph(const DAGraph&) = default;
  DAGraph(DAGraph&&) noexcept = default;
  DAGraph& operator=(const DAGraph&) = default;
  DAGraph&  operator=(DAGraph&&) = default;
  virtual ~DAGraph() = default;

  T get_distance(int, int) const override;

 private:
  std::vector<int> top_sort_;

  void get_top_sort(int, std::vector<bool>&);
};

template <typename T>
DAGraph<T>::DAGraph(int node_count, const std::vector<EdgePtr> &edges) :
    DirectedGraph<T>(node_count, edges) {
  std::vector<bool> visited(static_cast<size_t>(this->node_count_), false);
  for (int i = 0; i < this->node_count_; ++i)
    if (!visited[i])
      get_top_sort(i, visited);
}

template <typename T>
T DAGraph<T>::get_distance(int id_source, int id_destination) const {
  std::vector<T> distance(static_cast<size_t>(this->node_count_));
  std::vector<bool> is_infinite(static_cast<size_t>(this->node_count_), true);
  for (int i = 0; i < this->node_count_; ++i) {
    if (top_sort_[i] == id_destination) {
      is_infinite[id_destination] = false;
      continue;
    }

    int curr = top_sort_[i];
    for (auto&& edge : this->adj_list_[curr]) {
      int nxt = edge->get_to()->get_id();
      if (!is_infinite[nxt] &&
          (is_infinite[curr] || distance[nxt] + edge->get_weight()
                                < distance[curr])) {
        is_infinite[curr] = false;
        distance[curr] = distance[nxt] + edge->get_weight();
      }
    }

    if (curr == id_source) {
      if (is_infinite[curr])
        throw "destination can't be accessed from source";
      return distance[curr];
    }
  }

  return T();
}

template <typename T>
void DAGraph<T>::get_top_sort(int node, std::vector<bool>& visited) {
  visited[node] = true;
  for (auto&& it : this->adj_list_[node]) {
    int nxt = it->get_to()->get_id();
    if (visited[nxt])
      continue;
    get_top_sort(nxt, visited);
  }
  top_sort_.push_back(node);
}

}

#endif //MAPS_DAGRAPH_H
