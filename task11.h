//
// Created by marcin on 11.12.2020.
//

#ifndef ADVENTOFCODE2020_TASK11_H
#define ADVENTOFCODE2020_TASK11_H

#include <vector>
#include <set>
#include <algorithm>

class Task11 {
  using Row = std::vector<char>;
  std::vector<Row> roomBase;
  char dummy = '?';
  bool part2 = false;

  char &at(std::vector<Row> &rm, int x, int y);
  std::multiset<char> &atAround(std::vector<Row> &rm, int x, int y, std::multiset<char> &res);

  void solve();

  bool example_data;
 public:
  Task11(bool example);
  void Solve1();
  void Solve2();
};

#endif //ADVENTOFCODE2020_TASK11_H
