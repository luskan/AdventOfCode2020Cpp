//
// Created by Marcin Jędrzejewski on 15/12/2020.
//

#include "task15.h"

#include <iostream>
#include <string>
#include <cassert>
#include <unordered_map>
#include <array>
#include "utils.h"

Task15::Task15(bool example) {
  example_data = example;
}

struct test_data {
  std::vector<int> nums;
  int turnToStop;
  int expectedResult;
  //test_data(std::vector<int> i, int t, int e) : nums(i), turnToStop(t), expectedResult(e) {}
};

void Task15::solve1() {
  /*
  Given the starting numbers 1,3,2, the 2020th number spoken is 1.
  Given the starting numbers 2,1,3, the 2020th number spoken is 10.
  Given the starting numbers 1,2,3, the 2020th number spoken is 27.
  Given the starting numbers 2,3,1, the 2020th number spoken is 78.
  Given the starting numbers 3,2,1, the 2020th number spoken is 438.
  Given the starting numbers 3,1,2, the 2020th number spoken is 1836.
  */

  if (example_data) {
    /*
     // missing to_array: xcode clang is not c++20 feature ready?
    std::array tests = std::to_array<test_data>({
                                                    {{2, 1, 3}, 2020, 10},
                                                    {{1, 2, 3}, 2020, 27},
                                                    {{2, 3, 1}, 2020, 78},
                                                    {{3, 2, 1}, 2020, 438},
                                                    {{3, 1, 2}, 2020, 1836}
                                                });*/
      std::array<test_data, 5> tests = {{
              {{2, 1, 3}, 2020, 10},
              {{1, 2, 3}, 2020, 27},
              {{2, 3, 1}, 2020, 78},
              {{3, 2, 1}, 2020, 438},
              {{3, 1, 2}, 2020, 1836}
      }};

    int n = 0;
    for (auto &t : tests) {
      auto val = findSolution(t.nums, t.turnToStop);
      verify_result(val, t.expectedResult);
      std::cout << " part1: sample" << n++ << " = " << val << std::endl;
    }
  } else {
    // correct: 536
    auto res = findSolution({1, 2, 16, 19, 18, 0}, 2020);
    verify_result(res, 536);
    std::cout << " part1: solution = " << res << std::endl;
  }
}

void Task15::solve2() {
  /*
    Given 0,3,6, the 30000000th number spoken is 175594.
    Given 1,3,2, the 30000000th number spoken is 2578.
    Given 2,1,3, the 30000000th number spoken is 3544142.
    Given 1,2,3, the 30000000th number spoken is 261214.
    Given 2,3,1, the 30000000th number spoken is 6895259.
    Given 3,2,1, the 30000000th number spoken is 18.
    Given 3,1,2, the 30000000th number spoken is 362.
     */

  if (example_data) {
    std::array<test_data, 7> tests = {{
        {{0, 3, 6}, 30000000, 175594},
        {{1, 3, 2}, 30000000, 2578},
        {{2, 1, 3}, 30000000, 3544142},
        {{1, 2, 3}, 30000000, 261214},
        {{2, 3, 1}, 30000000, 6895259},
        {{3, 2, 1}, 30000000, 18},
        {{3, 1, 2}, 30000000, 362}
    }};

    int n = 0;
    for (auto &t : tests) {
      auto val = findSolution(t.nums, t.turnToStop);
      verify_result(val, t.expectedResult);
      std::cout << " part2: sample" << n++ << " = " << val << std::endl;
    }
  } else {
    auto val = findSolution({1, 2, 16, 19, 18, 0}, 30000000);
    verify_result(val, 24065124);
    std::cout << " part2: value: " << val << std::endl;
  }
}

int Task15::findSolution(std::vector<int> nums, int turnToStop) {
  std::unordered_map<int, uint64_t> cache;
  for (size_t i = 0; i < nums.size() - 1; ++i)
    cache[nums[i]] = i;
  nums.reserve(turnToStop);
  while (true) {
    int onTop = nums.back();
    auto it = cache.find(onTop);
    if (it == cache.end()) {
      nums.push_back(0);
    } else {
      int dist = nums.size() - 1 - it->second;
      nums.push_back(dist);
    }
    cache[onTop] = nums.size() - 2;
    if (nums.size() == turnToStop)
      return nums.back();
  }
  return 0;
}
