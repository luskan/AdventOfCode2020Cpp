//
// Created by marcin on 11.12.2020.
//

#include "task11.h"

#include <fstream>
#include <iostream>
#include <string>
#include "utils.h"

Task11::Task11(bool example) {
  example_data = example;
  std::ifstream ifs(example ? "../data/data11_example.txt" : std::string("../") + get_relative_data_path() + "data/data11_task.txt");
  std::string line;
  while (std::getline(ifs, line)) {
    Row row;
    for (size_t i = 0; i < line.size(); ++i) {
      row.push_back(line.at(i));
    }
    roomBase.push_back(row);
  }
}

void Task11::solve() {
  std::vector<Row> room(roomBase);
  std::multiset<char> around;
  for (int it = 0; it < 100000; ++it) {
    int stateChanges = 0;
    std::vector<Row> roomCopy = room;
    for (int x = 0; x < room[0].size(); ++x) {
      for (int y = 0; y < room.size(); ++y) {
        if (at(room, x, y) == 'L') {
          atAround(room, x, y, around);
          if (around.count('#') == 0) {
            at(roomCopy, x, y) = '#';
            ++stateChanges;
          }
        } else if (at(room, x, y) == '#') {
          atAround(room, x, y, around);
          if (around.count('#') >= (part2 ? 5 : 4)) {
            at(roomCopy, x, y) = 'L';
            ++stateChanges;
          }
        }
      }
    }

    room = std::move(roomCopy);

    if (stateChanges == 0)
      break;
  }

  int occupied = 0;
  for (int y = 0; y < room.size(); ++y) {
    for (int x = 0; x < room[0].size(); ++x) {
      if (at(room, x, y) == '#')
        occupied++;
    }
  }

  if (part2) {
    verify_result(occupied, example_data ? 26 : get_data_result<int>(11, 2));
    std::cout << " part2: occupied = " << occupied << std::endl;
  } else {
    verify_result(occupied, example_data ? 37 : get_data_result<int>(11, 1));
    std::cout << " part1: occupied = " << occupied << std::endl;
  }
}

void Task11::Solve1() {
  Timer opt_timer;
  solve();
}

void Task11::Solve2() {
  Timer opt_timer;
  part2 = true;
  solve();
}
std::multiset<char> &Task11::atAround(std::vector<Row> &rm, int x, int y, std::multiset<char> &res) {
  res.clear();

  if (part2) {

    for (int x1 = x - 1; x1 >= 0; --x1) {
      char c = at(rm, x1, y);
      if (c == '.')
        continue;
      res.insert(c);
      break;
    }

    for (int x1 = x + 1; x1 < rm[0].size(); ++x1) {
      char c = at(rm, x1, y);
      if (c == '.')
        continue;
      res.insert(c);
      break;
    }

    for (int y1 = y - 1; y1 >= 0; --y1) {
      char c = at(rm, x, y1);
      if (c == '.')
        continue;
      res.insert(c);
      break;
    }

    for (int y1 = y + 1; y1 < rm.size(); ++y1) {
      char c = at(rm, x, y1);
      if (c == '.')
        continue;
      res.insert(c);
      break;
    }

    for (int x1 = x - 1, y2 = y - 1; x1 >= 0 && y2 >= 0; --x1, --y2) {
      char c = at(rm, x1, y2);
      if (c == '.')
        continue;
      res.insert(c);
      break;
    }

    for (int x1 = x + 1, y2 = y - 1; x1 < rm[0].size() && y2 >= 0; ++x1, --y2) {
      char c = at(rm, x1, y2);
      if (c == '.')
        continue;
      res.insert(c);
      break;
    }

    for (int x1 = x + 1, y2 = y + 1; x1 < rm[0].size() && y2 < rm.size(); ++x1, ++y2) {
      char c = at(rm, x1, y2);
      if (c == '.')
        continue;
      res.insert(c);
      break;
    }

    for (int x1 = x - 1, y2 = y + 1; x1 >= 0 && y2 < rm.size(); --x1, ++y2) {
      char c = at(rm, x1, y2);
      if (c == '.')
        continue;
      res.insert(c);
      break;
    }
  } else {
    res.insert(at(rm, x - 1, y - 1));
    res.insert(at(rm, x, y - 1));
    res.insert(at(rm, x + 1, y - 1));
    res.insert(at(rm, x - 1, y));
    res.insert(at(rm, x + 1, y));
    res.insert(at(rm, x - 1, y + 1));
    res.insert(at(rm, x, y + 1));
    res.insert(at(rm, x + 1, y + 1));
  }
  return res;
}
char &Task11::at(std::vector<Row> &rm, int x, int y) {
  if (x < 0 || y < 0)
    return dummy;
  if (x >= rm[0].size() || y >= rm.size())
    return dummy;
  return rm[y][x];
}
