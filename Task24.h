//
// Created by marci_000 on 01.01.2021.
//

#ifndef ADVENTOFCODE2020_TASK24_H
#define ADVENTOFCODE2020_TASK24_H

#include <vector>
#include <array>
#include <unordered_map>
#include <set>
#include <string_view>
#include "utils.h"

using namespace std::literals;

class Task24 {
  struct hex_pos {
    int x;
    int y;

    friend bool operator<(const hex_pos &lop, const hex_pos &rop) {
      return std::make_tuple(lop.x, lop.y) < std::make_tuple(rop.x, rop.y);
    }
    friend bool operator==(const hex_pos &lop, const hex_pos &rop) {
      return std::make_tuple(lop.x, lop.y) == std::make_tuple(rop.x, rop.y);
    }
  };
  friend std::hash<Task24::hex_pos>;
  enum class Direction {
    e, se, sw, w, nw, ne
  };
  hex_pos DirToPos(const hex_pos &pos, Direction dir) {
    if (pos.y & 1) {
      switch (dir) {
        case Direction::e:return {1, 0};
        case Direction::se:return {1, 1};
        case Direction::sw:return {0, 1};
        case Direction::w:return {-1, 0};
        case Direction::nw:return {0, -1};
        case Direction::ne:return {1, -1};
      }
    } else {
      switch (dir) {
        case Direction::e:return {1, 0};
        case Direction::se:return {0, 1};
        case Direction::sw:return {-1, 1};
        case Direction::w:return {-1, 0};
        case Direction::nw:return {-1, -1};
        case Direction::ne:return {0, -1};
      }
    }
    throw "Invalid !";
  };
  using path_t = std::vector<Direction>;
  using paths_t = std::vector<path_t>;
  enum class TileColor {
    white, black
  };
  struct Tile {
    TileColor color = TileColor::white;
    hex_pos position = {0, 0};

    Tile(TileColor color, hex_pos position) : color(color), position(position) {}

    void toggle() {
      color = (color == TileColor::white) ? TileColor::black : TileColor::white;
    }

    friend bool operator<(const Tile &lop, const Tile &rop) {
      return std::make_tuple(lop.position.x, lop.position.y, lop.color)
          < std::make_tuple(rop.position.x, rop.position.y, rop.color);
    }
  };

  std::array<std::tuple<Direction, std::string_view>, 6> mapDirToStr{{
      {Direction::se, "se"sv},
      {Direction::nw, "nw"sv},
      {Direction::ne, "ne"sv},
      {Direction::sw, "sw"sv},
      {Direction::e, "e"sv},
      {Direction::w, "w"sv}
  }};

  std::multiset<Task24::Tile> getNearbyTiles(const std::unordered_map<hex_pos, Tile> &tiles, hex_pos hexPos);

  std::unordered_map<hex_pos, Tile> generateTileMap();

  paths_t paths;
  bool example_data;
 public:
  Task24(bool example);
  void Solve1();
  void Solve2();
};

namespace std {
template<>
struct hash<Task24::hex_pos> {
  std::size_t operator()(Task24::hex_pos const &hp) const noexcept {
    return hp.x ^ hp.y;
  }
};
}

#endif //ADVENTOFCODE2020_TASK24_H
