//
// Created by Marcin Jędrzejewski on 14/12/2020.
//

#ifndef ADVENTOFCODE2020_TASK14_H
#define ADVENTOFCODE2020_TASK14_H

#include <vector>
#include <string>

class task14 {
    struct data {
        std::string mask;
        std::vector<std::tuple<uint64_t,uint64_t>> assings;
    };
    std::vector<data> entries;
public:
    task14();
    void solve1();
    void solve2();
};


#endif //ADVENTOFCODE2020_TASK14_H
