//
// Created by marcin on 08.12.2020.
//

#include "Task8.h"
#include <fstream>
#include <regex>
#include <iostream>
#include "utils.h"

Task8::Task8(bool example) {
  example_data = example;
  std::ifstream ifs(example ? "../data/data8_example.txt" : std::string("../") + get_relative_data_path() + "data/data8_task.txt");
  std::string line;
  //jmp -612
  std::regex rg(R"((\w+) ([-+][0-9]+))", std::regex_constants::ECMAScript | std::regex_constants::icase);
  while (std::getline(ifs, line)) {
    std::smatch sm;
    if (!std::regex_match(line, sm, rg))
      throw "Some wrong format!";
    CodeLine cl = {};
    cl.instruction = sm[1];
    cl.arg = std::stoi(sm[2]);
    code.push_back(cl);
  }
}

void Task8::Solve1() {
  Timer opt_timer;
  auto val = ComputeSolve1();
  verify_result(val, example_data ? 5 : get_data_result<uint64_t>(8, 1));
  std::cout << " part1: value: " << val << std::endl;
}

int Task8::ComputeSolve1() {
  Timer opt_timer;
  int val = 0;
  int pc = 0;
  while (true) {
    if (pc >= code.size())
      break;
    if (pc < 0)
      break;
    CodeLine &cl = code[pc];
    if (cl.count > 0) {
      return val;
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
  return 0;
}

void Task8::Solve2() {
  Timer opt_timer;
  auto val = ComputeSolve2();
  verify_result(val, example_data ? 8 : get_data_result<uint64_t>(8, 2));
  std::cout << " part2: value: " << val << std::endl;
}

int Task8::ComputeSolve2() {
  Timer opt_timer;
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
        return val;
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
      code[n].count = 0;
  }
  return 0;
}
