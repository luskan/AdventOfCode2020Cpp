//
// Created by marci_000 on 18.12.2020.
//

#ifndef ADVENTOFCODE2020_TASK18_H
#define ADVENTOFCODE2020_TASK18_H

#include <vector>
#include <memory>

class task18 {
    enum class type_t {
        None, Mul, Add, ParenOpen, Arg, ParenClose
    };
    struct Node {
        int64_t arg = 0;
        type_t type = type_t::None;
        std::shared_ptr<Node> parent;
        std::shared_ptr<Node> sub;
    };
    std::vector<std::shared_ptr<Node>> ops;
public:
    task18();
    void solve1();
    void solve2();

    int64_t solve_eq(std::shared_ptr<Node>& nod);
};


#endif //ADVENTOFCODE2020_TASK18_H
