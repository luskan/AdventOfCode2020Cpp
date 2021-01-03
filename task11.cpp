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
  std::ifstream ifs(example ? "../data11_example.txt" : "../data11_task.txt");
  std::string line;
  while(std::getline(ifs, line)) {
    Row row;
    for (size_t i = 0; i < line.size(); ++i) {
      row.push_back(line.at(i));
    }
    room.push_back(row);
  }
}

void Task11::solve1() {
  std::multiset<char> around;
  for(int it = 0; it < 100000; ++it) {
    int stateChanges = 0;
    std::vector<Row> roomCopy = room;
    for (int x = 0; x < room[0].size(); ++x) {
      for (int y = 0; y < room.size(); ++y) {
        if (at(room, x, y) == 'L') {
          atAround(room, x, y, around);
          if ( around.count('#') == 0 ) {
            at(roomCopy, x, y) = '#';
            ++stateChanges;
          }
        }
        else if (at(room, x, y) == '#') {
          atAround(room, x, y, around);
          if (around.count('#') >= (part2 ? 5 :4)) {
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
    for (int x =0; x < room[0].size(); ++x) {
      if(at(room, x, y) == '#')
        occupied++;
    }
  }

  if (part2) {
   // verify_result(occupied, example_data ? 26 : 2072);
    std::cout << " part2: occupied = " << occupied << std::endl;
  }
  else {
    verify_result(occupied, example_data ? 37 : 2354);
    std::cout <<" part1: occupied = " << occupied << std::endl;
  }
}

void Task11::solve2() {
  part2 = true;
  solve1();
}
