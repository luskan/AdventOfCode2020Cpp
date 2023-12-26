//
// Created by marcin on 10.12.2020.
//

#include "task10.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include "utils.h"

Task10::Task10(bool example) {
  example_data = example;
  std::ifstream ifs(example_data ? "../data/data10_example.txt" : std::string("../") + get_relative_data_path() + "data/data10_task.txt");
  std::string line;
  while (std::getline(ifs, line)) {
    int v = std::stoi(line);
    entries.push_back(v);
  }
  std::sort(entries.begin(), entries.end());
  entries.push_back(entries.back() + 3);
}

void Task10::Solve1() {
  Timer opt_timer;
  std::vector<int> diffs;
  computeDiffs(entries, diffs);

  auto oneDiffs = std::count_if(diffs.begin(), diffs.end(), [](auto v) { return v == 1; });
  auto threeDiffs = std::count_if(diffs.begin(), diffs.end(), [](auto v) { return v == 3; });

  auto val = oneDiffs * threeDiffs;
  verify_result(val, example_data ? 220l : get_data_result<uint64_t>(10, 1));
  std::cout << " part1: value= " << val << std::endl;
}

void Task10::Solve2() {
  Timer opt_timer;
  std::vector<int> diffs;
  std::vector<int> ents = entries;
  computeDiffs(ents, diffs);

  uint64_t wtj = 1;

  std::vector<int> subDiffs;
  for (size_t i = 0; i < diffs.size(); ++i) {
    if (diffs[i] == 3)
      continue;
    subDiffs.clear();
    for (size_t k = i; k < diffs.size(); ++k) {
      if (diffs[k] == 3) {
        subDiffs.push_back(diffs[k]);
        wtj *= compute(0, subDiffs);
        i = k;
        break;
      } else {
        subDiffs.push_back(diffs[k]);
      }
    }
  }

  verify_result(wtj, example_data ? 19208ull : get_data_result<uint64_t>(10, 2));
  std::cout << " part2: value= " << wtj << std::endl;
}

bool Task10::computeDiffs(std::vector<int> &inEntries, std::vector<int> &diffs) {
  diffs.resize(inEntries.size(), 0);
  int curJoltage = 0;
  for (size_t n = 0; n < inEntries.size(); ++n) {
    auto v = inEntries[n];
    int diff = v - curJoltage;
    if (diff < 0 || diff > 3)
      return false;
    diffs[n] = diff;
    curJoltage = v;
  }
  return true;
}

uint64_t Task10::compute(int startFrom, std::vector<int> &diffs) {
  uint64_t total = 1;

  for (size_t i = startFrom; i < diffs.size() - 1; ++i) {
    int diff = diffs[i];
    int nextDiff = diffs[i + 1];
    if (diff == 1 && (nextDiff == 2 || nextDiff == 1) || diff == 2 && (nextDiff == 1)) {

      diffs[i + 1] += diff;
      diffs.erase(diffs.begin() + i);

      total += compute(i, diffs);

      diffs.insert(diffs.begin() + i, diff);
      diffs[i + 1] -= diff;
    }
  }
  return total;
}
