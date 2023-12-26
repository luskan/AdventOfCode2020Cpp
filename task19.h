//
// Created by marci_000 on 19.12.2020.
//

#ifndef ADVENTOFCODE2020_TASK19_H
#define ADVENTOFCODE2020_TASK19_H

#include <regex>
#include <vector>
#include <string>
#include <unordered_map>

struct data {
  bool final = false;
  char c = '?';
  std::vector<std::vector<int>> rules;
};

class Task19 {
  std::regex rg;
  std::vector<std::string> test_strings;
  std::unordered_map<int, data> rules;
  bool example_data;
  bool solve_2;
 public:
  Task19(bool example, bool s2);
  void Solve1();
  void Solve2();

  std::string build_rules(const std::unordered_map<int, data> &map, int index, int depth = 0);
};

#endif //ADVENTOFCODE2020_TASK19_H
