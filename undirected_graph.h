#ifndef MAPS_UNDIRECTED_GRAPH_H
#define MAPS_UNDIRECTED_GRAPH_H

#include "graph.h"
#include <vector>
#include "undirected_edge.h"
#include <queue>

namespace maps {

template <typename T>
class UndirectedGraph : public Graph<T> {
 public:
  explicit UndirectedGraph(int, const std::vector<Edge<T>*>&);
  UndirectedGraph(const UndirectedGraph&);
  UndirectedGraph& operator=(const UndirectedGraph&);
  virtual ~UndirectedGraph() = default;

  bool is_directed() const override;
  T get_distance(int, int) const override;

 protected:
  int node_count_;
  std::vector<UndirectedEdge<T>> edges_;
  std::vector< std::vector< UndirectedEdge<T>* > > adj_list_;

  void build_adj_list_();
 private:
  class HeapComp {
   public:
    bool operator()(const std::pair<T, int>&, const std::pair<T, int>&) const;
  };
};

template <typename T>
UndirectedGraph<T>::UndirectedGraph(int node_count,
                                    const std::vector<Edge<T> *>& edges) :
    node_count_(node_count) {
  for (auto&& it : edges)
    if (it->is_directed())
      throw "edges don't match graph type";
  edges_.reserve(edges.size());
  for (auto&& it : edges) {
    edges_.push_back(*dynamic_cast<UndirectedEdge<T>*>(it));
  }
  build_adj_list_();
}

template <typename T>
UndirectedGraph<T>::UndirectedGraph(const UndirectedGraph &rhs) :
    node_count_(rhs.node_count_),
    edges_(rhs.edges_) {
  build_adj_list_();
}

template <typename T>
UndirectedGraph& UndirectedGraph<T>::operator=(const UndirectedGraph &rhs) {
  if (&rhs != this) {
    node_count_ = rhs.node_count_;
    edges_ = rhs.edges_;
    build_adj_list_();
  }
  return *this;
}

template <typename T>
bool UndirectedGraph<T>::is_directed() const {
  return false;
}

template <typename T>
T UndirectedGraph<T>::get_distance(int id_source, int id_destination) const {
  std::vector< T > distance(static_cast<size_t>(node_count_));
  std::vector< bool > is_inf_distance(static_cast<size_t>(node_count_), true);
  std::vector< bool > is_fixed(static_cast<size_t>(node_count_), false);
  std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>,
      HeapComp> heap;
  heap.push(std::make_pair(T(), id_source));
  is_inf_distance[id_source] = false;

  while (true) {
    while (!heap.empty() && is_fixed[heap.top().second])
      heap.pop();
    if (heap.empty())
      break;
    auto curr = heap.top();
    heap.pop();

    int node = curr.second;
    T cost = curr.first;
    is_fixed[node] = true;
    for (auto&& edge : adj_list_[node]) {
      int nxt = edge->get_first()->get_id();
      if (nxt == node)
        nxt = edge->get_second()->get_id();
      if (is_inf_distance[nxt] || distance[nxt] > cost + edge->get_weight()) {
        is_inf_distance[nxt] = false;
        distance[nxt] = cost + edge->get_weight();
        heap.push(std::make_pair(distance[nxt], nxt));
      }
    }
  }

  if (is_inf_distance[id_destination])
    throw "destination can't be accessed from source";
  return distance[id_destination];
}

template <typename T>
bool UndirectedGraph<T>::HeapComp::operator()(const std::pair<T, int> &first,
                                              const std::pair<T, int>
                                                &second) const {
  return first.first > second.first;
}

template <typename T>
void UndirectedGraph<T>::build_adj_list_() {
  adj_list_.assign(static_cast<size_t>(node_count_),
                   std::vector<UndirectedEdge<T>*>());
  for (auto& it : edges_) {
    adj_list_[it.get_first()->get_id()].push_back(&it);
    adj_list_[it.get_second()->get_id()].push_back(&it);
  }
}

}

#endif //MAPS_UNDIRECTED_GRAPH_H
