#ifndef MAPS_GRAPH_EXCEPTIONS_H
#define MAPS_GRAPH_EXCEPTIONS_H

#include <exception>

namespace maps {
namespace error {

  class no_path : public std::exception {
    virtual const char* what() const throw() {
      return "Destination can't be accessed from source";
    }
  };

class unrecognised_graph_type : public std::exception {
  virtual const char* what() const throw() {
    return "This type of graph is unrecognized";
  }
};

}
}

#endif //MAPS_GRAPH_EXCEPTIONS_H
