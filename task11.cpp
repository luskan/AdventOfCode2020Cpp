//
// Created by marcin on 11.12.2020.
//

#include "task11.h"

#include <fstream>
#include <iostream>

task11::task11() {
  std::ifstream ifs("../data11.txt");
  std::string line;
  while(std::getline(ifs, line)) {
    Row row;
    for (size_t i = 0; i < line.size(); ++i) {
      row.push_back(line.at(i));
    }
    room.push_back(row);
  }
}

void task11::solve1() {
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
          if (around.count('#') >= (part2? 5 :4)) {
            at(roomCopy, x, y) = 'L';
            ++stateChanges;
          }
        }
      }
    }

    room = std::move(roomCopy);

    /*
    for (int y = 0; y < room.size(); ++y) {
      for (int x =0; x < room[0].size(); ++x) {
        std::cout << at(room, x, y);
      }
      std::cout << std::endl;
    }
     */

    if (stateChanges == 0)
      break;
    std::cout << it << std::endl;
  }

  int occupied = 0;
  for (int y = 0; y < room.size(); ++y) {
    for (int x =0; x < room[0].size(); ++x) {
      if(at(room, x, y) == '#')
        occupied++;
    }
  }

  // 4263
  // 3001
  std::cout <<"Occupied : " << occupied << std::endl;
}

void task11::solve2() {
  part2 = true;
  solve1();
}
