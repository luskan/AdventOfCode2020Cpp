//
// Created by Marcin Jędrzejewski on 12/12/2020.
//
#define _USE_MATH_DEFINES // for C++

#include "task12.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <complex>

#include <cmath>
#include "utils.h"

Task12::Task12(bool example) {
  example_data = example;
  std::ifstream ifs(example ? "../data/data12_example.txt" : "../data/data12_task.txt");
  std::string line;
  std::regex rg(R"((\w)(\d+))");
  while (std::getline(ifs, line)) {
    std::smatch sm;
    if (std::regex_match(line, sm, rg)) {
      data d;
      d.type = sm[1].str()[0];
      d.arg = std::stoi(sm[2]);
      entries.push_back(d);
    } else {
      throw "Something wrong with parsing!";
    }
  }
}

void Task12::solve1() {
  int x = 0;
  int y = 0;
  int course = 90;

  for (size_t i = 0; i < entries.size(); ++i) {
    data &d = entries[i];
    switch (d.type) {
      case 'N':y += d.arg;
        break;
      case 'S':y -= d.arg;
        break;
      case 'E':x += d.arg;
        break;
      case 'W':x -= d.arg;
        break;
      case 'L':course -= d.arg;
        while (course < 0)
          course = 360 - (-course);
        break;
      case 'R':course += d.arg;
        while (course >= 360)
          course = course - 360;
        break;
      case 'F':
        switch (course) {
          case 0:y += d.arg;
            break;
          case 90:x += d.arg;
            break;
          case 180:y -= d.arg;
            break;
          case 270:x -= d.arg;
            break;
          default:throw "Invalid course!";
        }
        break;
      default:throw "Invalid instruction!";
    }
  }

  auto val = std::abs(x) + std::abs(y);
  verify_result(val, example_data ? 25 : 1010);
  std::cout << " part1: result = " << val << std::endl;
}

void Task12::solve2() {
  int wp_x = 10;
  int wp_y = 1;

  int ship_x = 0;
  int ship_y = 0;

  for (size_t i = 0; i < entries.size(); ++i) {
    data &d = entries[i];
    switch (d.type) {
      case 'N':wp_y += d.arg;
        break;
      case 'S':wp_y -= d.arg;
        break;
      case 'E':wp_x += d.arg;
        break;
      case 'W':wp_x -= d.arg;
        break;
      case 'L':
      case 'R': {
        std::complex pt(wp_x, wp_y);
        pt *= std::polar(1.0, (d.type == 'L' ? 1 : -1) * d.arg * M_PI / 180.0);
        wp_x = pt.real();
        wp_y = pt.imag();
        break;
      }
      case 'F':ship_x += d.arg * wp_x;
        ship_y += d.arg * wp_y;
        break;
    }
  }

  auto val = std::abs(ship_x) + std::abs(ship_y);
  verify_result(val, example_data ? 286 : 52742);
  std::cout << " part2: result = " << val << std::endl;
}
