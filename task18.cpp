//
// Created by marci_000 on 18.12.2020.
//

#include "task18.h"
#include <fstream>
#include <iostream>
#include <string>
#include <stack>
#include <map>
#include "utils.h"

Task18::Task18(bool example) {
  example_data = example;
}

void Task18::load(bool solve2) {
  std::fstream
      ifs(example_data ? (solve2 ? "../data/data18_example_2.txt" : std::string("../") + get_relative_data_path() + "data/data18_example.txt") : std::string("../") + get_relative_data_path() + "data/data18_task.txt");
  std::string line;
  std::stack<char> stack;
  std::map<char, int> precendence = {
      {')', 6},
      {'*', 4},
      {'+', solve2 ? 5 : 4},
      {'(', 0},
  };

  rpn_expressions.clear();
  while (std::getline(ifs, line)) {
    expr_t queue;
    for (int i = 0; i < line.size(); ++i) {
      auto c = line[i];
      if (c == ' ')
        continue;
      if (c == '(') {
        stack.push(c);
      } else if (c == ')') {
        while (stack.top() != '(') {
          char nc = stack.top();
          stack.pop();
          queue.push_back(nc);
        }
        stack.pop();
      } else if (precendence.contains(c)) {
        while (!stack.empty() && precendence[c] <= precendence[stack.top()]) {
          queue.push_back(stack.top());
          stack.pop();
        }
        stack.push(c);
      } else if (c >= '0' && c <= '9') {
        queue.push_back(c);
      } else {
        throw "Invalid input!";
      }
    }
    while (!stack.empty()) {
      queue.push_back(stack.top());
      stack.pop();
    }
    rpn_expressions.push_back(std::move(queue));
  }
}

uint64_t Task18::solve() {
  uint64_t total = 0;
  for (auto eq : rpn_expressions) {
    std::stack<uint64_t> stack;
    for (char c : eq) {
      if (c == '+' || c == '*') {
        uint64_t right = stack.top();
        stack.pop();
        uint64_t left = stack.top();
        stack.pop();
        if (c == '+')
          stack.push(left + right);
        if (c == '*')
          stack.push(left * right);
      } else
        stack.push(c - '0');
    }
    total += stack.top();
    stack.pop();
  }
  return total;
}

void Task18::Solve1() {
  Timer opt_timer;
  load(false);
  uint64_t total = solve();

  // Example: 26+437+12240+13632=26335
  verify_result(total, example_data ? 26335ull : get_data_result<uint64_t>(18, 1));
  std::cout << " part1: total = " << total << std::endl;
}

void Task18::Solve2() {
  Timer opt_timer;
  load(true);
  uint64_t total = solve();

  // Example: 51+46+1445+669060+23340=693942
  verify_result(total, example_data ? 693942ull : get_data_result<uint64_t>(18, 2));
  std::cout << " part2: total = " << total << std::endl;
}
