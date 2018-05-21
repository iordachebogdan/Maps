#ifndef MAPS_GRAPH_FACTORY_H
#define MAPS_GRAPH_FACTORY_H

#include "graph.h"
#include "directed_graph.h"
#include "edge.h"
#include <vector>

namespace maps {

enum GraphTypes {
  Line,
  Tree,
  DAG,
  Complete,
  BasicDirected,
  BasicUndirected
};

template <typename T>
class GraphFactory {
  typedef Edge<T>* EdgePtr;
 public:
  static Graph<T>* create_graph(GraphTypes, int, const std::vector< EdgePtr >&);
};

template <typename T>
Graph<T>* GraphFactory<T>::create_graph(GraphTypes type,
                                        int node_count,
                                        const std::vector<EdgePtr> &edges) {
  if (type == BasicDirected) {
    return new DirectedGraph<T>(node_count, edges);
  }
  else if (type == BasicUndirected) {
    return new UndirectedGraph<T>(node_count, edges);
  }
  return nullptr;
}

}

#endif //MAPS_GRAPH_FACTORY_H
