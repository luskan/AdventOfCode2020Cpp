//
// Created by Marcin Jędrzejewski on 13/12/2020.
//

#ifndef ADVENTOFCODE2020_TASK13_H
#define ADVENTOFCODE2020_TASK13_H

#include <vector>

class task13 {
    struct data {
        int id;
        int waitTime;
    };
    int startTimestamp;
    std::vector<data> entries;
public:
    task13();
    void solve1();
    void solve2();

    void runSolve2(uint64_t start, int id, int increment);
};


#endif //ADVENTOFCODE2020_TASK13_H
