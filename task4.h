//
// Created by marcin on 06.12.2020.
//

#ifndef ADVENTOFCODE2020_TASK4_H
#define ADVENTOFCODE2020_TASK4_H

#include <string>
#include <map>
#include <vector>

class Task4 {
  using PassportData = std::map<std::string, std::string>;
  std::vector<PassportData> allPassports;
  bool example_data;
 public:
  Task4(bool example);

  void Solve1();

  int countCorrect(bool validate);

  bool isValid(std::map<std::string, std::string> &map);

  void Solve2();
};

#endif //ADVENTOFCODE2020_TASK4_H
