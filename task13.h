//
// Created by Marcin Jędrzejewski on 13/12/2020.
//

#ifndef ADVENTOFCODE2020_TASK13_H
#define ADVENTOFCODE2020_TASK13_H

#include <vector>
#include <cstdint>

class Task13 {
  struct data {
    int id;
    int waitTime;
    uint64_t lastTsWithMatch;
  };
  int startTimestamp;
  std::vector<data> entriesBase;
  bool example_data;
 public:
  Task13(bool example);
  void Solve1();
  void Solve2();

  uint64_t findSolution2();
};

#endif //ADVENTOFCODE2020_TASK13_H
