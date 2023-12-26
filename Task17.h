//
// Created by marci_000 on 17.12.2020.
//

#ifndef ADVENTOFCODE2020_TASK17_H
#define ADVENTOFCODE2020_TASK17_H

#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <tuple>
#include "utils.h"

class Task17 {
  using index = std::tuple<int, int, int, int>;
  using matrix_4d_t = std::unordered_map<index, char>;
  matrix_4d_t internal_cube_base;

  char &get_at(matrix_4d_t &cube, int x, int y, int z, int w) {
    index ind{x, y, z, w};
    if (!cube.contains(ind))
      cube[ind] = '.';
    return cube[ind];
  }
  bool exists(matrix_4d_t &cube, int x, int y, int z, int w) {
    index ind{x, y, z, w};
    if (!cube.contains(ind))
      return false;
    return true;
  }
  std::multiset<char> get_around_fields(matrix_4d_t &cube, int x, int y, int z, int w);
  int findSolution();

  int minx, miny, minz, minw;
  int maxx, maxy, maxz, maxw;
  bool solve_2_mode = false;
  bool example_data;
 public:
  Task17(bool example);
  void Solve1();
  void Solve2();
};

#endif //ADVENTOFCODE2020_TASK17_H
