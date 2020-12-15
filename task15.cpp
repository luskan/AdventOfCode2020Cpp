//
// Created by Marcin Jędrzejewski on 15/12/2020.
//

#include "task15.h"

#include <iostream>
#include <string>
#include <cassert>
#include <unordered_map>

task15::task15() {

}

void task15::solve1() {
    /*
    Given the starting numbers 1,3,2, the 2020th number spoken is 1.
    Given the starting numbers 2,1,3, the 2020th number spoken is 10.
    Given the starting numbers 1,2,3, the 2020th number spoken is 27.
    Given the starting numbers 2,3,1, the 2020th number spoken is 78.
    Given the starting numbers 3,2,1, the 2020th number spoken is 438.
    Given the starting numbers 3,1,2, the 2020th number spoken is 1836.
    */

    assert(findSolution({1, 3, 2}, 2020) == 1);
    assert(findSolution({2, 1, 3}, 2020) == 10);
    assert(findSolution({1, 2, 3}, 2020) == 27);
    assert(findSolution({2, 3, 1}, 2020) == 78);
    assert(findSolution({3, 2, 1}, 2020) == 438);
    assert(findSolution({3, 1, 2}, 2020) == 1836);

    // correct: 536
    std::cout << "Solution: " << findSolution({1, 2, 16, 19, 18, 0}, 2020) << std::endl;
}

void task15::solve2() {
    /*
      Given 0,3,6, the 30000000th number spoken is 175594.
      Given 1,3,2, the 30000000th number spoken is 2578.
      Given 2,1,3, the 30000000th number spoken is 3544142.
      Given 1,2,3, the 30000000th number spoken is 261214.
      Given 2,3,1, the 30000000th number spoken is 6895259.
      Given 3,2,1, the 30000000th number spoken is 18.
      Given 3,1,2, the 30000000th number spoken is 362.
       */

    assert(findSolution({0, 3, 6}, 30000000) == 175594);
    assert(findSolution({1, 3, 2}, 30000000) == 2578);
    assert(findSolution({2, 1, 3}, 30000000) == 3544142);
    assert(findSolution({1, 2, 3}, 30000000) == 261214);
    assert(findSolution({2, 3, 1}, 30000000) == 6895259);
    assert(findSolution({3, 2, 1}, 30000000) == 18);
    assert(findSolution({3, 1, 2}, 30000000) == 362);

    // correct: 24065124
    std::cout << "Solution: " << findSolution({1, 2, 16, 19, 18, 0}, 30000000) << std::endl;
}

int task15::findSolution(std::vector<int> nums, int turnToStop) {
    std::unordered_map<int, uint64_t> cache;
    for (size_t i = 0; i < nums.size() - 1; ++i)
        cache[nums[i]] = i;
    nums.reserve(turnToStop);
    while(true) {
        int onTop = nums.back();
        auto it = cache.find(onTop);
        if (it == cache.end()) {
            nums.push_back(0);
        }
        else {
            int dist = nums.size() - 1 - it->second;
            nums.push_back(dist);
        }
        cache[onTop] = nums.size() - 2;
        if (nums.size() == turnToStop)
            return nums.back();
    }
    return 0;
}
