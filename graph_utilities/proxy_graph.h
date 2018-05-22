#ifndef MAPS_PROXY_GRAPH_H
#define MAPS_PROXY_GRAPH_H

#include "graph_factory.h"

namespace maps {

template <typename T>
class ProxyGraph : public Graph<T> {
 public:
  ProxyGraph(int, bool);
  ProxyGraph(const ProxyGraph&);
  ProxyGraph(ProxyGraph&&) noexcept;
  ProxyGraph& operator=(const ProxyGraph&);
  ProxyGraph& operator=(ProxyGraph&&) noexcept;
  virtual ~ProxyGraph();

  bool is_directed() const override;
  T get_distance(int, int) const override;

  void add_edge(const Node<T>*, const Node<T>*);
  void remove_edge(const Node<T>*, const Node<T>*);
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
ProxyGraph<T>::ProxyGraph(const ProxyGraph &rhs) :
    node_count_(rhs.node_count_),
    real_graph_(nullptr),
    is_directed_(rhs.is_directed_),
    changed_(true) {
  for (auto&& it : rhs.edges_)
    edges_.push_back(it->clone());
}

template <typename T>
ProxyGraph<T>::ProxyGraph(ProxyGraph &&rhs) noexcept :
    node_count_(rhs.node_count_),
    real_graph_(rhs.real_graph_),
    is_directed_(rhs.is_directed_),
    changed_(rhs.changed_) {
  edges_ = std::move(rhs.edges_);
  rhs.real_graph_ = nullptr;
}

template <typename T>
ProxyGraph<T>& ProxyGraph<T>::operator=(const ProxyGraph &rhs) {
  if (&rhs == this)
    return *this;
  node_count_ = rhs.node_count_;
  if (real_graph_)
    delete real_graph_;
  real_graph_ = nullptr;
  is_directed_ = rhs.is_directed_;
  changed_ = true;
  for (auto&& it : edges_)
    delete it;
  for (auto&& it : rhs.edges_)
    edges_.push_back(it->clone());
  return *this;
}

template <typename T>
ProxyGraph<T>& ProxyGraph<T>::operator=(ProxyGraph &&rhs) noexcept {
  if (&rhs == this)
    return *this;
  node_count_ = rhs.node_count_;
  real_graph_ = rhs.real_graph_;
  rhs.real_graph_ = nullptr;
  is_directed_ = rhs.is_directed_;
  changed_ = rhs.changed_;
  for (auto&& it : edges_)
    delete it;
  edges_ = std::move(rhs.edges_);
  return *this;
}

template <typename T>
ProxyGraph<T>::~ProxyGraph() {
  if (real_graph_)
    delete real_graph_;
  for (auto&& it : edges_)
    delete it;
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
void ProxyGraph<T>::add_edge(const Node<T> *first, const Node<T> *second) {
  changed_ = true;
  if (is_directed_)
    edges_.push_back(new DirectedEdge<T>(first, second));
  else
    edges_.push_back(new UndirectedEdge<T>(first, second));
}

template <typename T>
void ProxyGraph<T>::remove_edge(const Node<T> *first, const Node<T> *second) {
  changed_ = true;
  for (auto it = edges_.begin(); it != edges_.end(); ++it) {
    if (is_directed_) {
      auto edge = dynamic_cast<DirectedEdge<T>*>(*it);
      if (edge->get_from() == first && edge->get_to() == second) {
        delete *it;
        edges_.erase(it);
        return;
      }
    }

    if (!is_directed_) {
      auto edge = dynamic_cast<UndirectedEdge<T>*>(*it);
      if ((edge->get_first() == first && edge->get_second() == second) ||
          (edge->get_second() == first && edge->get_first() == second)) {
        delete *it;
        edges_.erase(it);
        return;
      }
    }
  }
}

}

#endif //MAPS_PROXY_GRAPH_H
