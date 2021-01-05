//
// Created by marcin on 06.12.2020.
//

#ifndef ADVENTOFCODE2020_TASK3_H
#define ADVENTOFCODE2020_TASK3_H

#include <vector>

struct TerrainSquare {
  bool isFree;
  bool isTree;
};
using TerrainRow = std::vector<TerrainSquare>;

class Task3 {
  std::vector<TerrainRow> terrain;
  bool example_data;
 public:
  Task3(bool example);
  TerrainSquare &get(int x, int y) {
    if (y >= terrain.size())
      throw "Y is to high!";
    TerrainRow &row = terrain[y];
    return row[x % row.size()];
  }
  int GetMaxY() const { return terrain.size(); }
  int GetNumberOfTreesForSlope(int dx, int dy);
  void Solve1();
  void Solve2();
};

#endif //ADVENTOFCODE2020_TASK3_H
