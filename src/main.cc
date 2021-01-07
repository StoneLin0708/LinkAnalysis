#include "linkanalysis.h"
#include <chrono>
#include <cstdio>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <string>

using fmt::print;
using std::string;

struct measure {
    using clock = std::chrono::high_resolution_clock;
    measure(string msg) : msg(msg) {
        print("-----{}-----\n", msg);
        start = clock::now();
    }
    ~measure() {
        auto now = clock::now();
        print("{} ms\n-----{}-----\n",
              std::chrono::duration_cast<std::chrono::milliseconds>(now - start)
                  .count(),
              msg);
    }
    string msg;
    clock::time_point start;
};

int main(int argc, char const *argv[]) {
    if (argc < 2)
        return 0;
    auto g = graph::from_file(argv[1]);
    bool fout = argc == 4;
    auto out = fout ? fopen(argv[2], "w") : stdout;
    auto cmd = fout ? string(argv[3]) : "";

    auto N = g.num_node();

    print("\n{}:\n", argv[1]);
    print("number of node = {}\n", g.num_node());
    print("density = {:.4f}\n", g.density());

    if (!fout || cmd == "authority" || cmd == "hubness") {
        auto m = measure("hits");
        auto hits = get_hits(g);
        if (!fout || cmd == "authority")
            printvec(out, hits.authority, "{:.3f} ",
                     fout ? "" : "authority : \n");
        if (!fout || cmd == "hubness")
            printvec(out, hits.hubness, "{:.3f} ", fout ? "" : "hubness : \n");
    }

    if (!fout || cmd == "pagerank") {
        auto m = measure("page rank");
        auto pr = pagerank(g, 0.85);
        printvec(out, pr, "{:.3f} ", fout ? "" : "pagerank");
    }

    if (!fout || cmd == "simrank") {
        auto m = measure("sim rank");
        auto sr = simrank(g, 0.6);
        printmat(out, sr, N, "{:.3f} ", fout ? "" : "simrank : \n");
    }

    return 0;
}