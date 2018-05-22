#ifndef MAPS_MAPS_EXCEPTIONS_H
#define MAPS_MAPS_EXCEPTIONS_H

#include <exception>

namespace maps {
namespace error {

class incompatible_points : public std::exception {
  virtual const char* what() const throw() {
    return
        "The points between the distance is computed have to be of same type";
  }
};

class bad_city : public std::exception {
  virtual const char* what() const throw() {
    return "City doesn't exist";
  }
};

class self_loop : public std::exception {
  virtual const char* what() const throw() {
    return "There cannot be any self-loops";
  }
};

class duplicate_street : public std::exception {
  virtual const char* what() const throw() {
    return "Can't have duplicate streets";
  }
};

class bad_street : public std::exception {
  virtual const char* what() const throw() {
    return "Street doesn't exist";
  }
};

}
}

#endif //MAPS_MAPS_EXCEPTIONS_H
