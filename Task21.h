//
// Created by marci_000 on 24.12.2020.
//

#ifndef ADVENTOFCODE2020_TASK21_H
#define ADVENTOFCODE2020_TASK21_H

#include <set>
#include <unordered_map>
#include <string>
#include <vector>
#include "utils.h"

class Task21 {
  using alergen_name = std::string;
  using ingridient_name_t = std::string;
  using ing_count_t = double;
  using ingridients = std::multiset<ingridient_name_t>;
  using ingridient_counts_t = std::unordered_map<ingridient_name_t, int>;
  using alergens = std::multiset<alergen_name>;

  using ingridient_vec_t = std::vector<ingridient_name_t>;
  using alergen_vec_t = std::vector<alergen_name>;
  std::vector<std::tuple<ingridient_vec_t, alergen_vec_t>> input_as_vec;
  std::set<ingridient_name_t> ing_with_alergens_set;
  std::unordered_map<alergen_name, ingridients> alergens_to_ingridients;
  std::unordered_map<ingridient_name_t, alergens> ingridients_to_alergens;
  std::unordered_map<ingridient_name_t, std::vector<int>> ingridients_to_product_list_number;

  bool example_data;
 public:
  Task21(bool example);
  void Solve1();
  void Solve2();
};

#endif //ADVENTOFCODE2020_TASK21_H
