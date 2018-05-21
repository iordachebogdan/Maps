cmake_minimum_required(VERSION 3.9)
project(Maps)

set(CMAKE_CXX_STANDARD 11)

add_executable(Maps edge.h main.cc undirected_edge.h node.h directed_edge.h point_node.h euclidian_distance.h graph.h directed_graph.h graph_factory.h undirected_graph.h complete_graph.h tree_graph.h da_graph.h)