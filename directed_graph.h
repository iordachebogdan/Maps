#ifndef MAPS_DIRECTED_GRAPH_H
#define MAPS_DIRECTED_GRAPH_H

#include "graph.h"
#include "directed_edge.h"
#include <vector>
#include <queue>

namespace maps {

template <typename T>
class DirectedGraph : public Graph<T> {
 public:
  explicit DirectedGraph(int, const std::vector<Edge<T>*>&);
  DirectedGraph(const DirectedGraph&);
  DirectedGraph& operator=(const DirectedGraph&);
  virtual ~DirectedGraph() = default;

  bool is_directed() const override;
  T get_distance(int, int) const override;

  static bool recognize(int, const std::vector<Edge<T>*>&);
 protected:
  int node_count_;
  std::vector< DirectedEdge<T> > edges_;
  std::vector< std::vector< DirectedEdge<T>* > > adj_list_;

  void build_adj_list_();

 private:
  class HeapComp {
   public:
    bool operator()(const std::pair<T, int>&, const std::pair<T, int>&) const;
  };
};

template <typename T>
DirectedGraph<T>::DirectedGraph(int node_count, const std::vector<Edge<T>*> &edges) :
    node_count_(node_count) {
  edges_.reserve(edges.size());
  for (auto&& it : edges)
    edges_.push_back(*dynamic_cast<DirectedEdge<T>*>(it));
  build_adj_list_();
}

template <typename T>
DirectedGraph<T>::DirectedGraph(const DirectedGraph &rhs) :
    node_count_(rhs.node_count_),
    edges_(rhs.edges_) {
  build_adj_list_();
}

template <typename T>
DirectedGraph<T>& DirectedGraph<T>::operator=(const DirectedGraph &rhs) {
  if (this != &rhs) {
    node_count_ = rhs.node_count_;
    edges_ = rhs.edges_;
    build_adj_list_();
  }
  return *this;
}

template <typename T>
bool DirectedGraph<T>::is_directed() const {
  return true;
}

template <typename T>
T DirectedGraph<T>::get_distance(int id_source, int id_destination) const {
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
      int nxt = edge->get_to()->get_id();
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
bool DirectedGraph<T>::HeapComp::operator()(const std::pair<T, int> &first,
                                            const std::pair<T, int>
                                              &second) const {
  return first.first > second.first;
}

template <typename T>
void DirectedGraph<T>::build_adj_list_() {
  adj_list_.assign(static_cast<size_t>(node_count_),
                   std::vector<DirectedEdge<T>*>());
  for (auto& it : edges_)
    adj_list_[it.get_from()->get_id()].push_back(&it);
}

template <typename T>
bool DirectedGraph<T>::recognize(int node_count,
                                 const std::vector<Edge<T>*> &edges) {
  for (auto&& it : edges)
    if (!it->is_directed())
      return false;
  return true;
}

}

#endif //MAPS_DIRECTED_GRAPH_H
