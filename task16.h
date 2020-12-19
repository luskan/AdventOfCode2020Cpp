//
// Created by marci_000 on 16.12.2020.
//

#ifndef ADVENTOFCODE2020_TASK16_H
#define ADVENTOFCODE2020_TASK16_H

#include <vector>
#include <string>
#include <unordered_map>

class task16 {
    struct Rule {
        std::string name;
        int range1Start;
        int range1End;
        int range2Start;
        int range2End;
    };
    std::vector<Rule> rules;
    using ticket_t = std::vector<int>;
    std::vector<ticket_t> tickets;
    ticket_t my_ticket;
    std::unordered_map<int, std::vector<Rule>> rules_cache;
public:
    task16();
    void solve1();
    void solve2();
};


#endif //ADVENTOFCODE2020_TASK16_H
