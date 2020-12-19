//
// Created by marci_000 on 16.12.2020.
//

#include "task16.h"

#include <iostream>
#include <fstream>
#include <regex>
#include <set>

task16::task16() {
    std::ifstream ifs("../data16.txt");
    std::string line;
    std::regex rg_rule(R"(([\w\W\s]+): (\d+)-(\d+) or (\d+)-(\d+))");
    while(std::getline(ifs, line)) {
        if (line.size() == 0)
            continue;
        if (line == "your ticket:")
            break;
        std::smatch sm;
        if (std::regex_match(line, sm, rg_rule)) {
            Rule r;
            r.name = sm[1];
            r.range1Start = std::stoi(sm[2]);
            r.range1End = std::stoi(sm[3]);
            r.range2Start = std::stoi(sm[4]);
            r.range2End = std::stoi(sm[5]);
            rules.push_back(r);
        }
        else {
            throw "Wrong parsing!";
        }
    }

    while(std::getline(ifs, line)) {
        if (line.size() == 0)
            continue;
        if (line == "nearby tickets:")
            continue;

        std::regex rg_token(",");
        std::regex_token_iterator rg_beg(line.begin(), line.end(), rg_token, -1);
        std::regex_token_iterator<std::string::iterator> rg_end;
        ticket_t ticket;
        for(auto it = rg_beg; it != rg_end; ++it) {
            ticket.push_back(std::stoi((*it).str()));
        }
        if (my_ticket.size() == 0)
            my_ticket = std::move(ticket);
        else
            tickets.push_back(std::move(ticket));
    }

    for (auto r : rules) {
        for (int n = r.range1Start; n <= r.range1End; ++n) {
            if (!rules_cache.contains(n))
                rules_cache[n] = std::vector<Rule>();
            rules_cache[n].push_back(r);
        }
        for (int n = r.range2Start; n <= r.range2End; ++n) {
            if (!rules_cache.contains(n))
                rules_cache[n] = std::vector<Rule>();
            rules_cache[n].push_back(r);
        }
    }
}

void task16::solve1() {

    int sum = 0;
    for (auto t : tickets) {
        for (auto v : t) {
            if (!rules_cache.contains(v))
                sum += v;
        }
    }
    // Correct: 23054
    std::cout << "Sum: " << sum << std::endl;
}

void task16::solve2() {
    // Remove non valid
    for (int i = 0; i < tickets.size(); ++i) {
        for (auto v : tickets[i]) {
            if (!rules_cache.contains(v)) {
                tickets.erase(tickets.begin() + i);
                i--;
                break;
            }
        }
    }

    // For each ticket field assign its possible field names
    std::vector<std::multiset<std::string>> rule_assignmets;
    rule_assignmets.resize(my_ticket.size());
    for (size_t i = 0; i < tickets.size(); ++i) {
        ticket_t& t = tickets[i];
        for (size_t i = 0; i < t.size(); ++i) {
            const auto &rls = rules_cache[t[i]];
            for (const auto& r : rls) {
                rule_assignmets[i].insert(r.name);
            }
        }
    }

    // Convert to vector of tuples: <field_index> and <set of possible names>,
    // so that we will be able to sort by number of possible fields without loosing
    // field index on ticket.
    // Also, remove all possible names with counts fewer than total ticket count.
    using assign_t = std::tuple<int, std::multiset<std::string>>;
    std::vector<assign_t> sorted_rule_assignmets;
    for(int n = 0; n < rule_assignmets.size(); ++n) {
        auto& set = rule_assignmets[n];
        for (Rule& r : rules) {
            if (set.count(r.name) != tickets.size()) {
                set.erase(r.name);
            }
        }
        if (rule_assignmets[n].size() == 0)
            throw "Someting wrong!";
        sorted_rule_assignmets.push_back({n, set});
    }

    // Sort
    std::sort(sorted_rule_assignmets.begin(), sorted_rule_assignmets.end(),
              [](const auto& r1, const auto& r2)
              {
        const auto& s1 = std::get<1>(r1);
        const auto& s2 = std::get<1>(r2);
        return s1.size() < s2.size();
    });

    // Iterate sorted rules and assign name to appropriate indexs.
    std::set<std::string> taken;
    std::unordered_map<std::string, int> final_field_mapping;
    for (size_t i = 0; i < sorted_rule_assignmets.size(); ++i) {
        int index = std::get<0>(sorted_rule_assignmets[i]);
        const auto& rule_set = std::get<1>(sorted_rule_assignmets[i]);
        for (Rule& r : rules) {
            if (!rule_set.contains(r.name))
                continue;
            if (taken.contains(r.name))
                continue;
            taken.insert(r.name);
            final_field_mapping[r.name] = index;
            std::cout << index << ": " << r.name << std::endl;
        }
    }

    // Multiply departure filds on our ticket.
    uint64_t solution =
            (uint64_t)my_ticket[final_field_mapping["departure station"]] *
        my_ticket[final_field_mapping["departure time"]] *
        my_ticket[final_field_mapping["departure date"]] *
        my_ticket[final_field_mapping["departure platform"]] *
        my_ticket[final_field_mapping["departure track"]] *
        my_ticket[final_field_mapping["departure location"]];

    // 1740264017
    // 150179073
    std::cout << "Solution2: " << solution << std::endl;
}
