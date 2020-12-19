//
// Created by marci_000 on 17.12.2020.
//

#ifndef ADVENTOFCODE2020_TASK17_H
#define ADVENTOFCODE2020_TASK17_H

#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <tuple>

// function has to live in the std namespace
// so that it is picked up by argument-dependent name lookup (ADL).
namespace std{
    namespace
    {

        // Code from boost
        // Reciprocal of the golden ratio helps spread entropy
        //     and handles duplicates.
        // See Mike Seymour in magic-numbers-in-boosthash-combine:
        //     https://stackoverflow.com/questions/4948780

        template <class T>
        inline void hash_combine(std::size_t& seed, T const& v)
        {
            seed ^= hash<T>()(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }

        // Recursive template code derived from Matthieu M.
        template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
        struct HashValueImpl
        {
            static void apply(size_t& seed, Tuple const& tuple)
            {
                HashValueImpl<Tuple, Index-1>::apply(seed, tuple);
                hash_combine(seed, get<Index>(tuple));
            }
        };

        template <class Tuple>
        struct HashValueImpl<Tuple,0>
        {
            static void apply(size_t& seed, Tuple const& tuple)
            {
                hash_combine(seed, get<0>(tuple));
            }
        };
    }

    template <typename ... TT>
    struct hash<std::tuple<TT...>>
    {
        size_t
        operator()(std::tuple<TT...> const& tt) const
        {
            size_t seed = 0;
            HashValueImpl<std::tuple<TT...> >::apply(seed, tt);
            return seed;
        }

    };
}

class task17 {
    using index = std::tuple<int, int, int, int>;
    using matrix_4d_t = std::unordered_map<index, char>;
    matrix_4d_t internal_cube;

    char& get_at(matrix_4d_t& cube, int x, int y, int z, int w) {
        index ind{x, y, z, w};
        if (!cube.contains(ind))
            cube[ind] = '.';
        return cube[ind];
    }
    bool exists(matrix_4d_t& cube, int x, int y, int z, int w) {
        index ind{x, y, z, w};
        if (!cube.contains(ind))
           return false;
        return true;
    }
    std::multiset<char> get_around_fields(matrix_4d_t& cube, int x, int y, int z, int w);
    int minx,miny,minz,minw;
    int maxx,maxy,maxz,maxw;
    bool solve_2_mode = false;
public:
    task17();
    void solve1();
    void solve2();
};


#endif //ADVENTOFCODE2020_TASK17_H
