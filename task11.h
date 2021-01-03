//
// Created by marcin on 11.12.2020.
//

#ifndef ADVENTOFCODE2020_TASK11_H
#define ADVENTOFCODE2020_TASK11_H

#include <vector>
#include <set>
#include <algorithm>

class Task11 {
  using Row = std::vector<char>;
  std::vector<Row> room;
  char dummy = '?';
  bool part2 = false;

  char& at(std::vector<Row>& rm, int x, int y) {
    if (x < 0 || y < 0)
      return dummy;
    if (x >= rm[0].size() || y >= rm.size())
      return dummy;
    return rm[y][x];
  }

  std::multiset<char>& atAround(std::vector<Row>& rm, int x, int y, std::multiset<char>& res) {
    res.clear();

    if (part2) {

      for (int x1=x - 1; x1 >= 0; --x1) {
        char c = at(rm, x1, y);
        if (c == '.')
          continue;
        res.insert(c);
        break;
      }

      for (int x1=x + 1; x1 < rm[0].size(); ++x1) {
        char c = at(rm, x1, y);
        if (c == '.')
          continue;
        res.insert(c);
        break;
      }

      for (int y1=y - 1; y1 >= 0; --y1) {
        char c = at(rm, x, y1);
        if (c == '.')
          continue;
        res.insert(c);
        break;
      }

      for (int y1=y + 1; y1 < room.size(); ++y1) {
        char c = at(rm, x, y1);
        if (c == '.')
          continue;
        res.insert(c);
        break;
      }

      for (int x1=x - 1, y2=y-1; x1 >= 0 && y2 >= 0; --x1, --y2) {
        char c = at(rm, x1, y2);
        if (c == '.')
          continue;
        res.insert(c);
        break;
      }

      for (int x1=x + 1, y2=y-1; x1 < room[0].size() && y2 >= 0; ++x1, --y2) {
        char c = at(rm, x1, y2);
        if (c == '.')
          continue;
        res.insert(c);
        break;
      }

      for (int x1=x + 1, y2=y+1; x1 < room[0].size() && y2 < room.size(); ++x1, ++y2) {
        char c = at(rm, x1, y2);
        if (c == '.')
          continue;
        res.insert(c);
        break;
      }

      for (int x1=x - 1, y2=y+1; x1 >= 0 && y2 < room.size(); --x1, ++y2) {
        char c = at(rm, x1, y2);
        if (c == '.')
          continue;
        res.insert(c);
        break;
      }
    }
    else {
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

  bool example_data;
public:
  Task11(bool example);
  void solve1();
  void solve2();
};


#endif //ADVENTOFCODE2020_TASK11_H
