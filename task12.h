//
// Created by Marcin Jędrzejewski on 12/12/2020.
//

#ifndef ADVENTOFCODE2020_TASK12_H
#define ADVENTOFCODE2020_TASK12_H

#include <vector>
#include <string>
class Task12 {
  struct data {
    char type;
    int arg;
  };
  std::vector<data> entries;

  bool example_data;
 public:
  Task12(bool example);
  void Solve1();
  void Solve2();
};

#endif //ADVENTOFCODE2020_TASK12_H
