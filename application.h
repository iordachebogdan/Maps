#ifndef MAPS_APPLICATION_H
#define MAPS_APPLICATION_H

#include "region.h"
#include "euclidian_distance.h"
#include <iostream>

namespace maps {

class Application {
 public:
  Application() = default;
  ~Application();

  void run();

 private:
  void help_menu();
  void add_region();
  void remove_region();
  void add_street();
  void remove_street();
  void get_distance();
  void list_regions();
  void list_cities();

  std::map< std::string, Region<double, EuclidianDistance<double> >* > regions_;
};

}

#endif //MAPS_APPLICATION_H
