#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <exception>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <vector>
#include <deque>


class NonexistentNode : public std::runtime_error {
public:
    NonexistentNode(const auto val) : std::runtime_error((std::ostringstream() << "Node " << val << " does not exist").str()) {}
};

class NonexistentEdge : public std::runtime_error {
public:
    NonexistentEdge(const auto begin, const auto end) : std::runtime_error((std::ostringstream() << "The edge from " << begin << " to " << end << " does not exist").str()) {}
};

class DisconnectedGraph : public std::runtime_error {
public:
    DisconnectedGraph() : std::runtime_error("This graph is not fully connected") {}
};

class Cycle : public std::runtime_error {
    Cycle() : std::runtime_error("This graph contains a cycle") {}
};

class NegativeCycle : public std::runtime_error {
public:
    NegativeCycle() : std::runtime_error("This graph contains a negative cycle") {}
};

template <typename T>
class Graph {
protected:
    std::unordered_map<T, std::unordered_map<T, double>> _adjacency; // begin: {end: weight}

    // all algorithms need to be friends
    friend std::vector<std::vector<T>> sssp(Graph<T>& g, T start, bool is_pos = false);
    friend std::vector<T> shortest_path(Graph<T>& g, T start, T end, bool is_pos = false);
    friend std::vector<std::vector<T>> all_shortest_paths(Graph<T>& g);
    friend std::vector<T> top_sort(Graph<T>& g);
    friend Graph<T> mst(Graph<T>& g);
    friend std::vector<std::vector<T>> scc(Graph<T>& g);

    public:
    Graph() {}
    Graph(std::initializer_list<std::tuple<T, T, double>>& edges) {
        for (auto i : edges) {
            set_edge(std::get<0>(i), std::get<1>(i), std::get<2>(i));
        }
    }
    Graph(std::unordered_map<T, std::unordered_map<T, double>>& initial) : _adjacency(initial) {}
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
    bool is_dag() {
        try {
            top_sort(*this);
            return true;
        }
        catch (...) {
            return false;
        }
    }
    bool is_undirected() {
        for (auto i : _adjacency) {
            for (auto j : i.second) {
                if (!_adjacency[j.first].contains(i.first)) return false;
            }
        }
        return true;
    }
    bool is_positive() {
        for (auto edge : edges()) {
            if (std::get<2>(edge) < 0) return false;
        }
        return true;
    }
    bool is_connected() {
        std::unordered_map<T, bool> visited;
        for (T node : nodes()) {
            visited[node] = false;
            rev_adjacency[node] = {};
        }
        std::unordered_map<T, std::unordered_map<T, double>> undirected_adjacency;
        for (auto i : _adjacency) {
            for (auto j : i.second) {
                undirected_adjacency[i.first][j.first] = j.second
                undirected_adjacency[j.first][i.first] = j.second;
            }
        }
        
        dfs(undirected_adjacency, visited, visited.begin()->first);
        for (auto node : visited) {
            if (!visited.second) return false;
        }
        return true;
    }
protected:
    void dfs(std::unordered_map<T, std::unordered_map<T, double>>& adj, std::unordered_map<T, bool>& visited, T curr) {
        for (auto node : adj[curr]) {
            if (!visited[node.first]) {
                visited[node.first] = true;
                dfs(adj, visited, node.first);
            }
        }
    }
};

template <typename T>
std::vector<std::vector<T>> sssp(Graph<T>& g, T start, bool is_pos = false) {

}

template <typename T>
std::vector<T> shortest_path(Graph<T>& g, T start, T end, bool is_pos = false) {

}

template <typename T>
std::vector<std::vector<T>> all_shortest_paths(Graph<T>& g) {

}

template <typename T>
std::vector<T> top_sort(Graph<T>& g) {

}

template <typename T>
Graph<T> mst(Graph<T>& g) {

}

template <typename T>
std::vector<std::vector<T>> scc(Graph<T>& g) {

}

template <typename T>
std::ostream& operator<<(std::ostream& os, Graph<T> g) {
    for (auto i : g.edges()) {
        os << std::get<0>(i) << "---" << std::get<2>(i) << "-->" << std::get<1>(i) << "\n";
    }
    return os;
}

#endif // GRAPH_HPP
