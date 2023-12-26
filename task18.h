//
// Created by marci_000 on 18.12.2020.
//

#ifndef ADVENTOFCODE2020_TASK18_H
#define ADVENTOFCODE2020_TASK18_H

#include <deque>
#include <vector>
#include <stdint.h>

class Task18 {
  using expr_t = std::deque<char>;
  std::vector<expr_t> rpn_expressions;
  void load(bool solve2);
  uint64_t solve();
  bool example_data;
 public:
  Task18(bool example);
  void Solve1();
  void Solve2();
};

#endif //ADVENTOFCODE2020_TASK18_H
