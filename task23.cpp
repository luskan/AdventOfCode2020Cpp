//
// Created by marci_000 on 27.12.2020.
//

#include "task23.h"
#include <string>
#include <iostream>
#include <cassert>
#include <algorithm>

void testRingQueue();

task23::task23() {

    testRingQueue();
}

void testRingQueue() {
    RingQueue<int> rq;
    for (int n = 0; n < 4; ++n)
        rq.push_back(n);
    auto it = rq.begin();
    assert(*it == 0);
    it = it + 1;
    assert(*it == 1);
    auto it2 = it + 1;
    auto it3 = it2 + 1;
    auto it4 = it3 + 1; // circular test
    assert(*it2 == 2);
    assert(*it3 == 3);
    assert(*it4 == 0); // circular test
    auto it_3_erased = rq.erase(it3);
    assert(*it_3_erased == 0);
    auto inserted_it = rq.insert(it_3_erased+1, 99);
    assert(*inserted_it == 99);
}

void task23::solve1() {

    RingQueue<int> ring;
    //std::string data = "389125467"; //
    std::string data = "215694783";
    for (auto c : data)
        ring.push_back(c - '0');

    std::vector<int> cups3;
    auto current_cup = ring.begin();
    int max_element = ring.max_element();
    int min_element = ring.min_element();

    if (task_2) {
        for (int i = max_element + 1; i <= 1000000; ++i)
            ring.push_back(i);
    }

    //std::cout << "#" << 0 << " - " << ring.dump() << std::endl;

    int last_percent = -1;
    for (int iter = 0; iter < (task_2 ? 10 * 1000000 : 100); ++iter) {

        int percent = ((float)iter/(task_2 ? 10 * 1000000 : 100))*100;
        if (percent != last_percent) {
            std::cout << percent << std::endl;
            last_percent = percent;
        }

        cups3.clear();
        for (int n = 0; n < 3; ++n)
            cups3.push_back(*(current_cup + 1 + n));

        int current_cup_label = *current_cup;
        auto rm_cups = current_cup + 1;
        for (int n = 0; n < 3; ++n)
            rm_cups = ring.erase(rm_cups);

        //std::cout << "#     " << (iter + 1) << " - " << ring.dump() << std::endl;

        current_cup = ring.find(current_cup_label);

        int destination_label = current_cup_label - 1;
        if (destination_label < min_element)
            destination_label = max_element;
        while(true) {
            if (std::find(cups3.begin(), cups3.end(), destination_label) != cups3.end()) {
                destination_label--;
                if (destination_label < min_element)
                    destination_label = max_element;
            }
            else
                break;
        }

        auto dest_it = ring.find(destination_label);
        for (int n = 0; n < 3; ++n)
            dest_it = ring.insert(dest_it, cups3[n]);

        current_cup = ring.find(current_cup_label);
        current_cup = current_cup + 1;
    }

    //std::cout << "#" << (iter + 1) << " - " << ring.dump() << std::endl;
    auto one_it = ring.find(1);
    one_it++;
    std::string final;

    if (task_2) {
        uint64_t mul = (*one_it);
        one_it++;
        mul *= *one_it;
        final = std::to_string(mul);
        std::cout << "Solution2: " << final << std::endl;
    }
    else {
        while (*one_it != 1) {
            final += std::to_string(*one_it);
            one_it++;
        }
        std::cout << "Solution1: " << final << std::endl;
    }
}

void task23::solve2() {
    task_2 = true;
    solve1();
}
