//
// Created by marcin on 10.12.2020.
//

#ifndef ADVENTOFCODE2020_TASK10_H
#define ADVENTOFCODE2020_TASK10_H

#include <vector>
#include <cstdint>

class Task10 {
  std::vector<int> entries;
  bool example_data;

  bool computeDiffs(std::vector<int> &vector, std::vector<int> &vector1);
  uint64_t compute(int startFrom, std::vector<int> &diffs);
 public:
  Task10(bool example);
  void Solve1();
  void Solve2();
};

#endif //ADVENTOFCODE2020_TASK10_H
