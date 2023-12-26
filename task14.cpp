//
// Created by Marcin Jędrzejewski on 14/12/2020.
//

#include "task14.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <map>
#include <cmath>
#include "utils.h"

Task14::Task14(bool example, bool p2) {
  example_data = example;
  part2 = p2;
  std::ifstream ifs(example ? (!p2 ? "../data/data14_example.txt" : std::string("../") + get_relative_data_path() + "data/data14_example_part2.txt")
  : std::string("../") + get_relative_data_path() + "data/data14_task.txt");
      std::string line;

  std::regex rg_mask(R"(mask = ([01X]+))");
  std::regex rg_assign(R"(mem\[(\d+)\] = (\d+))");

  data d;
  int maskCount = 0;
  while (std::getline(ifs, line)) {
    std::smatch sm;

    if (std::regex_match(line, sm, rg_mask)) {
      if (maskCount > 0) {
        entries.push_back(d);
        d = {};
      }
      d.mask = sm[1];
      maskCount++;
    } else if (std::regex_match(line, sm, rg_assign)) {
      d.assings.push_back({std::stoi(sm[1]), std::stoi(sm[2])});
    } else {
      throw "Wrong parsing!";
    }
  }
  entries.push_back(d);
}

void Task14::Solve1() {
  Timer opt_timer;
  std::map<uint64_t, uint64_t> mem;
  for (size_t i = 0; i != entries.size(); ++i) {
    std::string &mask = entries[i].mask;
    uint64_t mask_set_ones = 0;
    uint64_t mask_set_zeros = 0;
    for (int i = mask.size() - 1; i >= 0; --i) {
      uint64_t bitToSet = (mask.size() - 1 - i);
      if (mask[i] == '1')
        mask_set_ones |= (1ULL << bitToSet);
      if (mask[i] == '0')
        mask_set_zeros |= (1ULL << bitToSet);
    }
    for (size_t k = 0; k < entries[i].assings.size(); ++k) {
      uint64_t addr = std::get<0>(entries[i].assings[k]);
      uint64_t arg = std::get<1>(entries[i].assings[k]);
      arg |= mask_set_ones;
      arg &= ~mask_set_zeros;
      mem[addr] = arg;
    }
  }
  uint64_t sum = 0;
  for (auto[key, value] : mem) {
    sum += value;
  }

  verify_result(sum, example_data ? 165ull : get_data_result<uint64_t>(14, 1));
  std::cout << " part1: sum = " << sum << std::endl;
}

void Task14::Solve2() {
  Timer opt_timer;
  std::map<uint64_t, uint64_t> mem;

  for (size_t i = 0; i != entries.size(); ++i) {
    std::string &mask = entries[i].mask;

    // Setup initial mask, and count how many floating bits exists.
    uint64_t mask_set_ones_org = 0;
    int floatingCount = 0;
    for (int i = mask.size() - 1; i >= 0; --i) {
      uint64_t bitToSet = (mask.size() - 1 - i);
      if (mask[i] == '1')
        mask_set_ones_org |= (1ULL << bitToSet);
      if (mask[i] == 'X')
        floatingCount++;
    }

    for (size_t k = 0; k < entries[i].assings.size(); ++k) {
      uint64_t addr = std::get<0>(entries[i].assings[k]);
      uint64_t arg = std::get<1>(entries[i].assings[k]);

      // If there are floating positions...
      if (floatingCount != 0) {

        //then iterate all its possible combinations.
        for (uint64_t fcount = 0; fcount < pow(2, floatingCount); ++fcount) {
          addr = std::get<0>(entries[i].assings[k]);
          uint64_t fcountIt = 0;
          uint64_t mask_set_ones = mask_set_ones_org;
          uint64_t mask_set_zeros = 0;
          for (int i = mask.size() - 1; i >= 0; --i) {
            if (mask[i] == 'X') {
              bool b = fcount & (1ULL << fcountIt);
              uint64_t bitToSet = (mask.size() - 1 - i);
              if (b)
                mask_set_ones |= (1ULL << bitToSet);
              else
                mask_set_zeros |= (1ULL << bitToSet);
              fcountIt++;
            }
          }
          addr |= mask_set_ones;
          addr &= ~mask_set_zeros;
          mem[addr] = arg;
        }
      } else {
        addr |= mask_set_ones_org;
        mem[addr] = arg;
      }
    }
  }
  uint64_t sum = 0;
  for (auto[key, value] : mem) {
    sum += value;
  }

  verify_result(sum, example_data ? 208ull : get_data_result<uint64_t>(14, 2));
  std::cout << " part2: sum = " << sum << std::endl;
}
