//
// Created by Marcin Jędrzejewski on 15/12/2020.
//

#ifndef ADVENTOFCODE2020_TASK15_H
#define ADVENTOFCODE2020_TASK15_H

#include <vector>

class Task15 {
  bool example_data;
  int findSolution(std::vector<int>, int);
 public:
  Task15(bool example);
  void solve1();
  void solve2();
};

#endif //ADVENTOFCODE2020_TASK15_H
