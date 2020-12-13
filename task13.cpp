//
// Created by Marcin Jędrzejewski on 13/12/2020.
//

#include "task13.h"

#include <fstream>
#include <regex>
#include <iostream>

task13::task13() {
    std::ifstream ifs("../data13.txt");
    std::string line;
    if(std::getline(ifs, line)) {
        startTimestamp = std::stoi(line);
    }

    const std::regex sep_rg(R"(,)");
    if(std::getline(ifs, line)) {
        std::regex_token_iterator rg_it(line.begin(), line.end(), sep_rg, -1);
        std::regex_token_iterator<std::string::iterator> rg_end;
        for(;rg_it != rg_end; ++rg_it) {
            auto v = (*rg_it).str();
            if (*rg_it != "x")
                entries.push_back({std::stoi(v), 0});
            else
                entries.push_back({-1, 0});
        }
    }
}

void task13::solve1() {
    for (size_t i = 0; i < entries.size(); ++i) {
        int busId = entries[i].id;
        if (busId == -1)
            continue;
        int time1 = startTimestamp%busId;
        if (time1 == 0) {
            entries[i].waitTime = 0;
        }
        else {
            entries[i].waitTime = busId - time1;
        }
    }
    auto it = std::min_element(entries.begin(), entries.end(),
                     [](const auto& el1, const auto& el2){ return el1.waitTime < el2.waitTime; });

    std::cout << it->waitTime * it->id << std::endl;
}

void task13::solve2() {
    u_int64_t ts=0;
    int id1 = entries[0].id;

    auto it = std::max_element(entries.begin(), entries.end(),
                               [](const auto& el1, const auto& el2){ return el1.id < el2.id; });
    int incts = id1;

    while(true) {
        bool foundBadOne = false;
        int maxDiff = 0;
        for (size_t i = 1; i < entries.size(); ++i) {
            int curId = entries[i].id;
            if (curId == -1)
                continue;
            u_int64_t t1 = ts / curId;
            u_int64_t t2 = t1 * curId;
            u_int64_t t3 = t2 + curId;

            int diff = t3 - ts;
            if (diff > maxDiff)
                maxDiff = diff;
            if (diff != i) {
                foundBadOne = true;
                //break;
            }
        }
        if (!foundBadOne && ts != 0) {
            std::cout << "" << ts <<std::endl;
            break;
        }
        int add = std::max(1,((maxDiff / id1) - 1)) * id1;
        ts += add;
    }
}
