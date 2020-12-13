//
// Created by marcin on 06.12.2020.
//
#include <fstream>
#include <iostream>
#include "task3.h"
#include <string>

Task3::Task3() {
  std::ifstream ifs("../data3.txt");
  std::string line;
  while(std::getline(ifs, line)) {
    TerrainRow row;
    for (std::size_t n = 0; n < line.size(); ++n) {
      TerrainSquare ts = {};
      if (line[n] == '.')
        ts.isFree = true;
      if (line[n] == '#')
        ts.isTree = true;
      row.push_back(ts);
    }
    terrain.push_back(row);
  }
  std::cout << terrain.size();
}

void Task3::Solve1() {
  std::cout << "Total trees: " << GetNumberOfTreesForSlope(3,1) << std::endl;
}

void Task3::Solve2() {
  int mul = 1;
  int slopes[][2] ={ {1,1}, {3,1}, {5,1}, {7,1}, {1,2}};
  for (int n = 0; n < sizeof(slopes)/sizeof(slopes[0]); ++n) {
    mul *= GetNumberOfTreesForSlope(slopes[n][0], slopes[n][1]);
  }
  std::cout << "Trees mul: " << mul << std::endl;
}

int Task3::GetNumberOfTreesForSlope(int dx, int dy) {
  int trees = 0;
  int x = 0;
  int y = 0;
  while(y < GetMaxY()) {
    x += dx;
    y += dy;
    if (y >= GetMaxY())
      break;
    if (get(x,y).isTree)
      trees++;
  }
  return trees;
}
