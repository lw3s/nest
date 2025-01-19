#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <exception>
#include <unordered_map>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <limits.h>
#include <stack>
#include <algorithm>
#include <climits>

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
    std::unordered_map<T, std::unordered_map<T, double>*>* _adjacency; // begin, {{end, weight}}

public:
    Graph() {
        _adjacency = new std::unordered_map<T, std::unordered_map<T, double>*>;
    }

    ~Graph() {
        for (auto& pair : *_adjacency) {
            delete pair.second;
        }
        delete _adjacency;
    }

    size_t size() { return _adjacency->size(); }

    std::vector<T> nodes() { // not recommended to use
        std::vector<T> ret;
        for (const auto& key_value : *_adjacency) {
            ret.push_back(key_value.first);
        }
        return ret;
    }

    std::vector<std::tuple<T, T, double>> edges() { // not recommended to use
        std::vector<std::tuple<T, T, double>> ret;
        for (const auto& begin_ends : *_adjacency) {
            for (const auto& end_weight : *(begin_ends.second)) {
                ret.push_back({begin_ends.first, end_weight.first, end_weight.second});
            }
        }
        return ret;
    }

    void clear_node(T node) {
        if (_adjacency->contains(node)) delete (*_adjacency)[node];
        (*_adjacency)[node] = new std::unordered_map<T, double>;
    }

    void update_edge(T begin, T end, double weight) {
        if (!_adjacency->contains(begin)) throw NonexistentNode(begin);
        if (!_adjacency->contains(end)) throw NonexistentNode(end);
        (*(*_adjacency)[begin])[end] = weight;
    }

    void del_node(T node) {
        if (!_adjacency->contains(node)) throw NonexistentNode(node);
        _adjacency->erase(node);
        for (auto& i : *_adjacency) {
            (*_adjacency)[i.first].erase(node);
        }
    }

    void del_edge(T begin, T end) {
        if (!_adjacency->contains(begin)) throw NonexistentNode(begin);
        if (!_adjacency->contains(end)) throw NonexistentNode(end);
        if (!(*_adjacency)[begin]->contains(end)) throw NonexistentEdge(begin, end);
        (*_adjacency)[begin]->erase(end);
    }

    double weight(T begin, T end) {
        if (!_adjacency->contains(begin)) throw NonexistentNode(begin);
        if (!_adjacency->contains(end)) throw NonexistentNode(end);
        if (!(*_adjacency)[begin]->contains(end)) throw NonexistentEdge(begin, end);
        return (*(*_adjacency)[begin])[end];
    }
};

// Dijkstra

class Graph {
public:
    int V;  // Number of vertices
    std::vector<std::vector<std::pair<int, int>>> adj;  // Adjacency list where each pair is (neighbor, weight)

    // Constructor to initialize graph with given number of vertices
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    // Add an edge to the graph (u -> v with weight w)
    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});  // Since it's an undirected graph
    }

    // Dijkstra's algorithm to find the shortest path from a source vertex
    std::vector<int> dijkstra(int src) {
        // Create a priority queue to store (distance, vertex)
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

        // Initialize distances with infinity
        std::vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        // Push the source vertex into the priority queue
        pq.push({0, src});

        // Process all vertices
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            // Explore the neighbors of u
            for (auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                // If a shorter path to v is found, update distance and push it to the queue
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        return dist;
    }
};

// Prim

class Graph {
public:
    int V;  // Number of vertices
    std::vector<std::vector<std::pair<int, int>>> adj;  // Adjacency list where each pair is (neighbor, weight)

    // Constructor to initialize the graph with given number of vertices
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    // Add an edge to the graph (u <-> v with weight w)
    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});  // Since it's an undirected graph
    }

    // Prim's algorithm to find the Minimum Spanning Tree (MST)
    std::vector<std::pair<int, int>> primMST(int src) {
        // Min-heap priority queue to store (weight, vertex)
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

        // To keep track of vertices included in MST
        std::vector<bool> inMST(V, false);

        // Vector to store the MST edges
        std::vector<std::pair<int, int>> mstEdges;

        // Start with the source vertex
        pq.push({0, src});  // (weight, vertex)
        
        while (!pq.empty()) {
            int u = pq.top().second;
            int weight = pq.top().first;
            pq.pop();

            // If u is already in MST, skip it
            if (inMST[u]) continue;

            // Include this vertex in MST
            inMST[u] = true;

            // Add the edge to the MST (except for the first one)
            if (weight != 0) {  // The first vertex has no incoming edge
                mstEdges.push_back({u, weight});
            }

            // Update the priority queue with the neighbors of u
            for (auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int edgeWeight = neighbor.second;

                // If v is not in MST and the edge weight is smaller, push to pq
                if (!inMST[v]) {
                    pq.push({edgeWeight, v});
                }
            }
        }

        return mstEdges;
    }
};

// Tarjan

class TarjanSCC {
public:
    TarjanSCC(int n) : n(n), time(0) {
        adj.resize(n);
        disc.resize(n, -1);
        low.resize(n, -1);
        inStack.resize(n, false);
    }

    // Add an edge to the graph
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    // Main function to find and print all SCCs
    void findSCCs() {
        for (int i = 0; i < n; ++i) {
            if (disc[i] == -1) {
                tarjanDFS(i);
            }
        }
    }

private:
    int n; // Number of nodes
    int time; // Timer to keep track of discovery time
    std::vector<std::vector<int>> adj; // Adjacency list representation of the graph
    std::vector<int> disc, low; // Discovery time and low-link values
    std::vector<bool> inStack; // To check if a node is currently in the stack
    std::stack<int> stk; // Stack to hold the nodes

    // Helper function to perform DFS and find SCCs
    void tarjanDFS(int u) {
        // Set discovery time and low-link value
        disc[u] = low[u] = time++;
        stk.push(u);
        inStack[u] = true;

        // Explore the neighbors of u
        for (int v : adj[u]) {
            if (disc[v] == -1) {
                tarjanDFS(v);
                low[u] = std::min(low[u], low[v]);
            } else if (inStack[v]) {
                low[u] = std::min(low[u], disc[v]);
            }
        }

        // If u is a root node, pop all nodes in the SCC
        if (disc[u] == low[u]) {
            std::cout << "SCC: ";
            while (true) {
                int w = stk.top();
                stk.pop();
                inStack[w] = false;
                std::cout << w << " ";
                if (w == u) break;
            }
            std::cout << std::endl;
        }
    }
};

// Kahn

class KahnTopologicalSort {
public:
    KahnTopologicalSort(int n) : n(n) {
        adj.resize(n);
        inDegree.resize(n, 0);
    }

    // Add an edge to the graph
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        inDegree[v]++; // Increment in-degree of vertex v
    }

    // Perform topological sort using Kahn's Algorithm
    bool topologicalSort() {
        std::queue<int> q;
        std::vector<int> topOrder;

        // Enqueue nodes with in-degree 0 (no dependencies)
        for (int i = 0; i < n; ++i) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        // Process the nodes in the queue
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topOrder.push_back(u);

            // For each neighbor of u, reduce its in-degree
            for (int v : adj[u]) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        // Check if there was a cycle (i.e., not all nodes were processed)
        if (topOrder.size() != n) {
            std::cout << "The graph contains a cycle. Topological sort is not possible.\n";
            return false;
        }

        // Print the topological order
        std::cout << "Topological Sort: ";
        for (int node : topOrder) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
        return true;
    }

private:
    int n; // Number of nodes
    std::vector<std::vector<int>> adj; // Adjacency list representation of the graph
    std::vector<int> inDegree; // In-degree array
};

// Bellman-Ford

struct Edge {
    int u, v, weight;
};

// Bellman-Ford Algorithm to find the shortest paths from source
class BellmanFord {
public:
    BellmanFord(int n) : n(n) {
        dist.resize(n, INF); // Distance to all nodes is initially infinite
        adj.resize(n); // Adjacency list to store the edges
    }

    // Add an edge to the graph
    void addEdge(int u, int v, int weight) {
        adj[u].push_back({u, v, weight});
    }

    // Perform Bellman-Ford algorithm and print the shortest path from the source
    bool run(int source) {
        dist[source] = 0; // Distance to the source node is 0

        // Relax all edges (n - 1) times
        for (int i = 1; i < n; ++i) {
            for (auto& edge : adj[i]) {
                if (dist[edge.u] != INF && dist[edge.u] + edge.weight < dist[edge.v]) {
                    dist[edge.v] = dist[edge.u] + edge.weight;
                }
            }
        }

        // Check for negative weight cycles
        for (auto& edge : adj) {
            if (dist[edge.u] != INF && dist[edge.u] + edge.weight < dist[edge.v]) {
                std::cout << "Graph contains a negative weight cycle.\n";
                return false;
            }
        }

        // Print the shortest distances
        std::cout << "Shortest distances from source node " << source << ":\n";
        for (int i = 0; i < n; ++i) {
            if (dist[i] == INF)
                std::cout << "Node " << i << ": INF\n";
            else
                std::cout << "Node " << i << ": " << dist[i] << "\n";
        }
        return true;
    }

private:
    int n; // Number of nodes
    std::vector<int> dist; // Distance vector
    std::vector<std::vector<Edge>> adj; // Adjacency list for the graph
    static const int INF = std::numeric_limits<int>::max(); // Represent infinity
};

// Ford-Fulkerson

class FordFulkerson {
public:
    FordFulkerson(int n) : n(n), graph(n, std::vector<int>(n, 0)), residual(n, std::vector<int>(n, 0)) {}

    // Add an edge with a given capacity from u to v
    void addEdge(int u, int v, int capacity) {
        graph[u][v] = capacity; // original graph with capacities
        residual[u][v] = capacity; // residual graph initially equals to the original graph
    }

    // Perform DFS to find an augmenting path from source to sink
    bool dfs(int u, int t, std::vector<int>& parent) {
        std::vector<bool> visited(n, false);
        visited[u] = true;
        parent[u] = -1;

        // Create a stack for DFS
        std::queue<int> q;
        q.push(u);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            // Explore all neighbors
            for (int v = 0; v < n; ++v) {
                if (!visited[v] && residual[node][v] > 0) {
                    q.push(v);
                    visited[v] = true;
                    parent[v] = node;
                    if (v == t) return true; // If we reached the sink, stop the search
                }
            }
        }
        return false; // No augmenting path found
    }

    // Ford-Fulkerson algorithm to compute maximum flow
    int computeMaxFlow(int source, int sink) {
        std::vector<int> parent(n);
        int maxFlow = 0;

        // Augment the flow while there is an augmenting path
        while (dfs(source, sink, parent)) {
            // Find the maximum flow through the path found by DFS
            int pathFlow = INT_MAX;
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                pathFlow = std::min(pathFlow, residual[u][v]);
            }

            // Update the residual graph
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                residual[u][v] -= pathFlow;
                residual[v][u] += pathFlow;
            }

            maxFlow += pathFlow; // Add the flow of this augmenting path to the total flow
        }

        return maxFlow;
    }

private:
    int n; // Number of nodes
    std::vector<std::vector<int>> graph; // Original graph with capacities
    std::vector<std::vector<int>> residual; // Residual graph with remaining capacities
};

#endif // GRAPH_HPP
