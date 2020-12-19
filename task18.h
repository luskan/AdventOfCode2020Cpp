//
// Created by marci_000 on 18.12.2020.
//

#ifndef ADVENTOFCODE2020_TASK18_H
#define ADVENTOFCODE2020_TASK18_H

#include <deque>
#include <vector>

class task18 {
    using expr_t = std::deque<char>;
    std::vector<expr_t> rpn_expressions;
    void load(bool solve2);
    uint64_t solve();
public:
    task18();
    void solve1();
    void solve2();
};


#endif //ADVENTOFCODE2020_TASK18_H
