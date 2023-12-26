//
// Created by marci_000 on 24.12.2020.
//

#include "Task21.h"
#include <regex>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "utils.h"

using namespace std::literals;

Task21::Task21(bool example) {
  example_data = example;

  std::ifstream ifs(example ? "../data/data21_example.txt" : std::string("../") + get_relative_data_path() + "data/data21_task.txt");
  std::string line;

  std::regex rg_all(R"(([\w+ ]+)\s\(contains ([\w+, ]+)\))");
  std::regex rg_first_part(R"( )");
  std::regex rg_second_part(R"(,)");
  int product_list_id = 0;
  while (std::getline(ifs, line)) {
    std::smatch sm;
    std::vector<std::string> ingridients;
    std::vector<std::string> alergens;
    if (std::regex_match(line, sm, rg_all)) {
      std::string part1 = sm[1];
      std::string part2 = sm[2];

      std::regex_token_iterator rg_it(part1.begin(), part1.end(), rg_first_part, -1);
      std::regex_token_iterator<std::string::iterator> rg_end;
      for (; rg_it != rg_end; ++rg_it) {
        ingridients.push_back(trim_copy(*rg_it));
      }

      std::regex_token_iterator rg_it2(part2.begin(), part2.end(), rg_second_part, -1);
      std::regex_token_iterator<std::string::iterator> rg_end2;
      for (; rg_it2 != rg_end2; ++rg_it2) {
        alergens.push_back(trim_copy(*rg_it2));
      }

      input_as_vec.push_back(std::make_tuple(ingridients, alergens));

      for (auto &a : alergens)
        for (auto &i : ingridients)
          alergens_to_ingridients[a].insert(i);
      for (auto &i : ingridients)
        for (auto &a : alergens)
          ingridients_to_alergens[i].insert(a);
      for (auto &i : ingridients)
        ingridients_to_product_list_number[i].push_back(product_list_id);

      ++product_list_id;
    } else {
      throw "Parins error!";
    }
  }
}

void Task21::Solve1() {
  Timer opt_timer;
  std::vector<std::tuple<ingridient_name_t, ing_count_t>> ingridient_counts;
  std::vector<std::tuple<alergen_name, ingridient_name_t, ing_count_t>> ingridient_all_counts;
  std::unordered_map<alergen_name, ingridient_counts_t> alergens_to_ingridient_counts;

  // For each alergen, count all its possible ingridients
  // So we will have a map with entry for each alergen - and counts of each its indgridients
  for (auto&[alerg_name, ingridients] : alergens_to_ingridients) {
    for (auto &ing : ingridients) {
      alergens_to_ingridient_counts[alerg_name][ing]++;
    }
  }

  // Now make a total sum of each ingridient count and store it in ingridient_counts.
  // ingridient_all_counts is also created, but its a rewrite of alergens_to_ingridient_counts into a vector of tuples.
  for (auto&[alerg_name, ing_counts] : alergens_to_ingridient_counts) {
    int total_sum = 0;
    for (auto&[ing_name, count] : ing_counts)
      total_sum += count;
    for (auto&[ing_name, count] : ing_counts) {
      ingridient_all_counts.push_back(std::make_tuple(alerg_name, ing_name, (double) count / (double) total_sum));
      auto it = std::find_if(ingridient_counts.begin(), ingridient_counts.end(),
                             [&, ing_name = ing_name](auto &item) {
                               auto&[ing, prob_old] = item;
                               return ing == ing_name;
                             });
      if (it == ingridient_counts.end())
        ingridient_counts.push_back(std::make_tuple(ing_name, (double) count / (double) total_sum));
      else {
        auto[ing, prob_old] = *it;
        ingridient_counts.erase(it);
        ingridient_counts.push_back(
            std::make_tuple(ing_name, (double) count / (double) total_sum + prob_old));
      }
    }
  }

  // Sort by counts
  std::sort(ingridient_counts.begin(), ingridient_counts.end(),
            [](const auto &p1, const auto &p2) { return std::get<1>(p1) > std::get<1>(p2); });
  std::sort(ingridient_all_counts.begin(), ingridient_all_counts.end(),
            [](const auto &p1, const auto &p2) { return std::get<2>(p1) > std::get<2>(p2); });

  std::set<ingridient_name_t> was_ingridient_used;
  int number_of_alergens = alergens_to_ingridients.size();
  std::vector<ingridient_name_t> ing_with_alergens;
  std::vector<ingridient_name_t> ing_with_no_alergens;

  // Alergen can have one or zero alergens. ingridient_counts is sorted so at the begining
  // we will have ingridients with highest counts which are better candidates.
  for (const auto &it : ingridient_counts) {
    auto&[ing_name, count] = it;
    if (was_ingridient_used.contains(ing_name))
      continue;
    was_ingridient_used.insert(ing_name);

    // There are fewer alergens than ingridients ("Each allergen is found in exactly one ingredient").
    if (ing_with_alergens.size() < number_of_alergens) {
      ing_with_alergens.push_back(ing_name);
      ing_with_alergens_set.insert(ing_name);
    } else {
      ing_with_no_alergens.push_back(ing_name);
    }
  }

  // ing_with_alergens contains now possible ingridients with alergens,
  // and ing_with_no_alergens contains those with no alergens.

  int final_count = 0;
  for (auto &ing_name : ing_with_no_alergens) {
    final_count += ingridients_to_product_list_number[ing_name].size();
  }

  verify_result(final_count, example_data ? 5 : get_data_result<uint64_t>(21, 1));
  std::cout << " part1: result = " << final_count << std::endl;
}

void Task21::Solve2() {
  Timer opt_timer;
  std::vector<std::string> ing_all_vec;
  for (auto&[ing, alg] : ingridients_to_alergens) {
    if (ing_with_alergens_set.contains(ing))
      ing_all_vec.push_back(ing);
  }
  std::sort(ing_all_vec.begin(), ing_all_vec.end());
  std::unordered_map<ingridient_name_t, std::set<alergen_name>> ingredient_to_not_its_alergens;

  for (auto &product : input_as_vec) {
    auto&[ing_vec, alerg_vec] = product;

    ingridient_vec_t ing_vec_copy;
    for (auto s : ing_vec) {
      if (ing_with_alergens_set.contains(s))
        ing_vec_copy.push_back(s);
    }

    std::sort(ing_vec_copy.begin(), ing_vec_copy.end());
    int ik = 0;
    for (auto &ing : ing_vec_copy) {
      if (ing_all_vec[ik] != ing) {
        for (auto a : alerg_vec)
          ingredient_to_not_its_alergens[ing_all_vec[ik]].insert(a);
        ik++;
      }
      ik++;
    }

    // Add final missing ingridient.
    if (ik < ing_all_vec.size()) {
      auto ing2 = ing_all_vec[ik];
      for (auto a : alerg_vec)
        ingredient_to_not_its_alergens[ing2].insert(a);
    }
  }

  std::unordered_map<ingridient_name_t, std::set<alergen_name>> ingredient_to_its_alergens;
  for (auto&[ing_name, not_its_alergens] : ingredient_to_not_its_alergens) {
    for (auto&[alg, dummy] : alergens_to_ingridients) {
      if (!not_its_alergens.contains(alg))
        ingredient_to_its_alergens[ing_name].insert(alg);
    }
  }

  // Reduce possible alergens for each ingridient.
  while (true) {

    // Check if all sets are one element
    int one_element_count = 0;
    for (auto&[ing, algs] : ingredient_to_its_alergens)
      one_element_count += algs.size();
    if (one_element_count == ingredient_to_its_alergens.size())
      break;

    // Iterate all ingridients with its possible sets, for each ingridient with finally assigned alergen
    // (this will be ingridient with one element set) remove this alergen with all the rest ingridient sets.
    for (auto&[ing, algs] : ingredient_to_its_alergens) {
      if (algs.size() == 1) {
        for (auto&[ing2, algs2] : ingredient_to_its_alergens) {
          if (algs2.size() == 1)
            continue;
          algs2.erase(*algs.begin());
        }
      }
    }
  }

  // Rewrite map of results into vector
  std::vector<std::tuple<std::string, std::string>> final_ingridient_to_alergen;
  for (auto&[ing_name, its_alergens] : ingredient_to_its_alergens) {
    if (its_alergens.size() != 1)
      throw "Something wrong!";
    final_ingridient_to_alergen.push_back({ing_name, *its_alergens.begin()});
  }

  // Sort ingridients by their alergen names
  std::sort(final_ingridient_to_alergen.begin(), final_ingridient_to_alergen.end(),
            [](auto &p1, auto &p2) { return std::get<1>(p1) < std::get<1>(p2); });

  // Final answer
  std::string final_str;
  for (auto &v : final_ingridient_to_alergen) {
    auto&[ing_name, alg_name] = v;
    //std::cout << ing_name << " : " << alg_name << std::endl;
    if (!final_str.empty())
      final_str += ",";
    final_str += ing_name;
  }

  verify_result(final_str, example_data ? "mxmxvkd,sqjhc,fvjkl"s : get_data_result<std::string>(21, 2));
  std::cout << " part2: result = " << final_str << std::endl;
}
