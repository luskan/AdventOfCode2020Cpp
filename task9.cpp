//
// Created by marcin on 09.12.2020.
//

#include "task9.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include "utils.h"

task9::task9(bool example) {
  example_data = example;
  std::ifstream ifs(example_data ? "../data/data9_example.txt" : std::string("../") + get_relative_data_path() + "data/data9_task.txt");
  std::string line;
  while (std::getline(ifs, line)) {
    entries.push_back(std::stoull(line));
  }
}

unsigned long task9::findSolve1() {
  Timer opt_timer;
  const int preamble = example_data ? 5 : 25;
  std::vector<bool> used;
  used.resize(entries.size(), false);
  for (int n = preamble; n < entries.size(); ++n) {
    std::fill(used.begin(), used.end(), false);
    auto cur = entries[n];
    bool isOk = false;
    for (int n1 = n - preamble; n1 < n; ++n1) {
      uint32_t n1v = entries[n1];
      if (used[n1])
        continue;
      for (int n2 = n1 + 1; n2 < n; ++n2) {
        uint32_t n1v = entries[n1];
        uint32_t n2v = entries[n2];
        if (used[n2])
          continue;
        if (n1v + n2v == cur) {
          used[n1] = true;
          used[n2] = true;
          isOk = true;
          break;
        }
      }
      if (isOk)
        break;
    }
    if (!isOk) {
      return cur;
    }
  }
  return 0;
}

void task9::Solve1() {
  Timer opt_timer;
  auto res = findSolve1();
  verify_result(res, example_data ? 127ul : get_data_result<uint64_t>(9, 1));
  std::cout << " part1: " << res << std::endl;
}

unsigned long task9::findSolve2() {
  Timer opt_timer;
  uint32_t val = findSolve1();
  std::vector<uint32_t> vals;
  for (int n = 0; n < entries.size(); ++n) {
    vals.clear();
    uint32_t v1 = entries[n];
    vals.push_back(v1);
    for (int k = n + 1; k < entries.size(); ++k) {
      uint32_t v2 = entries[k];
      vals.push_back(v2);
      auto sum = std::accumulate(vals.begin(), vals.end(), 0);
      if (val < sum)
        break;
      if (val == sum) {
        std::sort(vals.begin(), vals.end());
        return vals.front() + vals.back();
      }
    }
  }
  return 0;
}

void task9::Solve2() {
  Timer opt_timer;
  auto res = findSolve2();
  verify_result(res, example_data ? 62ul : get_data_result<uint64_t>(9, 2));
  std::cout << " part2: " << res << std::endl;
}
