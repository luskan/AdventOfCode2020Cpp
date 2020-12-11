//
// Created by marcin on 10.12.2020.
//

#include "task10.h"
#include <fstream>
#include <iostream>
#include <cmath>

task10::task10() {
  std::ifstream ifs("../data10.txt");
  std::string line;
  while(std::getline(ifs, line)) {
    int v = std::stoi(line);
    entries.push_back(v);
  }
  std::sort(entries.begin(), entries.end());
  entries.push_back(entries.back() + 3);
}

void task10::solve1() {
  std::vector<int> diffs;

  bool b = computeDiffs(entries, diffs);

  auto oneDiffs = std::count_if(diffs.begin(), diffs.end(), [](auto v) { return v == 1; });
  auto threeDiffs = std::count_if(diffs.begin(), diffs.end(), [](auto v) { return v == 3; });
  std::cout << "One diffs: " << oneDiffs << std::endl;
  std::cout << "Three diffs: " << threeDiffs << std::endl;
  std::cout << "mult.: " << oneDiffs*threeDiffs << std::endl;
}



void task10::solve2() {
  /*
  std::vector<int> diffs;
  computeDiffs(entries, diffs);

  u_int64_t wtj = 1;
  std::vector<int> subRange;
  for (size_t i = 0; i < diffs.size() ; ++i) {
    if (diffs[i] == 3)
      continue;
    for (size_t k = i; k < diffs.size() ;++k) {
      if (diffs[k] == 3) {
        i = k;

        std::cout << "-----" << std::endl;
        break;
      }
      else {
        std::cout << diffs[k] << std::endl;
        seqLen++;
      }
    }
  }

  std::cout << "226775649501184" << std::endl;
  std::cout << wtj;
   */
}

void task10::solve2b() {
  std::vector<int> diffs;
  std::vector<int> ents = entries;
  computeDiffs(ents, diffs);

   u_int64_t wtj = 1;

   std::vector<int> subDiffs;
   for (size_t i = 0; i < diffs.size() ; ++i) {
     if (diffs[i] == 3)
       continue;
     subDiffs.clear();
     for (size_t k = i; k < diffs.size() ;++k) {
       if (diffs[k] == 3) {
         subDiffs.push_back(diffs[k]);
         wtj *= compute(0, subDiffs);
         i = k;
         break;
       }
       else {
         subDiffs.push_back(diffs[k]);
       }
     }
   }

  std::cout << wtj;
}

bool task10::computeDiffs(std::vector<int>& inEntries, std::vector<int>& diffs) {
  diffs.resize(inEntries.size(), 0);
  int curJoltage = 0;
  for (size_t n = 0; n < inEntries.size(); ++n) {
    auto v = inEntries[n];
    int diff = v - curJoltage;
    if (diff < 0 || diff > 3)
      return false;
    diffs[n] = diff;
    curJoltage = v;
  }
  return true;
}

u_int64_t task10::compute(int startFrom, std::vector<int>& diffs) {
  u_int64_t total = 1;

  for (size_t i = startFrom; i < diffs.size() - 1; ++i) {
    int diff = diffs[i];
    int nextDiff = diffs[i + 1];
    if (diff == 1 && (nextDiff == 2 || nextDiff == 1) || diff == 2 && (nextDiff == 1)) {

      diffs[i + 1] += diff;
      diffs.erase(diffs.begin() + i);

      total += compute(i,  diffs);

      diffs.insert(diffs.begin() + i, diff);
      diffs[i + 1] -= diff;
    }
  }
  return total;
}
