//
// Created by marcin on 08.12.2020.
//

#ifndef ADVENTOFCODE2020_TASK8_H
#define ADVENTOFCODE2020_TASK8_H

#include <vector>
#include <string>

class Task8 {
  struct CodeLine {
    std::string instruction;
    int arg;
    int count;
  };
  std::vector<CodeLine> code;
  bool example_data;

  int ComputeSolve1();
  int ComputeSolve2();
 public:
  Task8(bool example);
  void Solve1();
  void Solve2();
};

#endif //ADVENTOFCODE2020_TASK8_H
