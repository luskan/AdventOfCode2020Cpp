//
// Created by Marcin Jędrzejewski on 13/12/2020.
//

#include "task13.h"

#include <fstream>
#include <regex>
#include <iostream>
#include "utils.h"

Task13::Task13(bool example) {
  example_data = example;
  std::ifstream ifs(example_data ? "../data/data13_example.txt" : std::string("../") + get_relative_data_path() + "data/data13_task.txt");
  std::string line;
  if (std::getline(ifs, line)) {
    startTimestamp = std::stoi(line);
  }

  const std::regex sep_rg(R"(,)");
  if (std::getline(ifs, line)) {
    std::regex_token_iterator rg_it(line.begin(), line.end(), sep_rg, -1);
    std::regex_token_iterator<std::string::iterator> rg_end;
    for (; rg_it != rg_end; ++rg_it) {
      auto v = (*rg_it).str();
      if (*rg_it != "x")
        entriesBase.push_back({std::stoi(v), 0, 0});
      else
        entriesBase.push_back({-1, 0, 0});
    }
  }
}

void Task13::Solve1() {
  Timer opt_timer;
  std::vector<data> entries(entriesBase);
  for (size_t i = 0; i < entries.size(); ++i) {
    int busId = entries[i].id;
    if (busId == -1)
      continue;
    int time1 = startTimestamp % busId;
    if (time1 == 0) {
      entries[i].waitTime = 0;
    } else {
      entries[i].waitTime = busId - time1;
    }
  }
  entries.erase(std::remove_if(entries.begin(), entries.end(), [](auto &it) { return it.id < 0; }), entries.end());
  auto it = std::min_element(entries.begin(), entries.end(),
                             [](const auto &el1, const auto &el2) { return el1.waitTime < el2.waitTime; });

  auto val = it->waitTime * it->id;
  verify_result(val, example_data ? 295 : get_data_result<int>(13, 1));
  std::cout << " part1: result = " << val << std::endl;
}

void Task13::Solve2() {
  Timer opt_timer;
  auto ts = findSolution2();

  verify_result(ts, example_data ? 1068781ull : get_data_result<uint64_t>(13, 2));
  std::cout << " part2: result = " << ts << std::endl;
}

uint64_t Task13::findSolution2() {
  std::vector<data> entries(entriesBase);
  uint64_t ts = 0;
  int add = entries[0].id;
  int lastIndex = 1;
  while (true) {
    for (size_t i = lastIndex; i < entries.size(); i += 1) {
      int curId = entries[i].id;
      if (curId == -1)
        continue;

      if ((ts + i) % curId != 0)
        break;

      if (i == entries.size() - 1)
        return ts;

      // Use higher increment (add variable) to speed up iterations.
      // Also skip (update lastIndex) to next bus.
      auto lastTS = entries[i].lastTsWithMatch;
      entries[i].lastTsWithMatch = ts;
      if (lastTS != 0) {
        int newAdd = ts - lastTS;
        if (newAdd > add) {
          lastIndex = i;
          add = newAdd;
        }
      }
    }

    ts += add;
  }
}
