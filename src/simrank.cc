#include <algorithm>

#include "graph.h"
#include "linkanalysis.h"
#include <cmath>
#include <fmt/format.h>
#include <fmt/ranges.h>

using fmt::print;
using std::vector;

std::vector<float> simrank(const graph &g, float decay) {
    int N = g.num_node();
    std::vector<float> sr(N * N, 0);
    for (auto b=sr.begin(); b < sr.end(); b+=N+1)
        *b = 1;

    double diff = 1;
    int step = 0;
    while (diff > 0.0001){
        std::vector<float> new_sr(N * N, 0);

        for (int a = 0; a < N; ++a) {
            for (int b = 0; b < N; ++b) {
                if (a == b) {
                    new_sr[a * N + b] = 1;
                } else {
                    double sum = 0;
                    const auto &Ia = g.in_neighbors(a);
                    const auto &Ib = g.in_neighbors(b);
                    for (const auto &ia : Ia)
                        for (const auto &ib : Ib)
                            sum += sr[ia.first * N + ib.first];
                    new_sr[a * N + b] =
                        (sum != 0) ? decay * sum / (Ia.size() * Ib.size()) : 0;
                }
            }
        }
        diff = 0;
        for (auto i = 0; i < N*N; ++i) {
            diff += std::abs(sr[i] - new_sr[i]);
        }
        sr = new_sr;

        ++step;
    }
    print("sim rank : {} step\n", step);
    return sr;
}