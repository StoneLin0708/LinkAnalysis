#include "graph.h"
#include "linkanalysis.h"
#include <algorithm>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <iostream>
#include <numeric>
#include <vector>
// #include <fmt/ranges.h>

using fmt::print;
using std::vector;

/*
 *    a  b  c
 * a  0  0  1
 * b  1  0  0
 * c .5 .5  0
 *
 * a->c
 * b->a
 * c->a
 * c->b
 */

// 1  1 .15/6 + .85 x 0
// 2  1 .15/6 + .85 x 1
// 3  1 .15/6 + .85 x 1
// 4  1 .15/6 + .85 x 1
// 5  1 .15/6 + .85 x 1
// 6  1 .15/6 + .85 x 1

vector<float> pagerank(const graph &g, float damping) {
    graph ng = g;
    const auto N = g.num_node();
    vector<float> pr(N, 1.0f / N);

    for (int i = 0; i < N; ++i) {
        auto s = g.num_out(i);
        if (s == 0)
            continue;
        for (auto j : ng.out_neighbors(i))
            ng.update_edge(i, j.first, ng(i, j.first) / s);
    }

    float diff = 1;
    int step = 0;
    while (diff > 0.0001) {
        vector<float> new_pr(N, 0);
        for (auto i = 0; i < N; ++i) {
            for (auto j : ng.in_neighbors(i)) {
                new_pr[i] += pr[j.first] * j.second;
            }
        }
        const double df = (1.0 - damping) / N;
        // printvec(new_pr, "{:.4f},", "new pr bn");
        std::transform(new_pr.begin(), new_pr.end(), new_pr.begin(),
                       [=](auto a) { return df + a * damping; });
        // printvec(new_pr, "{:.4f},", "new pr af");
        diff = 0;
        for (auto i = 0; i < N; ++i) {
            diff += std::fabs(pr[i] - new_pr[i]);
        }
        pr = new_pr;
        ++step;
    }
    print("page rank : {} step\n", step);
    return pr;
}