//
// Created by marci_000 on 27.12.2020.
//

#ifndef ADVENTOFCODE2020_TASK23_H
#define ADVENTOFCODE2020_TASK23_H

#include <vector>
#include <algorithm>
#include <string>

template<typename T, typename Coll = std::vector<T>>
class RingQueue {
    Coll vec;
public:
    template<typename Coll>
    struct iterator {
        typename Coll* vec;
        int pos;
        iterator(Coll& vec, int pos) : vec(&vec), pos(pos) {
        }
        iterator(const iterator&) = default;
        bool operator==(const iterator& it) {
            return it.pos == pos;
        }
        T operator*() {
            return (*vec)[pos];
        }
        void operator++(int) {
            pos++;
            if (pos >= vec->size())
                pos = 0;
        }
        iterator<Coll> operator+(int i) {
            int new_pos = (pos + i) % (*vec).size();
            return iterator(*vec, new_pos);
        }
    };
    RingQueue() {
    }

    void resize(size_t count) {
        vec.resize(count);
    }

    iterator<Coll> erase(iterator<Coll>& it) {
        size_t pos_del = it.pos % vec.size();
        vec.erase(vec.begin() + pos_del);
        return iterator(vec, (pos_del % vec.size()));
    }

    // items can be positive and negative.
    void rotate(int items) {

    }

    iterator<Coll> begin() {
        return iterator(vec, 0);
    }

    void push_back(T t) {
        vec.push_back(t);
    }

    iterator<Coll> insert(iterator<Coll> it, T t) {
        vec.insert(vec.begin() + it.pos + 1, t);
        int new_pos = (it.pos + 1) % vec.size();
        return iterator(vec, new_pos);
    }

    T max_element() {
        return *std::max_element(vec.begin(), vec.end());
    }
    T min_element() {
        return *std::min_element(vec.begin(), vec.end());
    }

    iterator<Coll> end() {
        return iterator<Coll>(vec, -1);
    }

    iterator<Coll> find(T i) {
        auto it = std::find(vec.begin(), vec.end(), i);
        if (it == vec.end())
            return end();
        auto dist = (it - vec.begin());
        return iterator<Coll>(vec, dist);
    }

    std::string dump() {
        std::string s;
        for (auto n : vec) {
            if (!s.empty())
                s+=", ";
            s += std::to_string(n);
        }
        return s;
    }
};

class task23 {
    bool task_2 = false;
public:
    task23();
    void solve1();
    void solve2();
};


#endif //ADVENTOFCODE2020_TASK23_H
