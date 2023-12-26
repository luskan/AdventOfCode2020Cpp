//
// Created by marcin on 06.12.2020.
//
#include <fstream>
#include <iostream>
#include "task3.h"
#include <string>
#include "utils.h"

Task3::Task3(bool example) {
  example_data = example;
  std::ifstream ifs(example_data ? "../data/data3_example.txt" : std::string("../") + get_relative_data_path() + "data/data3_task.txt");
  std::string line;
  while (std::getline(ifs, line)) {
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
}

void Task3::Solve1() {
  Timer opt_timer;
  auto count = GetNumberOfTreesForSlope(3, 1);
  verify_result(count, example_data ? 7 : get_data_result<int>(3, 1));
  std::cout << " part1: total trees: " << count << std::endl;
}

void Task3::Solve2() {
  Timer opt_timer;
  int mul = 1;
  int slopes[][2] = {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};
  for (int n = 0; n < sizeof(slopes) / sizeof(slopes[0]); ++n) {
    mul *= GetNumberOfTreesForSlope(slopes[n][0], slopes[n][1]);
  }
  verify_result(mul, example_data ? 336 : get_data_result<int>(3, 2));
  std::cout << " part2: trees: " << mul << std::endl;
}

int Task3::GetNumberOfTreesForSlope(int dx, int dy) {
  int trees = 0;
  int x = 0;
  int y = 0;
  while (y < GetMaxY()) {
    x += dx;
    y += dy;
    if (y >= GetMaxY())
      break;
    if (get(x, y).isTree)
      trees++;
  }
  return trees;
}
