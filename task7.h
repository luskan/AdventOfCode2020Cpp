//
// Created by marcin on 07.12.2020.
//

#ifndef ADVENTOFCODE2020_TASK7_H
#define ADVENTOFCODE2020_TASK7_H

#include <string>
#include <set>
#include <map>
#include <vector>

class Task7 {
  struct Bag {
    std::string color;
    std::set<std::string> bagsItCanBeIn;
    std::map<std::string, int> bagsItCanContain; // bag color -> count
  };
  std::map<std::string, Bag> bags;
  bool example_data;
  bool for_part1;
 public:
  Task7(bool example, bool part1 = true);
  void Solve1();
  void Solve2();

  std::set<std::string> findPathUp(std::string bagColor);
  std::multiset<std::string> findPathDown(std::string bagColor);
};

#endif //ADVENTOFCODE2020_TASK7_H
