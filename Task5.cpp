//
// Created by marcin on 06.12.2020.
//

#include "Task5.h"

#include <fstream>
#include <iostream>
#include <algorithm>
Task5::Task5() {
  std::fstream fs("../data5.txt");
  std::string line;
  while(std::getline(fs, line)) {
    entries.push_back(line);
  }
}

void Task5::solve1() {
  std::vector<SeatPos> seatPositions;
  std::vector<int> ids;
  computeSeats(seatPositions);
  for (size_t i = 0; i < seatPositions.size(); ++i) {
    ids.push_back(seatPositions[i].id);
  }
  std::sort(ids.begin(), ids.end());
  std::cout << "Highest id: " << ids.back() << std::endl;
}

void Task5::solve2() {
  std::vector<SeatPos> seatPositions;
  computeSeats(seatPositions);
  std::sort(seatPositions.begin(), seatPositions.end(),
            [](const auto& sp1, const auto& sp2) { return sp1.id < sp2.id;  } );
  SeatPos lastSp = seatPositions[0];

  for (int id = 1; id < 8*128; ++id) {
    if (!isTaken(id, seatPositions))
    {
      if (isTaken(id - 1, seatPositions) && isTaken(id + 1, seatPositions))
        std::cout << id << std::endl;
    }
  }
}

void Task5::computeSeats(std::vector<SeatPos>& vec) {
  SeatPos sp;
  for (int n = 0; n < entries.size(); ++n) {
    auto s = entries[n];
    sp.row = binaryPos(s.c_str(), s.c_str() + 7, 'F', 'B', 128);
    sp.col = binaryPos(s.c_str() + 7, s.c_str() + 10, 'L', 'R', 8);
    sp.id = sp.row * 8 + sp.col;
    vec.push_back(sp);
  }
}

int Task5::binaryPos(const char* begin,
                     const char* end,
                     char firstHalfChar, char secondHalfChar, int range) {
  int first = 0;
  int second = range;
  for (auto it = begin; it != end; ++it) {
    char c = *it;
    if (c == firstHalfChar)
      second = (second - first) / 2 + first;
    if (c == secondHalfChar)
      first = (second - first) / 2 + first;
  }
  if (first + 1 != second)
    throw "Some bad binary computation!";
  return first;
}

bool Task5::isTaken(int id, std::vector<SeatPos> &seatPositions) {
  return std::find_if(seatPositions.begin(), seatPositions.end(),
               [=](const auto& sp){ return sp.id == id; }) != seatPositions.end();
}
