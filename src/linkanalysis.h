#pragma once
#include "graph.h"
#include <fmt/format.h>
#include <string>
#include <tuple>
#include <vector>

struct hits {
    std::vector<float> authority;
    std::vector<float> hubness;
};

hits get_hits(const graph &g);

std::vector<float> pagerank(const graph &g, float damping);

std::vector<float> simrank(const graph &g, float decay);

template <typename Iter, typename Fmt, typename OS>
void printvec(OS os, Iter begin, Iter end, Fmt f,
              const std::string &name = "") {
    fmt::print(os, "{}", name);
    for (; begin != end; ++begin) {
        fmt::print(os, f, *begin);
    }
    fmt::print(os, "\n");
}

template <typename T, typename Fmt, typename OS>
void printvec(OS os, const std::vector<T> &v, Fmt f,
              const std::string &name = "") {
    printvec(os, v.begin(), v.end(), f, name);
}

template <typename T, typename Fmt, typename OS>
void printmat(OS os, const std::vector<T> &v, int N, Fmt f,
              const std::string &name = "") {
    fmt::print(os, "{}", name);
    for (auto begin = v.begin(); begin < v.end(); begin += N) {
        printvec(os, begin, begin + N, f);
    }
}