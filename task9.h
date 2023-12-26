//
// Created by marcin on 09.12.2020.
//

#ifndef ADVENTOFCODE2020_TASK9_H
#define ADVENTOFCODE2020_TASK9_H

#include <vector>
#include <stdint.h>
class task9 {
  std::vector<uint64_t> entries;
  bool example_data;

  unsigned long findSolve1();
  unsigned long findSolve2();
 public:
  task9(bool example);
  void Solve1();
  void Solve2();
};

#endif //ADVENTOFCODE2020_TASK9_H
