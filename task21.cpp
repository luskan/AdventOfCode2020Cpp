//
// Created by marci_000 on 24.12.2020.
//

#include "task21.h"
#include <regex>
#include <fstream>
#include <iostream>

task21::task21() {
    std::ifstream ifs("../data21.txt");
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

void task21::solve1() {
    /*
    std::cout << "Ingridients:" <<std::endl;
    for (auto [key, value] : ingridients_to_alergens) {
       std::cout << key << std::endl;
       std::cout << "   " << value.size() << ":";
       std::vector<std::string> srt;
        for (auto v : value)
            srt.push_back(v);
        std::sort(srt.begin(), srt.end());
       for (auto v : srt) {
           std::cout << " " << v;
       }
       std::cout << std::endl;
    }

    std::cout << "Alergens:" <<std::endl;
    for (auto [key, value] : alergens_to_ingridients) {
        std::cout << key << std::endl;
        std::cout << "   " << value.size() << ":";
        std::vector<std::string> srt;
        for (auto v : value)
            srt.push_back(v);
        std::sort(srt.begin(), srt.end());
        for (auto v : srt) {
            std::cout << " " << v;
        }
        std::cout << std::endl;
    }
*/

    std::vector<std::tuple<ingridient_name_t, ing_count_t>> ingridient_counts;
    std::vector<std::tuple<alergen_name, ingridient_name_t, ing_count_t>> ingridient_all_counts;
    std::unordered_map<alergen_name, ingridient_counts_t> alergens_to_ingridient_counts;

    // For each alergen, count all its possible ingridients
    // So we will have a map with entry for each alergen - and counts of each its indgridients
    for (auto& [alerg_name, ingridients] : alergens_to_ingridients) {
        for (auto& ing : ingridients) {
            alergens_to_ingridient_counts[alerg_name][ing]++;
        }
    }

    // Now make a total sum of each ingridient count and store it in ingridient_counts.
    // ingridient_all_counts is also created, but its a rewrite of alergens_to_ingridient_counts into a vector of tuples.
    for (auto& [alerg_name, ing_counts] : alergens_to_ingridient_counts) {
        int total_sum = 0;
        for (auto& [ing_name, count] : ing_counts)
            total_sum += count;
        for (auto& [ing_name, count] : ing_counts) {
            ingridient_all_counts.push_back(std::make_tuple(alerg_name, ing_name, (double) count / (double)total_sum));
            auto it = std::find_if(ingridient_counts.begin(), ingridient_counts.end(),
                                   [&](auto &item)
                                   {
                                        auto& [ing,prob_old] = item;
                                        return ing == ing_name;
                                   });
            if (it == ingridient_counts.end())
                ingridient_counts.push_back(std::make_tuple(ing_name, (double) count / (double)total_sum));
            else {
                auto [ing,prob_old] = *it;
                ingridient_counts.erase(it);
                ingridient_counts.push_back(
                        std::make_tuple(ing_name, (double) count / (double)total_sum + prob_old));
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
    std::set<ingridient_name_t> ing_with_alergens_set;
    std::vector<ingridient_name_t> ing_with_no_alergens;
    // Alergen can have one or zero alergens. ingridient_counts is sorted so at the begining
    // we will have ingridients with highest counts which are better candidates.
    for (const auto &it : ingridient_counts) {
        auto& [ing_name, count] = it;
        if (was_ingridient_used.contains(ing_name))
            continue;
        was_ingridient_used.insert(ing_name);
        //std::cout << std::get<1>(prob) << " : " << std::get<2>(prob) << " - " << std::get<0>(prob);

        // There are fewer alergens than ingridients ("Each allergen is found in exactly one ingredient").
        if (ing_with_alergens.size() < number_of_alergens) {
            ing_with_alergens.push_back(ing_name);
            ing_with_alergens_set.insert(ing_name);
            //std::cout << " +";
        } else {
            ing_with_no_alergens.push_back(ing_name);
            //std::cout << " -";
        }

        //std::cout << std::endl;
    }

    // ing_with_alergens contains now possible ingridients with alergens,
    // and ing_with_no_alergens contains those with no alergens.

    int final_count = 0;
    for (auto &ing_name : ing_with_no_alergens) {
        final_count += ingridients_to_product_list_number[ing_name].size();
    }
    // correct: 2461
    std::cout << "Solution1: " << final_count << std::endl;

    ///


    /////
    /////

    /*
    alergens_to_ingridient_counts.clear();
    for (auto& [alerg_name, ingridients] : alergens_to_ingridients) {
        for (auto& ing : ingridients) {
            if (ing_with_alergens_set.contains(ing))
                alergens_to_ingridient_counts[alerg_name][ing]++;
        }
    }

    ingridient_counts.clear();
    ingridient_all_counts.clear();

    // Now make a total sum of each ingridient count and store it in ingridient_counts.
    // ingridient_all_counts is also created, but its a rewrite of alergens_to_ingridient_counts into a vector of tuples.
    for (auto& [alerg_name, ing_counts] : alergens_to_ingridient_counts) {
        int total_sum = 0;
        for (auto& [ing_name, count] : ing_counts)
            total_sum += count;
        for (auto& [ing_name, count] : ing_counts) {
            ingridient_all_counts.push_back(std::make_tuple(alerg_name, ing_name, (double) count / (double)total_sum));
            auto it = std::find_if(ingridient_counts.begin(), ingridient_counts.end(),
                                   [&](auto &item)
                                   {
                                       auto& [ing,prob_old] = item;
                                       return ing == ing_name;
                                   });
            if (it == ingridient_counts.end())
                ingridient_counts.push_back(std::make_tuple(ing_name, (double) count / (double)total_sum));
            else {
                auto [ing,prob_old] = *it;
                ingridient_counts.erase(it);
                ingridient_counts.push_back(
                        std::make_tuple(ing_name, (double) count / (double)total_sum + prob_old));
            }
        }
    }

    // Sort by counts
    std::sort(ingridient_counts.begin(), ingridient_counts.end(),
              [](const auto &p1, const auto &p2) { return std::get<1>(p1) > std::get<1>(p2); });
    std::sort(ingridient_all_counts.begin(), ingridient_all_counts.end(),
              [](const auto &p1, const auto &p2) { return std::get<2>(p1) > std::get<2>(p2); });

    /////
    /////

    std::set<alergen_name> was_alergen_used;
    std::vector<std::tuple<std::string, std::string>> final_ingridient_to_alergen;
    std::unordered_map<alergen_name, std::vector<std::tuple<ingridient_name_t, ing_count_t>>> alergen_name_to_ing_probs;
    for (const auto &prob : ingridient_all_counts) {
        auto&[alergen_name, ingridient_name, count] = prob;

        // Skip ingridients which cannot have alergens.
        if (std::find(ing_with_alergens.begin(), ing_with_alergens.end(), ingridient_name) == ing_with_alergens.end())
            continue;

        //std::cout << alergen_name << " : " << ingridient_name << " - " << count << std::endl;

        alergen_name_to_ing_probs[alergen_name].push_back(std::make_tuple(ingridient_name, count));
    }

    // Now we have in alergen_name_to_ing_probs, for each alergen, list of ingridients which can possibly
    // have this alergen with number of its occurences. For each alergen, we will now sort ingridients by its occurencies.
    // Those with highest occurrencies are better candidates.

    for (auto&[alergen, ing_counts] : alergen_name_to_ing_probs) {
        std::sort(ing_counts.begin(), ing_counts.end(), [](auto &p1, auto &p2) { return std::get<1>(p1) > std::get<1>(p2); });
    }

    // Now we create a vector with alergen,ingridient and ingridient count, to find which ingridient
    // have higher count for which alergen.
    std::vector<std::tuple<alergen_name, ingridient_name_t, ing_count_t>> top_counts_for_ing;
    for (auto&[alergen, ing_name_counts] : alergen_name_to_ing_probs) {
        //std::cout << alergen << std::endl;
        for (auto it : ing_name_counts) {
            auto& [ing_name, count] = it;
            //std::cout << "  : " << ing_name << " - " << count << std::endl;
            top_counts_for_ing.push_back(std::make_tuple(alergen, ing_name, count));
        }
    }

    // Sort by counts
    std::sort(top_counts_for_ing.begin(), top_counts_for_ing.end(),
              [](auto &p1, auto &p2)
              {
        auto& [p1_alg_name, p1_ing_name, p1_count] = p1;
        auto& [p2_alg_name, p2_ing_name, p2_count] = p2;

        return p1_count > p2_count;
        //return std::make_tuple(p1_count, p1_ing_name) > std::make_tuple(p2_count, p2_ing_name);
    });

    std::unordered_map<ingridient_name_t, std::vector<std::tuple<alergen_name, ing_count_t>>> ing_to_probs_fin;
    std::set<alergen_name> choosen_alergen;
    std::set<ingridient_name_t> choosen_ing;
    for (auto &it : top_counts_for_ing) {
        auto&[a_name, i_name, prob] = it;

        std::cout << "top: " << a_name << ", " << i_name << ", " << prob << "  - "
                  << (choosen_alergen.contains(a_name) ? "alergen was" : "") << ", "
                  << (choosen_ing.contains(i_name) ? "ing was" : "")
                  << std::endl;

        if (choosen_alergen.contains(a_name))
            continue;
        if (choosen_ing.contains(i_name))
            continue;
        choosen_alergen.insert(a_name);
        choosen_ing.insert(i_name);
        ing_to_probs_fin[i_name].push_back(std::make_tuple(a_name, prob));

        final_ingridient_to_alergen.push_back(std::make_tuple(i_name, a_name));
    }
     */

    std::set<alergen_name> was_alergen_used;
    std::vector<std::tuple<std::string, std::string>> final_ingridient_to_alergen;

    std::unordered_map<ingridient_name_t, std::vector<std::tuple<alergen_name, ing_count_t>>> ing_to_probs_fin;
    std::set<alergen_name> choosen_alergen;
    std::set<ingridient_name_t> choosen_ing;

    std::unordered_map<ingridient_name_t, std::unordered_map<alergen_name, int>> ings_to_alergs;


    std::vector<std::string> ing_all_vec;
    for (auto& [ing, alg] : ingridients_to_alergens) {
        if (ing_with_alergens_set.contains(ing))
            ing_all_vec.push_back(ing);
    }
    std::sort(ing_all_vec.begin(), ing_all_vec.end());

    std::vector<std::tuple<std::string,std::string>> out_vecs;

    std::unordered_map<ingridient_name_t, std::set<alergen_name>> ingredient_to_not_its_alergens;

    for (auto& product : input_as_vec) {
        auto& [ing_vec, alerg_vec] = product;
        ingridient_vec_t ing_with_alergs_vec;

        ingridient_vec_t ing_vec_copy;
        for (auto s : ing_vec) {
            if ( ing_with_alergens_set.contains(s) )
                ing_vec_copy.push_back(s);
        }

        std::sort(ing_vec_copy.begin(), ing_vec_copy.end());
        int ik = 0;
        std::string line;
        for (auto& ing : ing_vec_copy) {
            if (ing_all_vec[ik] != ing) {
                line += std::string(ing_all_vec[ik].size(), ' ') + " ";

                for (auto a : alerg_vec)
                    ingredient_to_not_its_alergens[ing_all_vec[ik]].insert(a);
                ik++;
            }
            ik++;
            line += ing + " ";
            ing_with_alergs_vec.push_back(ing);
            for (auto a : alerg_vec)
                ings_to_alergs[ing][a]++;
        }

        if (ik < ing_all_vec.size()) {
            line += std::string(ing_all_vec[ik].size(), ' ') + " ";
            auto ing2 = ing_all_vec[ik];
            for (auto a : alerg_vec)
                ingredient_to_not_its_alergens[ing2].insert(a);
        }

        std::string line2;
        line2 = "(contains ";
        for (size_t i = 0; i < alerg_vec.size(); ++i) {

            line2 += alerg_vec[i];
            if ( i + 1 < alerg_vec.size())
                line2 += ", ";
        }
        line2 += ")";

        out_vecs.push_back({line, line2});

        size_t ai = 0;
        size_t ii = 0;
        while(true) {
            if (ai >= alerg_vec.size())
                break;
            if (ii >= ing_with_alergs_vec.size())
                break;
            if (choosen_alergen.contains(alerg_vec[ai])) {
                ai++;
                continue;
            }
            if (choosen_ing.contains(ing_with_alergs_vec[ii])) {
                ii++;
                continue;
            }
            choosen_alergen.insert(alerg_vec[ai]);
            choosen_ing.insert(ing_with_alergs_vec[ii]);
            final_ingridient_to_alergen.push_back(std::make_tuple(ing_with_alergs_vec[ii], alerg_vec[ai]));
            ii++;ai++;
        }
    }

    std::sort(out_vecs.begin(), out_vecs.end(), [](auto& p1, auto& p2) { return std::get<0>(p1) < std::get<0>(p2); });
    for (auto&[l1,l2] : out_vecs)
        std::cout << l1 << " " << l2 << std::endl;

    std::unordered_map<ingridient_name_t, std::set<alergen_name>> ingredient_to_its_alergens;
    for (auto& [ing_name,not_its_alergens] : ingredient_to_not_its_alergens) {
        for (auto& [alg, _] : alergens_to_ingridients) {
            if (!not_its_alergens.contains(alg))
                ingredient_to_its_alergens[ing_name].insert(alg);
        }
    }

    for (int tr=0; tr < 100; ++tr) {

        // Check if all sets are one element
        int one_element_count = 0;
        for (auto& [ing, algs] : ingredient_to_its_alergens)
            one_element_count += algs.size();
        if (one_element_count == ingredient_to_its_alergens.size())
            break;

        // Iterate all ingridients with its possible sets, for each ingridient with finally assigned alergen
        // (this will be ingridient with one element set) remove this alergen with all the rest ingridient sets.
        for (auto& [ing, algs] : ingredient_to_its_alergens) {
            if (algs.size() == 1) {
                for (auto& [ing2, algs2] : ingredient_to_its_alergens) {
                    if (algs2.size() == 1)
                        continue;
                    algs2.erase(*algs.begin());
                }
            }
        }
    }


    //
    std::cout << "ingredient_to_not_its_alergens" << std::endl;
    for (auto& [ing_name,its_alergens] : ingredient_to_not_its_alergens) {
        std::cout << ing_name << " : ";
        //if (its_alergens.size() != 1)
        //    throw "Something wrong!";
        //final_ingridient_to_alergen.push_back({ing_name, *its_alergens.begin()});
        for (auto alg : its_alergens) {
            std::cout << alg << ",";
        }
        std::cout << std::endl;
    }

    std::cout << "ingredient_to_its_alergens" << std::endl;
    final_ingridient_to_alergen.clear();
    for (auto& [ing_name,its_alergens] : ingredient_to_its_alergens) {
        std::cout << ing_name << " : ";
        if (its_alergens.size() != 1)
            throw "Something wrong!";
        final_ingridient_to_alergen.push_back({ing_name, *its_alergens.begin()});
        for (auto alg : its_alergens) {
            std::cout << alg << ",";
        }
        std::cout << std::endl;
    }

    std::cout << "--- --- --- ---" << std::endl;

    // Sort ingridients by their alergen names
    std::sort(final_ingridient_to_alergen.begin(), final_ingridient_to_alergen.end(),
              [](auto &p1, auto &p2) { return std::get<1>(p1) < std::get<1>(p2); });

    // Final answer
    std::string final_str;
    for (auto &v : final_ingridient_to_alergen) {
        auto& [ing_name, alg_name] = v;
        std::cout << ing_name << " : " << alg_name << std::endl;
        if (!final_str.empty())
            final_str += ",";
        final_str += ing_name;
    }

    if (final_str != "ltbj,nrfmm,pvhcsn,jxbnb,chpdjkf,jtqt,zzkq,jqnhd")
        throw "Invalid!";
    std::cout << "Solution2: " << final_str << std::endl;
}

void task21::solve2() {

}
