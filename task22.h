//
// Created by marci_000 on 26.12.2020.
//

#ifndef ADVENTOFCODE2020_TASK22_H
#define ADVENTOFCODE2020_TASK22_H

#include <deque>
#include <unordered_set>
#include <set>

class task22 {
    std::deque<int> player1_org;
    std::deque<int> player2_org;
public:
    task22();
    void solve1();
    void solve2();

    void recurive_combat(std::deque<int> &player1, std::deque<int> &player2, bool &player1wins);
};


#endif //ADVENTOFCODE2020_TASK22_H
