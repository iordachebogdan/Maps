#include "directed_edge.h"
#include "point_node.h"
#include "euclidian_distance.h"
#include <iostream>

int main() {
  maps::PointNode<int, maps::EuclidianDistance<int>> p1(2, 3), p2(5, 7);
  maps::Edge<int> *edge = new maps::DirectedEdge<int>(
      static_cast<maps::Node<int>*>(&p1),
      static_cast<maps::Node<int>*>(&p2)
  );

  std::cerr << edge->get_weight() << std::endl;

  return 0;
}