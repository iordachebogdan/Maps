#ifndef MAPS_REGION_H
#define MAPS_REGION_H

#include <vector>
#include <string>
#include <map>
#include <set>
#include "graph_utilities/proxy_graph.h"
#include "point_node.h"
#include "exceptions/maps_exceptions.h"

namespace maps {

template <typename T>
class City {
 public:
  City(const std::string&, T, T);

  std::string name;
  T x_coord, y_coord;
};

template <typename T, typename CostFunction>
class Region {
 public:
  Region(int, const std::vector<City<T>>&, bool);
  Region(const Region&);
  Region& operator=(const Region&);
  virtual ~Region() = default;

  void add_street(const std::string&, const std::string&);
  void remove_street(const std::string&, const std::string&);
  T get_distance(const std::string&, const std::string&);
  std::vector< std::string > get_cities() const;

 private:
  int city_count_;
  std::vector<PointNode<T, CostFunction>> cities_;
  std::map< std::string, int > cities_ids_;
  std::set< std::pair<int, int> > streets_;
  ProxyGraph<T> graph_;
  bool bidirectional_streets_;
};

template <typename T>
City<T>::City(const std::string &name, T x, T y) :
    name(name),
    x_coord(x),
    y_coord(y) {
}

template <typename T, typename CostFunction>
Region<T, CostFunction>::Region(int city_count,
                               const std::vector<City<T>> &cities,
                               bool bidirectional_streets) :
    city_count_(city_count),
    graph_(city_count, !bidirectional_streets),
    bidirectional_streets_(bidirectional_streets) {
  for (int i = 0; i < city_count; ++i) {
    cities_ids_[cities[i].name] = i;
    cities_.push_back(
        PointNode<T, CostFunction>(i, cities[i].x_coord, cities[i].y_coord) );
  }
}

template <typename T, typename CostFunction>
Region<T, CostFunction>::Region(const Region &rhs) :
    city_count_(rhs.city_count_),
    graph_(rhs.city_count_, !rhs.bidirectional_streets_),
    bidirectional_streets_(rhs.bidirectional_streets_),
    cities_ids_(rhs.cities_ids_),
    streets_(rhs.streets_),
    cities_(rhs.cities_){
  for (auto&& it : streets_) {
    if (it.first < it.second)
      graph_.add_edge(&cities_[it.first], &cities_[it.second]);
    else if (!bidirectional_streets_)
      graph_.add_edge(&cities_[it.first], &cities_[it.second]);
  }
};

template <typename T, typename CostFunction>
Region<T, CostFunction>& Region<T, CostFunction>::operator=(const Region &rhs) {
  city_count_ = rhs.city_count_;
  graph_ = ProxyGraph<T>(city_count_, !rhs.bidirectional_streets_);
  bidirectional_streets_ = rhs.bidirectional_streets_;
  cities_ids_ = rhs.cities_ids_;
  streets_ = rhs.streets_;
  cities_ = rhs.cities_;
  for (auto&& it : streets_) {
    if (it.first < it.second)
      graph_.add_edge(&cities_[it.first], &cities_[it.second]);
    else if (!bidirectional_streets_)
      graph_.add_edge(&cities_[it.first], &cities_[it.second]);
  }
  return *this;
}

template <typename T, typename CostFunction>
void Region<T, CostFunction>::add_street(const std::string &first,
                                         const std::string &second) {
  if (!cities_ids_.count(first) || !cities_ids_.count(first))
    throw error::bad_city();
  int id_first = cities_ids_[first];
  int id_second = cities_ids_[second];
  if (id_first == id_second)
    throw error::self_loop();
  if (streets_.find({id_first, id_second}) != streets_.end())
    throw error::duplicate_street();
  if (bidirectional_streets_ &&
      streets_.find({id_second, id_first}) != streets_.end())
    throw error::duplicate_street();

  streets_.insert({id_first, id_second});
  if (bidirectional_streets_)
    streets_.insert({id_second, id_first});

  graph_.add_edge(&cities_[id_first], &cities_[id_second]);
}

template <typename T, typename CostFunction>
void Region<T, CostFunction>::remove_street(const std::string &first,
                                            const std::string &second) {
  if (!cities_ids_.count(first) || !cities_ids_.count(first))
    throw error::bad_city();
  int id_first = cities_ids_[first];
  int id_second = cities_ids_[second];
  if (streets_.find({id_first, id_second}) == streets_.end())
    throw error::bad_street();
  streets_.erase({id_first, id_second});
  if (bidirectional_streets_)
    streets_.erase({id_second, id_first});

  graph_.remove_edge(&cities_[id_first], &cities_[id_second]);
}

template <typename T, typename CostFunction>
T Region<T, CostFunction>::get_distance(const std::string &first,
                                        const std::string &second) {
  if (!cities_ids_.count(first) || !cities_ids_.count(first))
    throw error::bad_city();
  int id_first = cities_ids_[first];
  int id_second = cities_ids_[second];
  return graph_.get_distance(id_first, id_second);
}

template <typename T, typename CostFunction>
std::vector< std::string > Region<T, CostFunction>::get_cities() const {
  std::vector< std::string > cities;
  for (auto&& it : cities_ids_)
    cities.push_back(it.first);
  return cities;
}

}

#endif //MAPS_REGION_H
