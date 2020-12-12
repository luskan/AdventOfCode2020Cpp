//
// Created by Marcin Jędrzejewski on 12/12/2020.
//

#ifndef ADVENTOFCODE2020_TASK12_H
#define ADVENTOFCODE2020_TASK12_H

#include <vector>
#include <string>
class task12 {
    struct data {
        char type;
        int arg;
    };
    std::vector<data> entries;
public:
    task12();
    void solve1();
    void solve2();
};


#endif //ADVENTOFCODE2020_TASK12_H
