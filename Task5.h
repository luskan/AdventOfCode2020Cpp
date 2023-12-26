//
// Created by marcin on 06.12.2020.
//

#ifndef ADVENTOFCODE2020_TASK5_H
#define ADVENTOFCODE2020_TASK5_H

#include <string>
#include <vector>

class Task5 {
  std::vector<std::string> entries;

  struct SeatPos {
    int row;
    int col;
    int id;
  };

  bool example_data;

 public:
  Task5(bool example);
  void Solve1();
  void Solve2();

  void computeSeats(std::vector<SeatPos> &vec);

  int binaryPos(const char *begin,
                const char *end,
                char firstHalfChar, char secondHalfChar, int range);

  bool isTaken(int id, std::vector<SeatPos> &vector);
};

#endif //ADVENTOFCODE2020_TASK5_H
