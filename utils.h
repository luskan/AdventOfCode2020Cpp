//
// Created by marci_000 on 20.12.2020.
//

#ifndef ADVENTOFCODE2020_UTILS_H
#define ADVENTOFCODE2020_UTILS_H

#include <string>
#include <stdint.h>

// function has to live in the std namespace
// so that it is picked up by argument-dependent name lookup (ADL).
namespace std {
namespace {

// Code from boost
// Reciprocal of the golden ratio helps spread entropy
//     and handles duplicates.
// See Mike Seymour in magic-numbers-in-boosthash-combine:
//     https://stackoverflow.com/questions/4948780

template<class T>
inline void hash_combine(std::size_t &seed, T const &v) {
  seed ^= hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

// Recursive template code derived from Matthieu M.
template<class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
struct HashValueImpl {
  static void apply(size_t &seed, Tuple const &tuple) {
    HashValueImpl<Tuple, Index - 1>::apply(seed, tuple);
    hash_combine(seed, get<Index>(tuple));
  }
};

template<class Tuple>
struct HashValueImpl<Tuple, 0> {
  static void apply(size_t &seed, Tuple const &tuple) {
    hash_combine(seed, get<0>(tuple));
  }
};
}

template<typename ... TT>
struct hash<std::tuple<TT...>> {
  size_t
  operator()(std::tuple<TT...> const &tt) const {
    size_t seed = 0;
    HashValueImpl<std::tuple<TT...> >::apply(seed, tt);
    return seed;
  }

};
}

// trim from start (in place)
static inline void ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
    return !std::isspace(ch);
  }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
    return !std::isspace(ch);
  }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
  ltrim(s);
  rtrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
  ltrim(s);
  return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
  rtrim(s);
  return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
  trim(s);
  return s;
}

template<typename T, typename E>
inline void verify_result(T result, E expected) {
  if (result != expected)
    throw "Invalid result!";
}

#endif //ADVENTOFCODE2020_UTILS_H
