//
// Created by marcin on 06.12.2020.
//

#ifndef ADVENTOFCODE2020_TASK2_H
#define ADVENTOFCODE2020_TASK2_H

#include <vector>
#include <string>

struct PasswordEntry {
  int min;
  int max;
  char c;
  std::string password;
};

class Task2 {
  std::vector<PasswordEntry> entries;
  bool example_data;
 public:
  Task2(bool example);
  void Solve1();
  void Solve2();
};

#endif //ADVENTOFCODE2020_TASK2_H
