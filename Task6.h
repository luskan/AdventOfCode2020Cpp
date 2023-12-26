//
// Created by marcin on 06.12.2020.
//

#ifndef ADVENTOFCODE2020_TASK6_H
#define ADVENTOFCODE2020_TASK6_H

#include <vector>
#include <string>

class Task6 {
  using GroupData = std::vector<std::string>;
  std::vector<GroupData> groups;
  bool example_data;
 public:
  Task6(bool example);
  void Solve1();
  void Solve2();

  std::string computeUnique(std::vector<std::string> &vector);

  std::string computeUnique2(std::vector<std::string> &vector);
};

#endif //ADVENTOFCODE2020_TASK6_H
