#include "graph.h"

#include <fmt/format.h>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <set>
#include <string>
#include <tuple>
#include <vector>

using fmt::format;
using fmt::print;
using std::string;
using std::vector;

std::vector<std::string> split(const std::string &str, char delim) {
    std::vector<std::string> strings;
    size_t start;
    size_t end = 0;
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {
        end = str.find(delim, start);
        strings.push_back(str.substr(start, end - start));
    }
    return strings;
}

graph::graph(int n) : _in_edges(n), _out_edges(n), _num_node(n) {}

graph::graph(const graph &o)
    : _in_edges(o._in_edges), _out_edges(o._out_edges), _num_node(o._num_node) {
}

graph graph::from_file(string path) {
    std::ifstream ifs(path);
    string ins;
    vector<std::pair<string, string>> d;
    std::set<string> names;

    while (std::getline(ifs, ins)) {
        auto sp = split(ins, ',');
        if (sp.size() != 2)
            throw std::runtime_error(fmt::format("graph read error : {}", ins));
        names.insert(sp[0]);
        names.insert(sp[1]);
        d.push_back({sp[0], sp[1]});
    }

    graph g(names.size());
    g.idx2name = vector<string>(names.begin(), names.end());
    for (int i = 0; i < g._num_node; ++i)
        g.name2idx[g.idx2name[i]] = i;
    std::for_each(d.begin(), d.end(), [&](auto i) {
        g.add_edge(g.name2idx[i.first], g.name2idx[i.second], 1);
    });
    return g;
}

float graph::operator()(int i, int j) const {
    const auto &o = _out_edges[i];
    const auto r =
        std::find_if(o.begin(), o.end(), [=](auto i) { return i.first == j; });
    return r != o.end() ? r->second : 0;
}

void graph::add_edge(int i, int j, float value) {
    _out_edges[i].push_back({j, value});
    _in_edges[j].push_back({i, value});
}

void graph::update_edge(int i, int j, float value) {
    auto &out = _out_edges[i];
    auto &in = _in_edges[j];
    std::find_if(out.begin(), out.end(), [=](auto x) { return x.first == j; })->second = value;
    std::find_if(in.begin(), in.end(), [=](auto x) { return x.first == i; })->second = value;
}

int graph::num_in(int i) const { return _in_edges[i].size(); }

int graph::num_out(int i) const { return _out_edges[i].size(); }

void graph::dump(std::ostream &os) const {
    for (int from = 0; from < _num_node; ++from) {
        for (auto to : _out_edges[from])
            os << format("{}->{} = {}\n", from, to.first, to.second);
        os << '\n';
    }
}

double graph::density() const {
    double total = _num_node * _num_node;
    return std::accumulate(_in_edges.begin(), _in_edges.end(), 0, [](auto s, auto& i){
        return s + i.size();
    }) / total;
}

// template <>
// struct fmt::formatter<graph> {
//     template <typename FormatContext>
//     auto format(const graph&g, FormatContext& ctx){
//         return fmt::format()
//     }
// };