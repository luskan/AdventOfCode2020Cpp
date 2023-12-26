//
// Created by marci_000 on 20.12.2020.
//

#ifndef ADVENTOFCODE2020_UTILS_H
#define ADVENTOFCODE2020_UTILS_H

#include <string>
#include <tuple>
#include <fstream>
#include <cstdint>
#include <sstream>

#include <chrono>
#include <iostream>

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

inline std::string get_relative_data_path() {
  /*
   By default your task data can be put in the data subfolder of the project.
   If you want to move it outside the project, then return relative path as below.

   then for example your project is at:
   /Users/user/projects/AdventOfCode2020Cpp

   and task data should be put in:
   /Users/user/projects/adventofcode_input/2020/data/data1_task.txt
   /Users/user/projects/adventofcode_input/2020/data/data1_task_result1.txt
   /Users/user/projects/adventofcode_input/2020/data/data1_task_result2.txt
   ...
  */

  return std::string("../adventofcode_input/2020/");
}

template<typename T>
T read_data_from_file(const std::string& fileName, int line_start, int line_end) {
  std::ifstream ifs(fileName);
  if (!ifs) {
    throw std::runtime_error("Unable to open file: " + fileName);
  }

  T result;
  std::string buffer;
  std::string line;
  int current_line = 0;
  while (std::getline(ifs, line)) {
    if (current_line >= line_start && (line_end == -1 || current_line <= line_end)) {
      buffer += line;
    }
    if (line_end != -1 && current_line >= line_end-1) {
      break;
    }
    current_line++;
  }
  std::istringstream(buffer) >> result;
  return result;
}

template<typename T>
inline T get_data(int day, int line_start = 0, int line_end = -1) {
  std::ostringstream fileNameStream;
  fileNameStream << std::string("../") + get_relative_data_path() + "data/data" << day << "_task.txt";
  std::string fileName = fileNameStream.str();

  return read_data_from_file<T>(fileName, line_start, line_end);
}

template<typename T>
inline T get_data_result(int day, int part) {
  std::ostringstream fileNameStream;
  fileNameStream << std::string("../") + get_relative_data_path() + "data/data" << day << "_task_result" << std::to_string(part) << ".txt";
  std::string fileName = fileNameStream.str();

  return read_data_from_file<T>(fileName, 0, -1);
}

class Timer {
 private:
  std::chrono::steady_clock::time_point start;
  std::string label;

 public:
  Timer(std::string label = "") {
    this->label = label;
    start = std::chrono::steady_clock::now();
  }

  ~Timer() {
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    int minutes = static_cast<int>(elapsed.count()) / 60;
    int seconds = static_cast<int>(elapsed.count()) % 60;
    int milliseconds = static_cast<int>(elapsed.count() * 1000) % 1000;

    if (seconds > 3) {
      std::cout << label << "  time: "
                << minutes << "m:"
                << seconds << "s:"
                << milliseconds << "ms" << std::endl;
    }
  }
};

#endif //ADVENTOFCODE2020_UTILS_H
