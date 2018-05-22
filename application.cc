#include "application.h"

namespace maps {

Application::~Application() {
  for (auto&& it : regions_)
    delete it.second;
}

void Application::run() {
  help_menu();
  std::string command;
  while (true) {
    getline(std::cin, command);
    if (command == "exit") {
      return;
    }
    if (command == "help")
      help_menu();
    else if (command == "add_region")
      add_region();
    else if (command == "rm_region")
      remove_region();
    else if (command == "add_street")
      add_street();
    else if (command == "rm_street")
      remove_street();
    else if (command == "get_dist")
      get_distance();
    else if (command == "ls_regions")
      list_regions();
    else if (command == "ls_cities")
      list_cities();
    else
      std::cout << "Invalid command\n";
  }
}

void Application::help_menu() {
  std::cout << "-------------------------------------\n";
  std::cout << "You can use either of these commands\n";
  std::cout << "help --display help menu\n";
  std::cout << "add_region --create a new region\n";
  std::cout << "rm_region --remove an existing region\n";
  std::cout << "add_street --add a new street to a region\n";
  std::cout << "rm_street --remove an existing street from a region\n";
  std::cout << "get_dist --get distance between two cities from a region\n";
  std::cout << "ls_regions --list regions\n";
  std::cout << "ls_cities --list cities of a region\n";
  std::cout << "-------------------------------------\n\n\n";
}

void Application::add_region() {
  std::string name;
  int city_count;
  std::set< std::string > cities;
  std::cout << "Enter name of new region:\n";
  getline(std::cin, name);
  if (regions_.count(name)) {
    std::cout << "This region already exists --exiting command--\n";
    return;
  }

  bool bidirec_streets;
  std::cout << "Are the streets bidirectional? (y/n)\n";
  std::string s; getline(std::cin, s);
  if (s != "y" && s != "n") {
    std::cout << "Invalid answer --exiting command--\n";
    return;
  }
  bidirec_streets = (s == "y");

  std::cout << "Enter number of cities:\n";
  std::cin >> city_count;
  std::cin.get();
  if (city_count <= 0) {
    std::cout << "Not a valid number --exiting command--\n";
    return;
  }

  std::string city_name;
  std::vector< City<double> > cities_vec;
  for (int i = 0; i < city_count; ++i) {
    std::cout << "Enter name of the city #" << i + 1 << ": ";
    getline(std::cin, city_name);
    if (cities.find(city_name) != cities.end()) {
      std::cout << "This city already exists\n";
      i--;
      continue;
    }
    double x, y;
    std::cout << "Enter coordinates of the city #" << i + 1 << '\n';
    std::cin >> x >> y;
    std::cin.get();
    cities.insert(city_name);
    cities_vec.push_back(City<double>(city_name, x, y));
  }

  regions_[name] = new Region<double, EuclidianDistance<double>>
      (city_count, cities_vec, bidirec_streets);
}

void Application::remove_region() {
  std::string name;
  std::cout << "What region do you want removed?\n";
  getline(std::cin, name);
  if (!regions_.count(name)) {
    std::cout << "Region doesn't exist\n";
    return;
  }

  delete regions_[name];
  regions_.erase(regions_.find(name));
  std::cout << "Region removed\n";
}

void Application::add_street() {
  std::string region;
  std::string city1, city2;
  std::cout << "Enter name of region:\n";
  getline(std::cin, region);
  if (!regions_.count(region)) {
    std::cout << "Region doesn't exist\n";
    return;
  }
  std::cout << "Enter name of first city:\n";
  getline(std::cin, city1);
  std::cout << "Enter name of second city:\n";
  getline(std::cin, city2);

  regions_[region]->add_street(city1, city2);
  std::cout << "Street added\n";
}

void Application::remove_street() {
  std::string region;
  std::string city1, city2;
  std::cout << "Enter name of region:\n";
  getline(std::cin, region);
  if (!regions_.count(region)) {
    std::cout << "Region doesn't exist\n";
    return;
  }
  std::cout << "Enter name of first city:\n";
  getline(std::cin, city1);
  std::cout << "Enter name of second city:\n";
  getline(std::cin, city2);

  regions_[region]->remove_street(city1, city2);
  std::cout << "Street added\n";
}

void Application::get_distance() {
  std::string region;
  std::string city1, city2;
  std::cout << "Enter name of region:\n";
  getline(std::cin, region);
  if (!regions_.count(region)) {
    std::cout << "Region doesn't exist\n";
    return;
  }
  std::cout << "Enter name of first city:\n";
  getline(std::cin, city1);
  std::cout << "Enter name of second city:\n";
  getline(std::cin, city2);

  double res = regions_[region]->get_distance(city1, city2);
  std::cout << "The distance is: " << res << "\n";
}

void Application::list_regions() {
  for (auto&& it : regions_)
    std::cout << it.first << '\n';
}

void Application::list_cities() {
  std::string region;
  std::cout << "Enter name of region:\n";
  getline(std::cin, region);
  if (!regions_.count(region)) {
    std::cout << "Region doesn't exist\n";
    return;
  }
  auto cities = regions_[region]->get_cities();
  for (auto&& it : cities)
    std::cout << it << '\n';
}

}

