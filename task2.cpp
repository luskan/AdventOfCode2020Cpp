//
// Created by marcin on 06.12.2020.
//

#include <fstream>
#include <iostream>
#include <regex>
#include <algorithm> // For std::count
#include "task2.h"
#include "utils.h"

Task2::Task2(bool example) {
  example_data = example;
  std::ifstream ifs(example_data ? "../data/data2_example.txt" : std::string("../") + get_relative_data_path() + "data/data2_task.txt");
  std::string line;

  // 9-12 q: qqqxhnhdmqqqqjz
  std::regex regLine{R"((\d+)-(\d+) (\w): (\w+))",
      std::regex_constants::ECMAScript | std::regex_constants::icase};

  while (std::getline(ifs, line)) {
    std::smatch m;
    if (!std::regex_search(line, m, regLine))
      throw "Wrong parsing!";
    if (m.size() != 5)
      throw "Wrong number of fields parsed!";

    PasswordEntry pe;
    pe.min = std::stoi(m[1]);
    pe.max = std::stoi(m[2]);
    pe.c = m[3].str()[0];
    pe.password = m[4];
    entries.push_back(pe);
  }
}

void Task2::Solve1() {
  Timer opt_timer;
  int valid = 0;
  for (auto &pe : entries) {
    int count = std::count(pe.password.begin(), pe.password.end(), pe.c);
    if (count >= pe.min && count <= pe.max)
      valid++;
  }
  verify_result(valid, example_data ? 2 : get_data_result<int>(2, 1));
  std::cout << " part1: valid passwords: " << valid << std::endl;
}

void Task2::Solve2() {
  Timer opt_timer;
  int valid = 0;
  for (auto &pe : entries) {
    int pos1 = pe.min - 1;
    int pos2 = pe.max - 1;
    if (pos1 >= pe.password.size())
      continue;
    if (pos2 >= pe.password.size())
      continue;

    int check1 = pe.password[pos1] == pe.c ? 1 : 0;
    int check2 = pe.password[pos2] == pe.c ? 1 : 0;
    if (check1 + check2 == 1)
      valid++;
  }

  verify_result(valid, example_data ? 1 : get_data_result<int>(2, 2));
  std::cout << " part2: valid passwords: " << valid << std::endl;
}
