//
// Created by marci_000 on 01.01.2021.
//

#include "Task24.h"

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <unordered_map>
#include <algorithm>
#include "utils.h"

Task24::Task24(bool example) {
  example_data = example;

  std::ifstream ifs(example ? "../data/data24_example.txt" : std::string("../") + get_relative_data_path() + "data/data24_task.txt");
  std::string line;
  while (std::getline(ifs, line)) {
    path_t path;
    for (std::size_t i = 0; i < line.size();) {
      std::string s = line.substr(i, 2);
      auto mapping = std::find_if(mapDirToStr.begin(),
                                  mapDirToStr.end(),
                                  [&](auto &mp) { return s.starts_with(std::get<1>(mp)); });
      if (mapping == mapDirToStr.end())
        throw "Invalid mapping?!?";
      i += std::get<1>(*mapping).size();
      if (i >= line.size() + 1)
        throw "Something wrong!";
      path.push_back(std::get<0>(*mapping));
    }
    paths.push_back(std::move(path));
  }
}

void Task24::Solve1() {
  Timer opt_timer;
  std::unordered_map<hex_pos, Tile> tiles = generateTileMap();

  int count = 0;
  for (const auto&[hp, tile] : tiles) {
    if (tile.color == TileColor::black)
      count++;
  }

  verify_result(count, example_data ? 10 : get_data_result<uint64_t>(24, 1));
  std::cout << " part1: count = " << count << std::endl;
}

std::unordered_map<Task24::hex_pos, Task24::Tile> Task24::generateTileMap() {
  std::unordered_map<hex_pos, Tile> tiles;
  for (const auto &path : paths) {
    std::string s;
    hex_pos cur_pos{0, 0};
    for (const auto &dir : path) {
      auto off = DirToPos(cur_pos, dir);
      cur_pos.x += off.x;
      cur_pos.y += off.y;
    }

    if (tiles.contains(cur_pos)) {
      auto &tile = tiles.at(cur_pos);
      tile.toggle();
      if (tile.color == TileColor::white)
        tiles.erase(cur_pos);
    } else {
      tiles.insert({cur_pos, {TileColor::black, cur_pos}});
    }
  }

  return tiles;
}

void Task24::Solve2() {
  Timer opt_timer;
  std::unordered_map<hex_pos, Tile> tiles = generateTileMap();

  for (int iter = 1; iter <= 100; ++iter) {
    std::unordered_map<hex_pos, Tile> tiles_next;

    for (const auto&[pos, tile]: tiles) {
      if (tile.color == TileColor::white)
        continue;

      auto tileSet = getNearbyTiles(tiles, tile.position);
      int blacks = std::count_if(tileSet.begin(), tileSet.end(), [](auto &t) { return t.color == TileColor::black; });

      Tile newTile = tile;

      // Rule 1 for turning black to white
      if (blacks == 0 || blacks > 2) {
        newTile.color = TileColor::white;
      }

      // Rule 2 for turning white to black (if exactly two black are nearby). Becasue our tile map does not store
      // white tiles (missing tile is considered to be white), this rule is first finding all nearby whites, and
      // for each nearby white it searches its nearby tiles - if there are exactly two blacks then rule two is
      // applied and new black tile is inserted.
      for (const auto &ts : tileSet) {
        if (ts.color == TileColor::white) {
          auto tileSet2 = getNearbyTiles(tiles, ts.position);
          int blacks2 =
              std::count_if(tileSet2.begin(), tileSet2.end(), [](auto &t) { return t.color == TileColor::black; });
          if (blacks2 == 2) {
            Tile new_ts{TileColor::black, ts.position};
            auto[it, inserted] = tiles_next.insert({ts.position, new_ts});
            if (!inserted)
              it->second = new_ts;
          }
        }
      }

      auto[it, inserted] = tiles_next.insert({newTile.position, newTile});
      if (!inserted)
        it->second = newTile;
    }

    tiles = std::move(tiles_next);
  }

  int count = 0;
  for (const auto&[hp, tile] : tiles) {
    if (tile.color == TileColor::black)
      count++;
  }

  verify_result(count, example_data ? 2208 : get_data_result<uint64_t>(24, 2));
  std::cout << " part2: count = " << count << std::endl;
}

std::multiset<Task24::Tile> Task24::getNearbyTiles(const std::unordered_map<hex_pos, Tile> &tiles, hex_pos hexPos) {
  std::multiset<Task24::Tile> resSet;

  std::array dirs = {Direction::e, Direction::se, Direction::sw,
      Direction::w, Direction::nw, Direction::ne};
  for (auto dir : dirs) {
    auto off = DirToPos(hexPos, dir);
    auto hexNewPos = hexPos;
    hexNewPos.x += off.x;
    hexNewPos.y += off.y;

    if (!tiles.contains(hexNewPos)) {
      resSet.insert({TileColor::white, hexNewPos});
      continue;
    }
    resSet.insert(tiles.at(hexNewPos));
  }
  return resSet;
}
