//
// Created by marci_000 on 27.12.2020.
//

#include "task23.h"
#include <string>
#include <iostream>
#include <cassert>
#include <algorithm>
#include "utils.h"

void testRingQueue();

Task23::Task23(bool example) {
  example_data = example;
  testRingQueue();
}

void testRingQueue() {
  RingQueue<int> rq;
  for (int n = 0; n < 4; ++n)
    rq.push_back(n);
  auto it = rq.begin();
  assert(*it == 0);
  it = it + 1;
  assert(*it == 1);
  auto it2 = it + 1;
  auto it3 = it2 + 1;
  auto it4 = it3 + 1; // circular test
  assert(*it2 == 2);
  assert(*it3 == 3);
  assert(*it4 == 0); // circular test
  auto it_3_erased = rq.erase(it3);
  assert(*it_3_erased == 0);
  auto inserted_it = rq.insert(it_3_erased + 1, 99);
  assert(*inserted_it == 99);
}

uint64_t Task23::solve(bool task_2) {

  RingQueue<uint64_t> ring;
  std::string data = example_data ? "389125467" : get_data<std::string>(23); // m

  for (auto c : data)
    ring.push_back(c - '0');

  std::vector<uint64_t> cups3(3);

  auto current_cup = ring.begin();
  auto max_element = ring.max_element();
  auto min_element = ring.min_element();

  if (task_2) {
    ring.reserve(10000000+10);
    for (uint64_t i = max_element + 1; i <= 1000000; ++i)
      ring.push_back(i);
    max_element = ring.max_element();
  }

  // Algorithm uses bruteforce - it does all required iterations, only ring collection uses
  // optimizations like caching and linked list to eliminate any bottlenecks.

  uint64_t max_iters = (task_2 ? 10 * 1000000 : 100);

  for (uint64_t iter = 0; iter < max_iters; ++iter) {

    // Take three next cups
    cups3[0] = *(current_cup + 1);
    cups3[1] = *(current_cup + 1 + 1);
    cups3[2] = *(current_cup + 1 + 2);

    // Apply task rules when choosing destination cup
    auto destination_label = *current_cup;
    if (destination_label == min_element)
      destination_label = max_element;
    else
      destination_label--;

    // Make sure destination is of correct value.
    while (true) {
      if (std::find(cups3.begin(), cups3.end(), destination_label) != cups3.end()) {
        if (destination_label == min_element)
          destination_label = max_element;
        else
          destination_label--;
      } else
        break;
    }

    // Find where to put the new cups
    auto dest_it = ring.find(destination_label);

    // Make sure the nodes are relinked, no memory operations are done (new/delete)
    // otherwise it slows down. splice is done individually on each cup, becasue
    // of the ring like structure of the container.

    auto it1 = current_cup + 1;
    auto it2 = current_cup + 2;
    auto it3 = current_cup + 3;
    auto it_end = current_cup + 4;

    ring.splice(dest_it+1, it1);
    ring.splice(it1+1, it2);
    ring.splice(it2+1, it3);

    current_cup = current_cup + 1;
  }

  auto one_it = ring.find(1);
  one_it++;
  std::string final;

  if (task_2) {
    uint64_t mul = (*one_it);
    one_it++;
    mul *= (uint64_t) (*one_it);
    return mul;
  } else {
    while (*one_it != 1) {
      final += std::to_string(*one_it);
      one_it++;
    }
    return std::stoull(final);
  }
}

void Task23::Solve1() {
  Timer opt_timer;
  auto result = solve(false);
  verify_result(result, example_data ? 67384529ull : get_data_result<uint64_t>(23, 1));
  std::cout << " part1: result = " << result << std::endl;
}

void Task23::Solve2() {
  Timer opt_timer;
  auto result = solve(true);
  verify_result(result, example_data ? 149245887792ull :  get_data_result<uint64_t>(23, 2));
  std::cout << " part2: result = " << result << std::endl;
}
