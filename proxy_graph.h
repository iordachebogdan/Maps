#ifndef MAPS_PROXY_GRAPH_H
#define MAPS_PROXY_GRAPH_H

#include "graph_factory.h"

namespace maps {

template <typename T>
class ProxyGraph : public Graph<T> {
 public:
  ProxyGraph(int, bool);

  bool is_directed() const override;
  T get_distance(int, int) const override;

  void add_edge(Edge<T>*);
 private:
  int node_count_;
  mutable Graph<T>* real_graph_;
  bool is_directed_;
  mutable bool changed_;
  std::vector< Edge<T>* > edges_;
};

template <typename T>
ProxyGraph<T>::ProxyGraph(int node_count, bool is_directed) :
    node_count_(node_count),
    real_graph_(nullptr),
    is_directed_(is_directed),
    changed_(true) {
}

template <typename T>
bool ProxyGraph<T>::is_directed() const {
  return is_directed_;
}

template <typename T>
T ProxyGraph<T>::get_distance(int id_source, int id_destination) const {
  if (changed_) {
    if (real_graph_)
      delete real_graph_;
    real_graph_ = GraphFactory<T>::create_graph(node_count_, edges_);
    changed_ = false;
  }
  return real_graph_->get_distance(id_source, id_destination);
}

template <typename T>
void ProxyGraph<T>::add_edge(Edge<T> *edge) {
  changed_ = true;
  edges_.push_back(edge);
}

}

#endif //MAPS_PROXY_GRAPH_H
