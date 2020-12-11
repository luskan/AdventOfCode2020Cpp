//
// Created by marcin on 08.12.2020.
//

#include "Task8.h"
#include <fstream>
#include <regex>
#include <iostream>

Task8::Task8() {
  std::ifstream ifs("../data8.txt");
  std::string line;
  //jmp -612
  std::regex rg(R"((\w+) ([-+][0-9]+))", std::regex_constants::ECMAScript | std::regex_constants::icase);
  while(std::getline(ifs, line)) {
    std::smatch sm;
    if (!std::regex_match(line, sm, rg))
      throw "Some wrong format!";
    CodeLine cl = {};
    cl.instruction = sm[1];
    cl.arg = std::stoi(sm[2]);
    code.push_back(cl);
  }
}

void Task8::solve1() {
  int val = 0;
  int pc = 0;
  while(true) {
    if (pc >= code.size())
      break;
    if (pc < 0)
      break;
    CodeLine &cl = code[pc];
    if (cl.count > 0) {
      std::cout << "Acc value: " << val << std::endl;
      break;
    }
    cl.count++;
    if (cl.instruction == "nop") {

    }
    else if (cl.instruction == "acc") {
      val += cl.arg;
    }
    else if (cl.instruction == "jmp") {
      pc += cl.arg;
      continue;
    }
    pc++;
  }
}

void Task8::solve2() {
  for (int n = 0; n < code.size(); n++) {
    CodeLine clorg = code[n];
    if (clorg.instruction == "nop")
      code[n].instruction = "jmp";
    else if (clorg.instruction == "jmp")
      code[n].instruction = "nop";
    else
      continue;

    int val = 0;
    int pc = 0;

    while (true) {
      if (pc >= code.size()) {
        std::cout << "Acc value: " << val << std::endl;
        //return;
        break;
      }
      if (pc < 0)
        break;
      CodeLine &cl = code[pc];

      if (cl.count > 1000) {
        break;
      }

      cl.count++;
      if (cl.instruction == "nop") {

      } else if (cl.instruction == "acc") {
        val += cl.arg;
      } else if (cl.instruction == "jmp") {
        pc += cl.arg;
        continue;
      }
      pc++;
    }
    code[n] = clorg;
    for (int n = 0; n < code.size(); n++)
      code[n].count=0;
  }
}
