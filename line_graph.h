#ifndef MAPS_LINE_GRAPH_H
#define MAPS_LINE_GRAPH_H

#include "undirected_graph.h"

namespace maps {

template <typename T>
class LineGraph : public UndirectedGraph<T> {
  typedef Edge<T>* EdgePtr;
 public:
  explicit LineGraph(int, const std::vector<EdgePtr>&);
  LineGraph(const LineGraph&) = default;
  LineGraph(LineGraph&&) noexcept = default;
  LineGraph& operator=(const LineGraph&) = default;
  LineGraph& operator=(LineGraph&&) noexcept = default;
  virtual ~LineGraph() = default;

  T get_distance(int, int) const override;

  static bool recognize(int, const std::vector<EdgePtr>&);
 private:
  std::vector<int> position_;
  std::vector<T> partial_distance_;
};

template <typename T>
LineGraph<T>::LineGraph(int node_count, const std::vector<EdgePtr> &edges) :
    UndirectedGraph<T>(node_count, edges) {
  position_.resize(static_cast<size_t>(node_count));
  partial_distance_.resize(static_cast<size_t>(node_count));

  int start = 0;
  while (this->adj_list_[start].size() != 1)
    start++;

  position_[start] = 0;
  int prev = start, curr = this->adj_list_[start][0]->get_first()->get_id();
  int curr_edge = 0;
  if (curr == start)
    curr = this->adj_list_[start][0]->get_second()->get_id();
  for (int i = 1; i < node_count; ++i) {
    position_[curr] = i;
    partial_distance_[i] = partial_distance_[i-1]
                           + this->adj_list_[prev][curr_edge]->get_weight();
    int aux = curr;
    curr = this->adj_list_[aux][0]->get_first()->get_id();
    if (curr == aux)
      curr = this->adj_list_[aux][0]->get_second()->get_id();
    curr_edge = 0;
    if (curr == prev) {
      curr = this->adj_list_[aux][1]->get_first()->get_id();
      if (curr == aux)
        curr = this->adj_list_[aux][1]->get_second()->get_id();
      curr_edge = 1;
    }
    prev = aux;
  }
}

template <typename T>
T LineGraph<T>::get_distance(int id_source, int id_destination) const {
  return partial_distance_[std::max(position_[id_source],
                                    position_[id_destination])] -
         partial_distance_[std::min(position_[id_source],
                                    position_[id_destination])];
}

template <typename T>
bool LineGraph<T>::recognize(int node_count,
                             const std::vector<EdgePtr> &edges) {
  if (node_count == 1)
    return true;
  for (auto&& it : edges)
    if (it->is_directed())
      return false;
  std::vector< std::vector<int> > adj(static_cast<size_t>(node_count));
  for (auto&& it : edges) {
    UndirectedEdge<T>* edge = dynamic_cast<UndirectedEdge<T>*>(it);
    adj[edge->get_first()->get_id()].push_back(edge->get_second()->get_id());
    adj[edge->get_second()->get_id()].push_back(edge->get_first()->get_id());
  }

  int deg1 = 0;
  for (int i = 0; i < node_count; ++i) {
    if (adj[i].size() > 2)
      return false;
    if (adj[i].size() == 1)
      deg1++;
    if (deg1 > 2)
      return false;
  }
  if (deg1 != 2)
    return false;

  std::vector<bool> visited(static_cast<size_t>(node_count));
  std::function<void(int)> dfs = [&](int node) {
    visited[node] = true;
    for (auto&& it : adj[node])
      if (!visited[it])
        dfs(it);
  };

  dfs(0);
  for (int i = 0; i < node_count; ++i)
    if (!visited[i])
      return false;
  return true;

}

}

#endif //MAPS_LINE_GRAPH_H
