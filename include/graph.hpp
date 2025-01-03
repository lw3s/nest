#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <exception>
#include <unordered_map>
#include <cstdlib>
#include <iostream>
#include <string>

class NonexistentNode : public std::exception {
    std::string _what;
public:
    NonexistentNode(const auto val) : _what((std::ostringstream() << "Node " << val << " does not exist.").str()) {}
    std::string what() { return _what; }
};
class NonexistentEdge : public std::exception {
    std::string _what;
public:
    NonexistentEdge(const auto begin, const auto end) : _what((std::ostringstream() << "The edge from " << begin << " to " << end << " does not exist.").str()) {}
    std::string what() { return _what; }
};
template <typename T>
class Graph {
protected:
    std::unordered_map<T, std::unordered_map<T, double>> _adjacency; // {begin, {end, weight}}
public:

    size_t size() { return _adjacency.size(); }
    void clear_node(T node) { _adjacency[node] = {}; }
    void update_edge(T begin, T end, double weight) {
        if (!_adjacency.contains(begin)) throw NonexistentNode(begin);
        if (!_adjacency.contains(end)) throw NonexistentNode(end);
        _adjacency[begin][end] = weight;
    }
    void del_node(T node) {
        if (!_adjacency.contains(node)) throw NonexistentNode(node);
        _adjacency.erase(node);
        for (auto i: _adjacency) {
            _adjacency[i].erase(node);
        }
    }
    void del_edge(T begin, T end) {
        if (!_adjacency.contains(begin)) throw NonexistentNode(begin);
        if (!_adjacency.contains(end)) throw NonexistentNode(end);
        if (!_adjacency[begin].contains(end)) throw NonexistentEdge(begin, end);
        _adjacency[begin].erase(end);
    }
    int weight(T begin, T end) {
        if (!_adjacency.contains(begin)) throw NonexistentNode(begin);
        if (!_adjacency.contains(end)) throw NonexistentNode(end);
        if (!_adjacency[begin].contains(end)) throw NonexistentEdge(begin, end);
        return _adjacency[begin][end];
    }
};

#endif // GRAPH_HPP