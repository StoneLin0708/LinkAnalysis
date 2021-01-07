#pragma once
#include <algorithm>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

class graph {
  public:
    // sparse matrix should be much faster at larger scale

    static graph from_file(std::string csv);

    graph(int n);
    graph(const graph &o);

    std::unordered_map<std::string, int> name2idx;
    std::vector<std::string> idx2name;

    float operator()(int i, int j) const;

    int num_in(int i) const;
    int num_out(int i) const;

    void add_edge(int i,int j, float value);
    void update_edge(int i, int j, float value);

    const std::vector<std::pair<int, float>>& in_neighbors(int i) const {return _in_edges[i];}
    const std::vector<std::pair<int, float>>& out_neighbors(int i) const {return _out_edges[i];}

    double density() const;

    void dump(std::ostream &os) const;
    int num_node() const { return _num_node; }

  private:
    std::vector<std::vector<std::pair<int, float>>> _in_edges;
    std::vector<std::vector<std::pair<int, float>>> _out_edges;

    int _num_node;
};