//
// Created by marcin on 06.12.2020.
//

#include <fstream>
#include <iostream>
#include "task1.h"

void Task1::solve1() {

  for (size_t i = 0; i < input.size(); ++i) {
    for (size_t n = i + 1; n < input.size(); ++n) {
      int vi = input[i];
      int vn = input[n];
      if (vi + vn == 2020) {
        std::cout << vi << " + " << vn << " = " << 2020 << std::endl;
        std::cout << vi << " * " << vn << " = " << vi*vn << std::endl;
      }
    }
  }
}

void Task1::solve2() {

  for (size_t i = 0; i < input.size(); ++i) {
    for (size_t n = i + 1; n < input.size(); ++n) {
      for (size_t k = n + 1; k < input.size(); ++k) {
        int vi = input[i];
        int vn = input[n];
        int vk = input[k];
        if (vi + vn + vk == 2020) {
          std::cout << vi << " + " << vn << " + " << vk << " = " << 2020 << std::endl;
          std::cout << vi << " * " << vn << " * " << vk << " = " << vi * vn * vk << std::endl;
        }
      }
    }
  }
}

Task1::Task1() {
  std::ifstream ifs("../data1.txt");
  std::string line;
  while(std::getline(ifs, line)) {
    input.push_back(std::stoi(line));
  }
  std::cout << input.size();
}
