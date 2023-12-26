//
// Created by marcin on 06.12.2020.
//

#include "Task6.h"

#include <fstream>
#include <set>
#include <iostream>
#include <algorithm>
#include "utils.h"

Task6::Task6(bool example) {
  example_data = example;
  std::ifstream ifs(example_data ? "../data/data6_example.txt" : std::string("../") + get_relative_data_path() + "data/data6_task.txt");
  std::string line;
  GroupData gd;
  while (std::getline(ifs, line)) {
    if (line.size() == 0) {
      groups.push_back(gd);
      gd.clear();
      continue;
    }
    gd.push_back(line);
  }
  groups.push_back(gd);
}

void Task6::Solve1() {
  Timer opt_timer;
  int total = 0;
  for (size_t n = 0; n < groups.size(); ++n) {
    std::string uni = computeUnique(groups[n]);
    total += uni.size();
  }

  verify_result(total, example_data ? 11 : get_data_result<int>(6, 1));
  std::cout << " part1: total = " << total << std::endl;
}

void Task6::Solve2() {
  Timer opt_timer;
  int total = 0;
  for (size_t n = 0; n < groups.size(); ++n) {
    std::string uni = computeUnique2(groups[n]);
    total += uni.size();
  }

  verify_result(total, example_data ? 6 : get_data_result<int>(6, 2));
  std::cout << " part2: total = " << total << std::endl;
}

std::string Task6::computeUnique(std::vector<std::string> &v) {
  std::set<char> s;
  for (size_t i = 0; i < v.size(); i++) {
    for (size_t k = 0; k < v[i].size(); ++k) {
      s.insert(v[i][k]);
    }
  }
  std::string res;
  for (auto c : s)
    res += c;
  std::sort(res.begin(), res.end());
  return res;
}

std::string Task6::computeUnique2(std::vector<std::string> &v) {
  std::vector<std::vector<char>> vecs;
  for (size_t i = 0; i < v.size(); i++) {
    std::vector<char> cur;
    for (size_t k = 0; k < v[i].size(); ++k) {
      cur.push_back(v[i][k]);
    }
    std::sort(cur.begin(), cur.end());
    auto last = std::unique(cur.begin(), cur.end());
    cur.erase(last, cur.end());
    vecs.push_back(cur);
  }

  std::vector<char> intersection = vecs[0];
  if (vecs.size() > 1) {
    for (size_t i = 1; i < vecs.size(); ++i) {
      std::vector<char> newIntersection;
      std::set_intersection(
          intersection.begin(), intersection.end(),
          vecs[i].begin(), vecs[i].end(),
          std::back_inserter(newIntersection)
      );
      intersection = newIntersection;
    }
  }

  std::string res;
  for (auto c : intersection)
    res += c;
  std::sort(res.begin(), res.end());
  return res;
}
