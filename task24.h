//
// Created by marci_000 on 01.01.2021.
//

#ifndef ADVENTOFCODE2020_TASK24_H
#define ADVENTOFCODE2020_TASK24_H

#include <vector>
#include <array>
#include "utils.h"

class task24 {
    struct hex_pos {
        int x;
        int y;

        friend bool operator<(const hex_pos& lop, const hex_pos& rop) {
            return std::make_tuple(lop.x, lop.y) < std::make_tuple(rop.x, rop.y);
        }
        friend bool operator==(const hex_pos& lop, const hex_pos& rop) {
            return std::make_tuple(lop.x, lop.y) == std::make_tuple(rop.x, rop.y);
        }
    };
    friend std::hash<task24::hex_pos>;
    enum class Direction {
        e, se, sw, w, nw, ne
    };
    hex_pos DirToPos(const hex_pos& pos, Direction dir) {
        if (pos.y&1) {
            switch (dir) {
                case Direction::e:
                    return {1, 0};
                case Direction::se:
                    return {1, 1};
                case Direction::sw:
                    return {0, 1};
                case Direction::w:
                    return {-1, 0};
                case Direction::nw:
                    return {0, -1};
                case Direction::ne:
                    return {1, -1};
            }
        }
        else {
            switch (dir) {
                case Direction::e:
                    return {1, 0};
                case Direction::se:
                    return {0, 1};
                case Direction::sw:
                    return {-1, 1};
                case Direction::w:
                    return {-1, 0};
                case Direction::nw:
                    return {-1, -1};
                case Direction::ne:
                    return {0, -1};
            }
        }
    };
    using path_t = std::vector<Direction>;
    using paths_t = std::vector<path_t>;
    enum class TileColor {
        white, black
    };
    struct Tile {
        TileColor color = TileColor::white;

        Tile() {}
        Tile(TileColor color) : color(color) {}

        void toggle() {
            color = (color == TileColor::white) ? TileColor::black : TileColor::white;
        }
    };

    std::array<std::tuple<Direction, std::string>, 6> mapDirToStr {{
           {Direction::se, "se"},
           {Direction::nw, "nw"},
           {Direction::ne, "ne"},
           {Direction::sw, "sw"},
           {Direction::e, "e"},
           {Direction::w, "w"}
    }};

    paths_t paths;
public:
    task24();
    void solve1();
    void solve2();
};

namespace std
{
    template<> struct hash<task24::hex_pos>
    {
        std::size_t operator()(task24::hex_pos const& hp) const noexcept
        {
            return hp.x ^ hp.y;
        }
    };
}

#endif //ADVENTOFCODE2020_TASK24_H
