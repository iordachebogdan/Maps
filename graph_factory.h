#ifndef MAPS_GRAPH_FACTORY_H
#define MAPS_GRAPH_FACTORY_H

#include "graph.h"
#include "directed_graph.h"
#include "complete_graph.h"
#include "edge.h"
#include "da_graph.h"
#include <vector>
#include "tree_graph.h"
#include "line_graph.h"

namespace maps {

enum GraphTypes {
  Line,
  Tree,
  DAG,
  Complete,
  BasicDirected,
  BasicUndirected,
  Undefined
};

template <typename T>
class GraphFactory {
  typedef Edge<T>* EdgePtr;
 public:
  static Graph<T>* create_graph(int, const std::vector< EdgePtr >&);
};

template <typename T>
Graph<T>* GraphFactory<T>::create_graph(int node_count,
                                        const std::vector<EdgePtr> &edges) {
  GraphTypes type = Undefined;
  if (DirectedGraph<T>::recognize(node_count, edges)) {
    type = BasicDirected;
    if (DAGraph<T>::recognize(node_count, edges))
      type = DAG;
  }
  if (UndirectedGraph<T>::recognize(node_count, edges)) {
    type = BasicUndirected;
    if (CompleteGraph<T>::recognize(node_count, edges))
      type = Complete;
    if (TreeGraph<T>::recognize(node_count, edges)) {
      type = Tree;
      if (LineGraph<T>::recognize(node_count, edges))
        type = Line;
    }
  }

  if (type == BasicDirected) {
    return new DirectedGraph<T>(node_count, edges);
  }
  else if (type == BasicUndirected) {
    return new UndirectedGraph<T>(node_count, edges);
  }
  else if (type == Complete) {
    return new CompleteGraph<T>(node_count, edges);
  }
  else if (type == DAG) {
    return new DAGraph<T>(node_count, edges);
  }
  else if (type == Tree) {
    return new TreeGraph<T>(node_count, edges);
  }
  else if (type == Line) {
    return new LineGraph<T>(node_count, edges);
  }
  throw "nonexisting graph type";
}

}

#endif //MAPS_GRAPH_FACTORY_H
