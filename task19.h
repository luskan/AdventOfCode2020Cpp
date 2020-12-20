//
// Created by marci_000 on 19.12.2020.
//

#ifndef ADVENTOFCODE2020_TASK19_H
#define ADVENTOFCODE2020_TASK19_H

#include <regex>
#include <vector>
#include <string>
#include <unordered_map>

struct data {
    bool final = false;
    char c = '?';
    std::vector<std::vector<int>> rules;
};

class task19 {
    std::regex rg;
    std::vector<std::string> test_strings;
    std::unordered_map<int, data> rules;
public:
    task19();
    void solve1();
    void solve2();

    std::string build_rules(const std::unordered_map<int, data>& map, int index, int depth = 0);
};


#endif //ADVENTOFCODE2020_TASK19_H
