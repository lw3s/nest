#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <exception>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <vector>

class NonexistentNode : public std::range_error {
public:
    NonexistentNode(const auto val) : std::range_error((std::ostringstream() << "Node " << val << " does not exist.").str()) {}
};

class NonexistentEdge : public std::range_error {
public:
    NonexistentEdge(const auto begin, const auto end) : std::range_error((std::ostringstream() << "The edge from " << begin << " to " << end << " does not exist.").str()) {}
};

template <typename T>
class Graph {
protected:
    std::unordered_map<T, std::unordered_map<T, double>> _adjacency; // begin: {end: weight}

    public:
    Graph() {}
    Graph(std::initializer_list<std::tuple<T, T, double>> edges) {
        for (auto i : edges) {
            set_edge(std::get<0>(i), std::get<1>(i), std::get<2>(i));
        }
    }
    Graph(std::unordered_map<T, std::unordered_map<T, double>> initial) : _adjacency(initial) {}
    size_t size() {
        return _adjacency.size();
    }
    std::vector<T> nodes() { // not recommended to use
        std::vector<T> nodes;
        for (const auto key_value : _adjacency) {
            nodes.push_back(key_value.first);
        }
        return nodes;
    }
    std::vector<std::tuple<T, T, double>> edges() { // not recommended to use
        std::vector<std::tuple<T, T, double>> edges;
        for (const auto begin_ends : _adjacency) {
            for (const auto end_weight : begin_ends.second) {
                edges.push_back({begin_ends.first, end_weight.first, end_weight.second});
            }
        }
        return edges;
    }
    void add_node(T node) {
        _adjacency[node] = {};
    }
    void set_edge(T begin, T end, double weight) {
        if (!_adjacency.contains(begin)) add_node(begin);
        if (!_adjacency.contains(end)) add_node(end);
        _adjacency[begin][end] = weight;
    }
    bool has_node(T node) {
        return _adjacency.contains(node);
    }
    bool has_edge(T begin, T end) {
        if (_adjacency.contains(begin)) {
            return _adjacency[begin].contains(end);
        }
        return false;
    }
    void del_node(T node) {
        if (!_adjacency.contains(node)) return;
        _adjacency.erase(node);
        for (auto i : _adjacency) {
            _adjacency[i.first].erase(node);
        }
    }
    void del_edge(T begin, T end) {
        if (!_adjacency.contains(begin)) return;
        if (!_adjacency[begin].contains(end)) return;
        _adjacency[begin].erase(end);
    }
    double weight(T begin, T end) {
        if (!_adjacency.contains(begin)) throw NonexistentNode(begin);
        if (!_adjacency.contains(end)) throw NonexistentNode(end);
        if (!_adjacency[begin].contains(end)) throw NonexistentEdge(begin, end);
        return _adjacency[begin][end];
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, Graph<T> g) {
    for (auto i : g.edges()) {
        os << std::get<0>(i) << "---" << std::get<2>(i) << "-->" << std::get<1>(i) << "\n";
    }
    return os;
}

#endif // GRAPH_HPP
