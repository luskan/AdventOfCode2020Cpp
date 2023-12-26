//
// Created by marci_000 on 05.01.2021.
//

#ifndef ADVENTOFCODE2020__TASK25_H_
#define ADVENTOFCODE2020__TASK25_H_

#include <cstdint>

class Task25 {
  uint64_t card_pubkey;
  uint64_t door_pubkey;
  bool example_data;
 public:
  Task25(bool example);
  void Solve1();
  void Solve2();
};

#endif //ADVENTOFCODE2020__TASK25_H_
