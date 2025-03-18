#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <exception>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <vector>
#include <deque>
#include <queue>
#include <limits>


class nonexistent_node : public std::runtime_error {
public:
    nonexistent_node(const auto val) : std::runtime_error((std::ostringstream() << "Node " << val << " does not exist").str()) {}
};

class nonexistent_edge : public std::runtime_error {
public:
    nonexistent_edge(const auto begin, const auto end) : std::runtime_error((std::ostringstream() << "The edge from " << begin << " to " << end << " does not exist").str()) {}
};

class disconnected_graph : public std::runtime_error {
public:
    disconnected_graph() : std::runtime_error("This graph is not fully connected") {}
};

class cycle : public std::runtime_error {
    cycle() : std::runtime_error("This graph contains a cycle") {}
};

class negative_cycle : public std::runtime_error {
public:
    negative_cycle() : std::runtime_error("This graph contains a negative cycle") {}
};

class directed_graph : public std::runtime_error {
public:
    directed_graph() : std::runtime_error("This graph is not undirected") {}
};

template <typename T>
class Graph {
protected:
    std::unordered_map<T, std::unordered_map<T, double>> _adjacency; // begin: {end: weight}

    // all algorithms need to be friends
    friend std::unordered_map<T, std::pair<double, std::vector<T>>> sssp(Graph<T>& g, T start);
    friend std::unordered_map<T, std::pair<double, std::vector<T>>> dijkstra(Graph<T>& g, T start);
    friend std::unordered_map<T, std::pair<double, std::vector<T>>> bellman_ford(Graph<T>& g, T start);
    friend std::vector<T> shortest_path(Graph<T>& g, T start, T end);
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
        if (!_adjacency.contains(begin)) throw nonexistent_node(begin);
        if (!_adjacency.contains(end)) throw nonexistent_node(end);
        if (!_adjacency[begin].contains(end)) throw nonexistent_edge(begin, end);
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
                if (!(_adjacency[j.first].contains(i.first) && _adjacency[j.first][i.first] == j.second)) return false;
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
std::unordered_map<T, std::pair<double, std::vector<T>>> sssp(Graph<T>& g, T start) {
    if (g.is_positive()) return dijkstra(g, start);
    else return bellman_ford(g, start);
}

template <typename T>
std::unordered_map<T, std::pair<double, std::vector<T>>> dijkstra(Graph<T>& g, T start) {
    std::priority_queue<std::pair<double, T>, std::vector<std::pair<double, T>>, std::greater<std::pair<double, T>>> heap;
    std::unordered_map<T, double> distances;
    std::unordered_map<T, T> predecessors;
    for (T node : g.nodes()) {
        distances[node] = std::numeric_limits<double>::infinity();
    }
    distances[start] = 0;
    heap.push(std::make_pair(0, start));
    
    while (!heap.empty()) {
        T top = heap.top().second;
        heap.pop();
        for (auto node : g._adjacency[top]) {
            double new_dist = distances[top] + node.second;
            if (new_dist < distances[node.first]) {
                distances[node.first] = new_dist;
                heap.push(std::make_pair(new_dist, node.first));
                predecessors[node.first] = top;
            }
        }
    }
    preds_to_result(predecessors, distances, g.nodes());
}

template <typename T>
std::unordered_map<T, std::pair<double, std::vector<T>>> bellman_ford(Graph<T>& g, T start) {
    std::unordered_map<T, double> distances;
    std::unordered_map<T, T> predecessors;
    for (T node : g.nodes()) {
        distances[node] = std::numeric_limits<double>::infinity();
    }
    distances[start] = 0;

    for (int i = 0; i < g.size(); ++i) {
        for (auto edge : g.edges()) {
            T end = std::get<1>(edge);
            double new_weight = distances[std::get<0>(edge)] + std::get<2>(edge);
            if (new_weight < distances[end]) {
                distances[end] = new_weight;
                predecessors[end] = std::get<0>(edge);
                if (i == g.size() - 1) throw negative_cycle();
            }
        }
    }
    return preds_to_result(predecessors, distances, g.nodes());
}

template <typename T>
std::unordered_map<T, std::pair<double, std::vector<T>>> preds_to_result(auto predecessors, auto distances, std::vector<T> nodes) {
    std::unordered_map<T, std::pair<double, std::vector<T>>> result;
    for (const auto& node : nodes) {
        std::vector<T> path;
        if (distances[node] == std::numeric_limits<double>::infinity()) {
            result[node] = {distances[node], path};  
            continue;
        }
        for (T at = node; at != start; at = predecessors[at]) {
            path.push_back(at);
        }
        path.push_back(start);
        std::reverse(path.begin(), path.end());
        result[node] = {distances[node], path};
    }
    return result;
}

template <typename T>
std::pair<double, std::vector<T>> shortest_path(Graph<T>& g, T start, T end) {
    return sssp(g, start)[end];
}

template <typename T>
std::vector<T> top_sort(Graph<T>& g) {
    std::unordered_map<T, int> in_degree;
    for (auto edge : g.edges()) {
        ++in_degree[std::get<1>(edge)];
    }
    std::deque<T> zero_in;
    for (auto node : in_degree) {
        if (node.second == 0) zero_in.push_back(node.first);
    }

    T curr;
    std::vector<T> ordering;
    std::unordered_set<T> visited;
    while (!zero_in.size()) {
        curr = zero_in.front();
        zero_in.pop_front();
        ordering.push_back(curr);
        for (auto edge : g._adjacency[curr]) {
            --in_degree[edge.first];
            if (in_degree[edge.first] == 0 && !visited.contains(edge.first)) {
                zero_in.push_back(edge.first);
                visited.insert(edge.first);
            }
        }
    }
    if (ordering.size() != g.size()) throw cycle();
    return ordering;
}

template <typename T>
Graph<T> mst(Graph<T>& g) {
    if (!g.is_undirected()) throw directed_graph();
    if (!g.is_connected()) throw disconnected_graph();

    Graph<T> mst;
    std::priority_queue<std::tuple<double, T, T>, std::vector<std::tuple<double, T, T>>, std::greater<std::tuple<double, T, T>>> heap;
    std::unordered_set<T> visited;
    add_edges(g._adjacency.begin()->first, g._adjacency, heap, visited);

    while (!heap.empty()) {
        std::tuple<double, T, T> curr_edge = heap.top();
        T from = std::get<1>(curr_edge); T to = std::get<2>(curr_edge); double weight = std::get<0>(curr_edge);
        heap.pop();
        if (visited.contains(to)) continue;
        mst.set_edge(from, to, weight);
        mst.set_edge(to, from, weight);
        add_edges(to, g._adjacency, heap, visited);
    }
    return mst;
}

template <typename T>
void add_edges(T node, std::unordered_map<T, std::unordered_map<T, double>>& adj, std::priority_queue<std::tuple<double, T, T>>& heap, std::unordered_set<T>& visited) {
    for (auto edge : adj[node]) {
        if (!visited.contains(edge.first)) {
            heap.push({ edge.second, node, edge.first });
        }
    }
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
