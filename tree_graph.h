#ifndef MAPS_TREE_GRAPH_H
#define MAPS_TREE_GRAPH_H

#include "undirected_graph.h"

namespace maps {

template <typename T>
class TreeGraph : public UndirectedGraph<T> {
  explicit TreeGraph(int, const std::vector<Edge<T>*>&);
  TreeGraph(const TreeGraph&) = default;
  TreeGraph(TreeGraph&&) noexcept = default;
  TreeGraph& operator=(const TreeGraph&) = default;
  TreeGraph& operator=(TreeGraph&&) noexcept = default;
};

}

#endif //MAPS_TREE_GRAPH_H
