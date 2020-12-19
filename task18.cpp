//
// Created by marci_000 on 18.12.2020.
//

#include "task18.h"
#include <fstream>
#include <iostream>
#include <string>
#include <stack>
#include <map>

task18::task18() {
}

void task18::load(bool solve2) {
    std::fstream ifs("../data18.txt");
    std::string line;
    std::stack<char> stack;
    std::map<char, int> precendence = {
            {')', 6},
            {'*', 4},
            {'+', solve2 ? 5 : 4},
            {'(', 0},
    };

    rpn_expressions.clear();
    while(std::getline(ifs, line)) {
        expr_t queue;
        for (int i = 0; i < line.size(); ++i) {
            auto c = line[i];
            if (c == ' ')
                continue;
            if (c == '(') {
                stack.push(c);
            }
            else if (c == ')') {
              while(stack.top() != '(') {
                  char nc = stack.top();
                  stack.pop();
                  queue.push_back(nc);
              }
              stack.pop();
            }
            else if (precendence.contains(c)) {
                while (!stack.empty() && precendence[c] <= precendence[stack.top()]) {
                    queue.push_back(stack.top());
                    stack.pop();
                }
                stack.push(c);
            }
            else if (c >= '0' && c <= '9') {
               queue.push_back(c);
            }
            else {
                throw "Invalid input!";
            }
        }
        while(!stack.empty()) {
            queue.push_back(stack.top());
            stack.pop();
        }
        rpn_expressions.push_back(std::move(queue));
    }
}

uint64_t task18::solve() {
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
            }
            else
                stack.push(c - '0');
        }
        total += stack.top();
        stack.pop();
    }
    return total;
}

void task18::solve1() {
    load(false);
    uint64_t total = solve();

    // correct : 53660285675207
    std::cout << "Solve 1 - total: " << total << std::endl;
}

void task18::solve2() {
    load(true);
    uint64_t total = solve();

    // correct : 53660285675207
    std::cout << "Solve 2 - Total: " << total << std::endl;
}
