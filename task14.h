//
// Created by Marcin Jędrzejewski on 14/12/2020.
//

#ifndef ADVENTOFCODE2020_TASK14_H
#define ADVENTOFCODE2020_TASK14_H

#include <vector>
#include <string>

class Task14 {
  struct data {
    std::string mask;
    std::vector<std::tuple<uint64_t, uint64_t>> assings;
  };
  std::vector<data> entries;
  bool example_data;
  bool part2;
 public:
  Task14(bool example, bool p2 = false);
  void Solve1();
  void Solve2();
};

#endif //ADVENTOFCODE2020_TASK14_H
