//
// Created by marci_000 on 01.01.2021.
//

#include "task24.h"

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <unordered_map>

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
            auto& tile = tiles[cur_pos];
            tile.toggle();
        }
        else {
            tiles[cur_pos] = {TileColor::black};
        }

        int count_b = 0, count_w=0;
        for (const auto& [hp, tile] : tiles) {
            if (tile.color == TileColor::black)
                count_b++;
            if (tile.color == TileColor::white)
                count_w++;
        }
        std::cout << "#" << n++ << ", b=" << count_b << ", w=" << count_w << ", " << cur_pos.x << ";" << cur_pos.y << " - ";
        std::cout << s << std::endl;
    }

    int count = 0;
    for (const auto& [hp, tile] : tiles) {
        if (tile.color == TileColor::black)
            count++;
    }

    std::cout << "Solution1: " << count << std::endl;
}

void task24::solve2() {

}
