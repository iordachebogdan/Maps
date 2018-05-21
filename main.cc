#include "directed_edge.h"
#include "point_node.h"
#include "euclidian_distance.h"
#include <iostream>
#include "directed_graph.h"
#include "undirected_graph.h"
#include "graph_factory.h"

int main() {
  maps::PointNode<int, maps::EuclidianDistance<int>> p1(0, 2, 3), p2(1, 5, 7);
  maps::Edge<int> *edge = new maps::DirectedEdge<int>(
      static_cast<maps::Node<int>*>(&p1),
      static_cast<maps::Node<int>*>(&p2)
  );

  std::cerr << edge->get_weight() << std::endl;

  maps::PointNode<int, maps::EuclidianDistance<int>> a1(0, 0, 0), a2(1, 0, 2), a3(2, 2, 2), a4(3, 1, 1);
  std::vector< maps::Edge<int>* > edges = {
      new maps::UndirectedEdge<int>(&a1, &a2),
      new maps::UndirectedEdge<int>(&a2, &a3),
      new maps::UndirectedEdge<int>(&a1, &a4),
      new maps::UndirectedEdge<int>(&a4, &a3)
  };

  maps::Graph<int>* g = maps::GraphFactory<int>::create_graph(4, edges);
  std::cerr << g->get_distance(0, 2) << std::endl;


  return 0;
}