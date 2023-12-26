//
// Created by marcin on 07.12.2020.
//

#include "task7.h"

#include <fstream>
#include <iostream>
#include <regex>
#include "utils.h"

Task7::Task7(bool example, bool part1) {
  for_part1 = part1;
  example_data = example;
  std::ifstream
      ifs(example_data ? (for_part1 ? "../data/data7_example.txt" : std::string("../") + get_relative_data_path() + "data/data7_example_part2.txt") : std::string("../") + get_relative_data_path() + "data/data7_task.txt");
  std::string line;

  // light lavender bags contain 5 clear teal bags, 2 wavy gold bags, 5 drab maroon bags, 2 posh cyan bags.
  std::regex regStart{R"(([\w\s]+?) bags contain )",
      std::regex_constants::ECMAScript | std::regex_constants::icase};
  std::regex regIns{R"((\d+) ([\w\s]+?) bags?[,.])",
      std::regex_constants::ECMAScript | std::regex_constants::icase};

  while (std::getline(ifs, line)) {
    std::smatch m1;
    if (!std::regex_search(line, m1, regStart))
      throw "Something wrong!";

    Bag bag;
    bag.color = m1[1];
    if (bags.contains(bag.color))
      bag = bags[bag.color];

    std::sregex_iterator reg_begin(line.begin() + m1[0].str().size() - 1, line.end(), regIns);
    std::sregex_iterator reg_end = std::sregex_iterator();
    for (auto ri = reg_begin; ri != reg_end; ++ri) {
      std::smatch m = *ri;
      if (m.size() != 3)
        throw "Wrong number of fields parsed!";
      bag.bagsItCanContain[m[2]] = std::stoi(m[1]);

      Bag bag2;
      if (bags.contains(m[2]))
        bag2 = bags[m[2]];
      else
        bag2.color = m[2];
      if (bag2.bagsItCanBeIn.contains(bag.color))
        throw "Somethind weiiiired!";
      bag2.bagsItCanBeIn.insert(bag.color);
      bags[bag2.color] = bag2;
    }

    bags[bag.color] = bag;
  }
}

void Task7::Solve1() {
  Timer opt_timer;
  Bag bag = bags["shiny gold"];
  std::set<std::string> all;
  for (auto bagColor : bag.bagsItCanBeIn) {
    std::set<std::string> path = findPathUp(bagColor);
    all.merge(path);
  }

  verify_result(all.size(), example_data ? 4ul : get_data_result<uint64_t>(7, 1));
  std::cout << " part1: total = " << all.size() << std::endl;
}

void Task7::Solve2() {
  Timer opt_timer;
  Bag bag = bags["shiny gold"];
  std::multiset<std::string> all;
  for (auto bagc : bag.bagsItCanContain) {
    for (int n = 0; n < bagc.second; ++n) {
      all.insert(bagc.first);
      std::multiset<std::string> path = findPathDown(bagc.first);
      all.merge(path);
    }
  }

  verify_result(all.size(), example_data ? 126ul : get_data_result<uint64_t>(7, 2));
  std::cout << " part2: total = " << all.size() << std::endl;
}

std::set<std::string> Task7::findPathUp(std::string bagColor) {
  std::set<std::string> path;
  path.insert(bagColor);
  Bag bag = bags[bagColor];
  for (auto bagc : bag.bagsItCanBeIn) {
    auto resVec = findPathUp(bagc);
    path.merge(resVec);
  }
  return path;
}

std::multiset<std::string> Task7::findPathDown(std::string bagColor) {
  std::multiset<std::string> path;
  Bag bag = bags[bagColor];
  for (auto bagc : bag.bagsItCanContain) {
    for (int n = 0; n < bagc.second; ++n) {
      path.insert(bagc.first);
      auto resVec = findPathDown(bagc.first);
      path.merge(resVec);
    }
  }
  return path;
}
