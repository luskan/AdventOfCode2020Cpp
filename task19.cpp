//
// Created by marci_000 on 19.12.2020.
//

#include "task19.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include "utils.h"

Task19::Task19(bool example, bool s2) {
  solve_2 = s2;
  example_data = example;
  std::ifstream ifs(example ? (solve_2 ? "../data/data19_example_2.txt" : std::string("../") + get_relative_data_path() + "data/data19_example.txt") : std::string("../") + get_relative_data_path() + "data/data19_task.txt");
  std::string line;

  std::regex rg_rule_1(R"((\d+): \"(\w+)\")");
  std::regex rg_rule_2(R"((\d+): (.*))");
  while (std::getline(ifs, line)) {
    if (line.empty())
      break;
    std::smatch sm;
    if (std::regex_match(line, sm, rg_rule_1)) {
      int index = std::stoi(sm[1]);
      if (sm[2].str().size() != 1)
        throw "Wrong string!";
      char c = sm[2].str().at(0);
      data d;
      d.final = true;
      d.c = c;
      if (rules.contains(index))
        throw "Multiple indexes!";
      rules[index] = d;
    } else if (std::regex_match(line, sm, rg_rule_2)) {
      int index = std::stoi(sm[1]);
      std::string rls = sm[2];
      data d;
      d.final = false;

      const std::regex sep_rg(R"( )");
      std::regex_token_iterator rg_it(rls.begin(), rls.end(), sep_rg, -1);
      std::regex_token_iterator<std::string::iterator> rg_end;
      d.rules.resize(1);
      for (; rg_it != rg_end; ++rg_it) {
        auto v = (*rg_it).str();
        if (*rg_it == "|") {
          d.rules.resize(d.rules.size() + 1);
        } else {
          int val = std::stoi(*rg_it);
          d.rules.back().push_back(val);
        }
      }

      if (rules.contains(index))
        throw "Multiple indexes!";
      rules[index] = d;
    }
  }

  while (std::getline(ifs, line)) {
    if (line.empty())
      break;
    test_strings.push_back(std::move(line));
  }
}

void Task19::Solve1() {
  Timer opt_timer;
  std::string expr = build_rules(rules, 0);
  //std::cout << expr << std::endl;
  rg = std::move(std::regex(expr, std::regex_constants::ECMAScript | std::regex_constants::icase));

  int total = 0;
  for (auto &str : test_strings) {
    if (std::regex_match(str, rg)) {
      total++;
    }
  }
  verify_result(total, example_data ? 2 :  get_data_result<int>(19, 1));
  std::cout << " part1: total = " << total << std::endl;
}

void Task19::Solve2() {
  Timer opt_timer;
  // Change rules:
  //8: 42
  //11: 42 31

  // To:
  //8: 42 | 42 8
  //11: 42 31 | 42 11 31

  std::vector<int> rule8 = {42, 8};
  rules[8].rules.push_back(rule8);
  std::vector<int> rule11 = {42, 11, 31};
  rules[11].rules.push_back(rule11);

  std::string expr = build_rules(rules, 0);
  //std::cout << expr << std::endl;
  rg = std::move(std::regex(expr, std::regex_constants::ECMAScript | std::regex_constants::icase));

  int total = 0;
  for (auto &str : test_strings) {
    if (std::regex_match(str, rg)) {
      total++;
    }
  }

  verify_result(total, example_data ? 12 : get_data_result<int>(19, 2));
  std::cout << " part2: total = " << total << std::endl;
}

std::string Task19::build_rules(const std::unordered_map<int, data> &rules_map, int index, int depth) {
  if (!rules_map.contains(index))
    throw "Missing rule!";
  if (depth == 20)
    return "";
  const auto &d = rules_map.at(index);
  std::string res;
  if (d.final) {
    res = std::string("") + d.c;
  } else {
    for (int k = 0; k < d.rules.size(); ++k) {
      const auto &rl = d.rules[k];
      for (int n = 0; n < rl.size(); ++n) {
        const auto &v = rl[n];
        std::string ex = build_rules(rules_map, v, depth + 1);
        if (!ex.empty())
          res += std::move(ex);
      }
      if (!res.empty() && !(k + 1 == d.rules.size()))
        res += "|";
    }
    res = "(?:" + res + ")";
  }
  return res;
}
