//
// Created by marci_000 on 17.12.2020.
//

#include "task17.h"

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

task17::task17() {
    std::ifstream ifs("../data17.txt");
    std::string line;
    int y = 0;
    minx = 0;
    miny = 0;
    minz = 0;
    minw = 0;
    maxx = 0;
    maxy = 0;
    maxz = 0;
    maxw = 0;
    while(std::getline(ifs, line)) {
        for (size_t i = 0; i < line.size(); ++i) {
            get_at(internal_cube, i, y, 0, 0) = line[i];
        }
        maxx = std::max(maxx, (int)line.size());
        y++;
    }
    maxy = y;
}

void task17::solve1() {



    for (int step = 0; step < 6; ++step) {
        matrix_4d_t temp;

        minz--;
        maxz++;
        miny--;
        maxy++;
        minx--;
        maxx++;
        if (solve_2_mode) {
            minw--;
            maxw++;
        }

        for (int w = minw; w <= maxw; ++w) {
            for (int z = minz; z <= maxz; ++z) {
                for (int y = miny; y <= maxy; ++y) {
                    for (int x = minx; x <= maxx; ++x) {

                        auto around = get_around_fields(internal_cube, x, y, z, w);
                        char c = exists(internal_cube, x, y, z, w) ? get_at(internal_cube, x, y, z, w) : '.';
                        if (c == '#') {
                            int active_around = around.count('#');
                            if (active_around == 2 || active_around == 3)
                                get_at(temp, x, y, z, w) = '#';
                        } else if (c == '.') {
                            int active_around = around.count('#');
                            if (active_around == 3)
                                get_at(temp, x, y, z, w) = '#';
                        } else {
                            throw "Weired!";
                        }
                    }
                }
            }
        }

        internal_cube = std::move(temp);
    }

    int total_active = 0;
    for(auto& [key, value] : internal_cube) {
        if (value == '#')
            total_active++;
    }
    // Correct 218
    std::cout << "Total active: " << total_active << std::endl;
}

void task17::solve2() {
    solve_2_mode = true;
    //1908
    solve1();
}

std::multiset<char> task17::get_around_fields(matrix_4d_t& cube, int x, int y, int z, int w) {
    std::multiset<char> res;
    for (int nw = w - 1; nw <= w + 1; ++nw) {
        for (int nz = z - 1; nz <= z + 1; ++nz) {
            for (int ny = y - 1; ny <= y + 1; ++ny) {
                for (int nx = x - 1; nx <= x + 1; ++nx) {
                    if (nx == x && ny == y && nz == z && nw == w)
                        continue;
                    if (exists(cube, nx, ny, nz, nw)) {
                        res.insert(get_at(cube, nx, ny, nz, nw));
                    }
                }
            }
        }
    }
    return res;
}
