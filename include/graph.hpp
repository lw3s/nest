#ifndef GRAPH_HPP
#define GRAPH_HPP


#include <exception>
#include <unordered_map>
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
    std::unordered_map<T, std::unordered_map<T, double>> _adjacency; // begin, {{end, weight}}


public:
    size_t size() {
        return _adjacency.size();
    }

    std::vector<T> nodes() { // not recommended to use
        std::vector<T> ret;
        for (const auto key_value : _adjacency) {
            ret.push_back(key_value.first);
        }
        return ret;
    }

    std::vector<std::tuple<T, T, double>> edges() { // not recommended to use
        std::vector<std::tuple<T, T, double>> ret;
        for (const auto begin_ends : _adjacency) {
            for (const auto end_weight : begin_ends.second) {
                ret.push_back({begin_ends.first, end_weight.first, end_weight.second});
            }
        }
        return ret;
    }

    void add_node(T node) {
        _adjacency[node] = {};
    }

    void set_edge(T begin, T end, double weight) {
        if (!_adjacency.contains(begin)) throw NonexistentNode(begin);
        if (!_adjacency.contains(end)) throw NonexistentNode(end);
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
        if (!_adjacency.contains(node)) throw NonexistentNode(node);
        _adjacency.erase(node);
        for (auto i : _adjacency) {
            _adjacency[i.first].erase(node);
        }
    }

    void del_edge(T begin, T end) {
        if (!_adjacency.contains(begin)) throw NonexistentNode(begin);
        if (!_adjacency.contains(end)) throw NonexistentNode(end);
        if (!_adjacency[begin].contains(end)) throw NonexistentEdge(begin, end);
        _adjacency[begin].erase(end);
    }

    double weight(T begin, T end) {
        if (!_adjacency.contains(begin)) throw NonexistentNode(begin);
        if (!_adjacency.contains(end)) throw NonexistentNode(end);
        if (!_adjacency[begin].contains(end)) throw NonexistentEdge(begin, end);
        return _adjacency[begin][end];
    }
};


#endif // GRAPH_HPP