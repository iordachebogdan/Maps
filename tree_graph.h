#ifndef MAPS_TREE_GRAPH_H
#define MAPS_TREE_GRAPH_H

#include "undirected_graph.h"

namespace maps {

template <typename T>
class TreeGraph : public UndirectedGraph<T> {
  typedef Edge<T>* EdgePtr;
 public:
  explicit TreeGraph(int, const std::vector<EdgePtr>&);
  TreeGraph(const TreeGraph&) = default;
  TreeGraph(TreeGraph&&) noexcept = default;
  TreeGraph& operator=(const TreeGraph&) = default;
  TreeGraph& operator=(TreeGraph&&) noexcept = default;
  virtual ~TreeGraph() = default;

  T get_distance(int, int) const override;

 private:
  std::vector< int > level_;
  std::vector< T > depth_;
  std::vector< std::vector< int > > ancestors_;

  void dfs_init(int);
  void compute_ancestors();
  int lca(int, int) const;
};

template <typename T>
TreeGraph<T>::TreeGraph(int node_count, const std::vector<EdgePtr> &edges) :
    UndirectedGraph<T>(node_count, edges) {
  ancestors_.assign(1, std::vector<int>(static_cast<size_t>(node_count)));
  level_.assign(static_cast<size_t>(node_count), 0);
  depth_.assign(static_cast<size_t>(node_count), T());
  dfs_init(0);
  compute_ancestors();
}

template <typename T>
T TreeGraph<T>::get_distance(int id_source, int id_destination) const {
  return depth_[id_source] + depth_[id_destination]
         - 2 * depth_[lca(id_destination, id_source)];
}

template <typename T>
void TreeGraph<T>::dfs_init(int node) {
  for (auto&& edge : this->adj_list_[node]) {
    int nxt = edge->get_first()->get_id();
    if (nxt == node)
      nxt = edge->get_second()->get_id();

    if (nxt == ancestors_[0][node])
      continue;
    ancestors_[0][nxt] = node;
    level_[nxt] = level_[node] + 1;
    depth_[nxt] = depth_[node] + edge->get_weight();
    dfs_init(nxt);
  }
}

template <typename T>
void TreeGraph<T>::compute_ancestors() {
  for (int i = 1; (1 << i) <= this->node_count_; ++i) {
    ancestors_.push_back(
        std::vector<int>(static_cast<size_t>(this->node_count_)));
    for (int j = 0; j < this->node_count_; ++j)
      ancestors_[i][j] = ancestors_[i-1][ancestors_[i-1][j]];
  }
}

template <typename T>
int TreeGraph<T>::lca(int first, int second) const {
  if (first == second)
    return first;
  if (level_[first] < level_[second])
    std::swap(first, second);

  int step = 0;
  while ((1 << step) <= this->node_count_)
    step++;
  step--;

  int diff = level_[first] - level_[second];
  for (int i = step; i >= 0; --i) {
    if (diff < i)
      continue;
    diff -= i;
    first = ancestors_[i][first];
  }

  if (first == second)
    return first;
  for (int i = step; i >= 0; --i)
    if (ancestors_[i][first] != ancestors_[i][second]) {
      first = ancestors_[i][first];
      second = ancestors_[i][second];
    }
  return ancestors_[0][first];
}

}

#endif //MAPS_TREE_GRAPH_H
