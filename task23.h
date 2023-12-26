//
// Created by marci_000 on 27.12.2020.
//

#ifndef ADVENTOFCODE2020_TASK23_H
#define ADVENTOFCODE2020_TASK23_H

#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include <deque>
#include <list>
#include <unordered_map>

// Simple Ring collection, it is based on list and uses caching for fast finding of elements.

template<typename ItColl>
struct iterator {
  ItColl *vec;
  typename ItColl::iterator pos;
  iterator() : vec(nullptr) {}
  iterator(ItColl &vec, typename ItColl::iterator pos) : vec(&vec), pos(pos) {
  }
  iterator(const iterator &) = default;
  bool operator==(const iterator &it) {
    return it.pos == pos;
  }
  typename ItColl::value_type operator*() {
    return *pos;
  }
  void operator++(int) {
    pos++;
    if (pos == vec->end())
      pos = vec->begin();
  }
  iterator<ItColl> operator+(int i) {
    typename ItColl::iterator new_pos = pos;

    for (int k = 0; k < i; ++k) {
      if (new_pos == vec->end())
        new_pos = vec->begin();
      new_pos++;
    }
    if (new_pos == vec->end())
      new_pos = vec->begin();

    return iterator(*vec, new_pos);
  }
};

template<typename C> iterator(C, typename C::iterator) -> iterator<C>;

template<typename T, typename Coll = std::list<T>>
class RingQueue {
  Coll vec;
 public:

  std::unordered_map<T, iterator<Coll>> cache;

  void verifyCache() {
    for (auto&[val, it] : cache) {
      if (val != *it)
        throw "Cache integrity error!";
    }
    if (cache.size() != vec.size())
      throw "Cache integrity error!";
  }

  RingQueue() {
  }

  void resize(size_t count) {
    vec.resize(count);
  }

  iterator<Coll> erase(iterator<Coll> &it) {

    auto cache_it = cache.find(*it);
    if (cache_it == cache.end())
      throw "Cache errorr";
    cache.erase(cache_it);

    auto new_it = vec.erase(it.pos);
    if (new_it == vec.end())
      new_it = vec.begin();
    return iterator(vec, new_it);
  }

  iterator<Coll> begin() {
    return iterator(vec, vec.begin());
  }

  void push_back(T t) {
    vec.push_back(t);
    auto end = vec.end();
    end--;
    cache[t] = iterator(vec, end);
  }

  iterator<Coll> insert(iterator<Coll> it, T t) {
    auto it_next = it.pos;
    it_next++;
    if (it_next == vec.end())
      it_next = vec.begin();
    auto new_pos = vec.insert(it_next, t);
    auto it_res = iterator(vec, new_pos);
    cache[t] = it_res;
    return it_res;
  }

  T max_element() {
    return *std::max_element(vec.begin(), vec.end());
  }
  T min_element() {
    return *std::min_element(vec.begin(), vec.end());
  }

  iterator<Coll> end() {
    return iterator<Coll>(vec, vec.end());
  }

  iterator<Coll> find(T i, bool linearSearch = false) {
    if (!linearSearch) {
      auto cached_it = cache.find(i);
      if (cached_it == cache.end())
        throw "Cache error!";
      else
        return cached_it->second;
    }

    auto it = std::find(vec.begin(), vec.end(), i);
    if (it == vec.end())
      return end();
    return iterator<Coll>(vec, it);
  }

  std::string dump() {
    std::string s;
    for (auto n : vec) {
      if (!s.empty())
        s += ", ";
      s += std::to_string(n);
    }
    return s;
  }
};

class Task23 {
  uint64_t solve(bool task_2);
  bool example_data;
 public:
  Task23(bool example);
  void Solve1();
  void Solve2();
};

#endif //ADVENTOFCODE2020_TASK23_H
