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
public:
  Task8();
  void solve1();
  void solve2();
};


#endif //ADVENTOFCODE2020_TASK8_H
