//
// Created by marcin on 06.12.2020.
//

#include <fstream>
#include <iostream>
#include <string>
#include "task1.h"
#include "utils.h"
#include <stdint.h>

Task1::Task1(bool example) {
  example_data = example;
  std::ifstream ifs(example ? "../data/data1_example.txt" : std::string("../") + get_relative_data_path() + "data/data1_task.txt");
  std::string line;
  while (std::getline(ifs, line)) {
    input.push_back(std::stoi(line));
  }
}

void Task1::Solve1() {
  Timer opt_timer;
  uint64_t result = 0;
  for (size_t i = 0; i < input.size(); ++i) {
    for (size_t n = i + 1; n < input.size(); ++n) {
      int vi = input[i];
      int vn = input[n];
      if (vi + vn == 2020) {
        result = vi * vn;
      }
    }
  }
  verify_result(result, example_data ? 514579ull : get_data_result<uint64_t>(1, 1));
  std::cout << " part1: " << result << std::endl;
}

void Task1::Solve2() {
  Timer opt_timer;
  uint64_t result = 0;

  for (size_t i = 0; i < input.size(); ++i) {
    for (size_t n = i + 1; n < input.size(); ++n) {
      for (size_t k = n + 1; k < input.size(); ++k) {
        int vi = input[i];
        int vn = input[n];
        int vk = input[k];
        if (vi + vn + vk == 2020) {
          result = vi * vn * vk;
        }
      }
    }
  }

  verify_result(result, example_data ? 241861950ull : get_data_result<uint64_t>(1, 2));
  std::cout << " part2: " << result << std::endl;
}

