cmake_minimum_required(VERSION 3.9)
project(Maps)

set(CMAKE_CXX_STANDARD 11)

add_executable(Maps graph_utilities/edge.h main.cc graph_utilities/undirected_edge.h graph_utilities/node.h graph_utilities/directed_edge.h point_node.h euclidian_distance.h graph_utilities/graph.h graph_utilities/directed_graph.h graph_utilities/graph_factory.h graph_utilities/undirected_graph.h graph_utilities/graph_types/complete_graph.h graph_utilities/graph_types/tree_graph.h graph_utilities/graph_types/da_graph.h graph_utilities/graph_types/line_graph.h graph_utilities/proxy_graph.h region.h application.h application.cc)