//
// Created by marci_000 on 18.12.2020.
//

#include "task18.h"
#include <fstream>
#include <iostream>
#include <string>

task18::task18() {
    std::fstream ifs("../data18.txt");
    std::string line;
    while(std::getline(ifs, line)) {
        std::shared_ptr cur_ptr = std::make_shared<Node>();
        ops.push_back(cur_ptr);
        for (int i = 0; i < line.size(); ++i) {
            auto c = line[i];
            if (c == ' ')
                continue;
            if (c == '(') {
                cur_ptr->sub = std::make_shared<Node>();
                cur_ptr->sub->type = type_t::ParenOpen;
                cur_ptr->sub->parent = cur_ptr;
                cur_ptr = cur_ptr->sub;
            }
            else if (c == ')') {
                cur_ptr->sub = std::make_shared<Node>();
                cur_ptr->sub->type = type_t::ParenClose;
                cur_ptr->sub->parent = cur_ptr;
                cur_ptr = cur_ptr->sub;
            }
            else if (c == '+') {
                cur_ptr->sub = std::make_shared<Node>();
                cur_ptr->sub->type = type_t::Add;
                cur_ptr->sub->parent = cur_ptr;
                cur_ptr = cur_ptr->sub;
            }
            else if (c == '*') {
                cur_ptr->sub = std::make_shared<Node>();
                cur_ptr->sub->type = type_t::Mul;
                cur_ptr->sub->parent = cur_ptr;
                cur_ptr = cur_ptr->sub;
            }
            else if (c >= '0' && c <= '9') {
                int n = i + 1;
                while (line[n] >= '0' && line[n] <= '9') n++;
                cur_ptr->sub = std::make_shared<Node>();
                std::string num = line.substr(i, n-i);
                if (num.size() != 1 || !(num[0] >= '0' && num[0] <= '9'))
                    throw "Invalid number";
                int val = std::stoi(num);
                cur_ptr->sub->arg = val;
                cur_ptr->sub->type = type_t::Arg;
                cur_ptr->sub->parent = cur_ptr;
                cur_ptr = cur_ptr->sub;
            }
            else {
                throw "Invalid input!";
            }
        }
    }
}

int64_t task18::solve_eq(std::shared_ptr<Node>& eq) {
    eq = eq->sub;
    int64_t sum = 0;
    type_t last_op = type_t::None;
    while (true) {
        if (eq->type == type_t::Mul) {
            last_op = eq->type;
        }
        else if (eq->type == type_t::Add) {
            last_op = eq->type;
        }
        else if (eq->type == type_t::Arg) {

            if (last_op == type_t::None)
                sum = eq->arg;
            else if (last_op == type_t::Add)
                sum += eq->arg;
            else if (last_op == type_t::Mul)
                sum *= eq->arg;
        }
        else if (eq->type == type_t::ParenOpen) {
            if (last_op == type_t::Add)
                sum += solve_eq(eq);
            else if (last_op == type_t::Mul)
                sum *= solve_eq(eq);
            else if (last_op == type_t::None)
                sum = solve_eq(eq);
        }
        else if (eq->type == type_t::ParenClose) {
            return sum;
        }
        if (!eq->sub)
            return sum;
        eq = eq->sub;
    }
    return sum;
}

void task18::solve1() {
    uint64_t total = 0;
    for (auto eq : ops) {
        auto eq_val = solve_eq(eq);;
        total += eq_val;
    }
    // correct : 53660285675207
    std::cout << "Total: " << total << std::endl;
}

void task18::solve2() {

}
