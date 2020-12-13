//
// Created by Marcin Jędrzejewski on 13/12/2020.
//

#include "task13.h"

#include <fstream>
#include <regex>
#include <iostream>
#include <chrono>
#include <thread>

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
                entries.push_back({std::stoi(v), 0, 0});
            else
                entries.push_back({-1, 0, 0});
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
    auto ts = findSolution2();
    //accepted: 803025030761664
    std::cout << "Found: " << ts <<std::endl;
}

uint64_t task13::findSolution2() {
    uint64_t ts = 0;
    int add = entries[0].id;
    int lastIndex = 1;
    while(true) {
        for (size_t i = lastIndex; i < entries.size(); i+=1) {
            int curId = entries[i].id;
            if (curId == -1)
                continue;

            if ((ts + i) % curId != 0)
                break;

            if (i == entries.size() - 1)
                return ts;

            // Use higher increment (add variable) to speed up iterations.
            // Also skip (update lastIndex) to next bus.
            auto lastTS = entries[i].lastTsWithMatch;
            entries[i].lastTsWithMatch = ts;
            if (lastTS != 0) {
                int newAdd = ts - lastTS;
                if (newAdd > add) {
                    lastIndex = i;
                    add = newAdd;
                }
            }
        }

        ts += add;
    }
}
