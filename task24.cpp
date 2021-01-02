//
// Created by marci_000 on 01.01.2021.
//

#include "task24.h"

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <unordered_map>
#include <algorithm>

task24::task24() {
    std::ifstream ifs("../data24.txt");
    std::string line;
    while(std::getline(ifs, line)) {
        path_t path;
        for (std::size_t i = 0; i < line.size(); ) {
            std::string s = line.substr(i, 2);
            auto mapping = std::find_if(mapDirToStr.begin(), mapDirToStr.end(), [&](auto& mp) { return s.starts_with(std::get<1>(mp)); });
            if (mapping == mapDirToStr.end())
                throw "Invalid mapping?!?";
            i += std::get<1>(*mapping).size();
            if (i >= line.size()+1)
                throw "Something wrong!";
            path.push_back(std::get<0>(*mapping));
        }
        paths.push_back(std::move(path));
    }
}

void task24::solve1() {
    std::unordered_map<hex_pos, Tile> tiles = generateTileMap();

    int count = 0;
    for (const auto& [hp, tile] : tiles) {
        if (tile.color == TileColor::black)
            count++;
    }

    // correct: 473
    std::cout << "Solution1: " << count << std::endl;
}

std::unordered_map<task24::hex_pos, task24::Tile> task24::generateTileMap() {
    std::unordered_map<hex_pos, Tile> tiles;
    for (const auto& path : paths) {
        std::string s;
        hex_pos cur_pos {0, 0};
        for (const auto& dir : path) {
            auto off = DirToPos(cur_pos, dir);
            cur_pos.x += off.x;
            cur_pos.y += off.y;
        }
        if (tiles.contains(cur_pos)) {
            auto& tile = tiles.at(cur_pos);
            tile.toggle();
        }
        else {
            tiles.insert({cur_pos, {TileColor::black, cur_pos}});
        }

        // This operation will generate new - not in the tile map white tiles, which
        // will be used in the solution 2.
        [[maybe_unused]]auto tile_set = getNearbyTiles(tiles, cur_pos);

        int count_b = 0, count_w=0;
        for (const auto& [hp, tile] : tiles) {
            if (tile.color == TileColor::black)
                count_b++;
            if (tile.color == TileColor::white)
                count_w++;
        }
    }
    return tiles;
}

void task24::solve2() {
    std::unordered_map<hex_pos, Tile> tiles = generateTileMap();

    for (int iter = 0; iter < 100; ++iter) {
        for (auto& [pos, tile]: tiles) {
            auto tileSet = getNearbyTiles(tiles, tile.position);
            //int white = std::count_if(tileSet.begin(), tileSet.end(), [](auto& t){ return t.color == TileColor::white;});
            int black = std::count_if(tileSet.begin(), tileSet.end(), [](auto& t){ return t.color == TileColor::black;});
            if (tile.color == TileColor::black) {
                if (black == 0 || black > 2) {
                    tile.toggle();
                }
            }
            else {
                if (black == 2) {
                    tile.toggle();
                }
            }
        }
    }

    int count = 0;
    for (const auto& [hp, tile] : tiles) {
        if (tile.color == TileColor::black)
            count++;
    }

    // correct: ?
    std::cout << "Solution2: " << count << std::endl;
}

std::multiset<task24::Tile> task24::getNearbyTiles(std::unordered_map<hex_pos, Tile> &tiles, hex_pos hexPos) {
    std::multiset<task24::Tile> resSet;

    std::array dirs = {Direction::e, Direction::se, Direction::sw,
                       Direction::w, Direction::nw, Direction::ne};
    for (auto dir : dirs) {
        auto off = DirToPos(hexPos, dir);
        hex_pos hexNewPos = hexPos;
        hexNewPos.x += off.x;
        hexNewPos.y += off.y;

        if (!tiles.contains(hexNewPos))
            tiles.insert({hexNewPos, {TileColor::white, hexNewPos}});
        resSet.insert(tiles.at(hexNewPos));
    }

    return resSet;
}
