#include "graph.h"
#include "linkanalysis.h"

#include <algorithm>
#include <cmath>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>

using fmt::print;
using std::vector;

hits get_hits(const graph &g) {
    const auto N = g.num_node();

    auto update = [=](const vector<float> &in, auto getneighbors) {
        auto tgt = vector<float>(N, 0);
        double accu = 0;
        for (int i = 0; i < N; ++i) {
            auto neighbors = getneighbors(i);
            tgt[i] = std::accumulate(
                neighbors.begin(), neighbors.end(), 0.0f,
                [&](auto sum, auto &node) { return sum + in[node.first]; });
            accu += tgt[i] * tgt[i];
        }
        accu = std::sqrt(accu);
        std::for_each(tgt.begin(), tgt.end(), [=](float &i) { i /= accu; });
        return tgt;
    };

    auto auth = vector<float>(N, 1);
    auto hub = vector<float>(N, 1);
    double residual = 1;
    int step = 0;
    while (residual > 0.0001) {
        auto auth_n = update(hub, [&](int i) { return g.in_neighbors(i); });
        auto hub_n = update(auth, [&](int i) { return g.out_neighbors(i); });
        residual = 0;
        for (int i = 0; i < N; ++i) {
            residual +=
                std::fabs(auth[i] - auth_n[i]) + std::abs(hub[i] - hub_n[i]);
        }
        auth = auth_n;
        hub = hub_n;
        ++step;
        // residual = 1;
        // if (step == 100)
        //     break;
    }
    print("hits : {} step\n", step);
    return hits{.authority = auth, .hubness = hub};
}