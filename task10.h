//
// Created by marcin on 10.12.2020.
//

#ifndef ADVENTOFCODE2020_TASK10_H
#define ADVENTOFCODE2020_TASK10_H

#include <vector>

class task10 {
  std::vector<int> entries;
public:
  task10();
  void solve1();
  void solve2();

  bool computeDiffs(std::vector<int>& vector, std::vector<int>& vector1);

  u_int64_t compute(int startFrom,  std::vector<int>& diffs);

  void solve2b();
};


#endif //ADVENTOFCODE2020_TASK10_H
