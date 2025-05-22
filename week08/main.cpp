#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <functional>

std::vector<std::vector<int>> convertMatrixToList(const std::string &filename) {
    std::ifstream inp(filename);
    if (!inp.is_open())
        return {};
    int n; inp >> n;
    std::vector<std::vector<int>> adj_list(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            int has_edge; inp >> has_edge;
            if (has_edge)
                adj_list[i].push_back(j);
        }
    inp.close();
    return adj_list;
}

std::vector<std::vector<int>> convertListToMatrix(const std::string &filename) {
    std::ifstream inp(filename);
    if (!inp.is_open())
        return {};
    int n; inp >> n;
    std::vector<std::vector<int>> adj_matrix(n, std::vector<int>(n, 0));
    for (int from = 0; from < n; from++) {
        int k; inp >> k;
        for (int j = 0; j < k; j++) {
            int to; inp >> to;
            adj_matrix[from][to] = 1;
        }
    }
    inp.close();
    return adj_matrix;
}

/* Doesn't work at all, an undirected graph in implementation is the same as a directed graph
This is more like checking if the graph can be converted to undirected graph or not (`true` if not possible) */
bool isDirected(const std::vector<std::vector<int>> &adjMatrix) {
    int n = (int)adjMatrix.size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            if (adjMatrix[i][j] != adjMatrix[j][i])
                return true;
    return false;
}

int countVertices(const std::vector<std::vector<int>> &adjMatrix) {
    return (int)adjMatrix.size();
}

int countEdges(const std::vector<std::vector<int>> &adjMatrix) {
    int edge_count = 0;
    for (const std::vector<int> &v : adjMatrix)
        for (const int &u : v)
            edge_count += u;
    if (!isDirected(adjMatrix))
        edge_count /= 2;
    return edge_count;
}

std::vector<int> getIsolatedVertices(const std::vector<std::vector<int>> &adjMatrix) {
    std::vector<int> isolated_nodes;
    for (int v = 0; v < (int)adjMatrix.size(); v++) {
        int neighbors = 0;
        for (const int &u : adjMatrix[v])
            neighbors += u;
        if (neighbors == 0)
            isolated_nodes.push_back(v);
    }
    return isolated_nodes;
}

bool isCompleteGraph(const std::vector<std::vector<int>> &adjMatrix) {
    int n = (int)adjMatrix.size();
    for (const std::vector<int> &v : adjMatrix) {
        int neighbors = 0;
        for (int u : v)
            neighbors += u;
        if (neighbors != n - 1)
            return false;
    }
    return true;
}

bool isBipartite(const std::vector<std::vector<int>> &adjMatrix) {
    int n = (int)adjMatrix.size();
    std::vector<int> layer(n);
    std::queue<int> q;
    for (int i = 0; i < n; i++) {
        if (layer[i] == 0) {
            layer[i] = 1;
            q.push(i);
            while (!q.empty()) {
                int u = q.front(); 
                q.pop();
                for (int v = 0; v < n; v++){
                    if (adjMatrix[u][v]) {
                        if (layer[u] == layer[v])
                            return false;
                        if (layer[v] == 0) {
                            layer[v] = layer[u] + 1;
                            q.push(v);
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool isCompleteBipartite(const std::vector<std::vector<int>> &adjMatrix) {
    return isCompleteGraph(adjMatrix) && isBipartite(adjMatrix);
}

/// @brief 
/// @param adjMatrix an undirected graph
/// @return 
std::vector<std::vector<int>> getComplementGraph(const std::vector<std::vector<int>> &adjMatrix) {
    std::vector<std::vector<int>> complement = adjMatrix;
    int n = (int)adjMatrix.size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            complement[i][j] = complement[j][i] = !adjMatrix[i][j];
    return complement;
}

std::vector<int> findEulerCycle(const std::vector<std::vector<int>> &adjMatrix) {
    int n = (int)adjMatrix.size();
    std::vector<int> circuit, trail(1, 0);
    std::vector<std::vector<int>> adjMatrix_copy = adjMatrix;
    while (!trail.empty()) {
        int u = trail.back();
        bool moved = false;
        for (int v = 0; v < n; v++)
            if (adjMatrix_copy[u][v]) {
                adjMatrix_copy[u][v] = 0;
                trail.push_back(v);
                moved = true;
                break;
            }
        if (!moved)
            circuit.push_back(u), trail.pop_back();
    }
    std::reverse(circuit.begin(), circuit.end());
    return circuit;
}

/// @brief 
/// @param adjMatrix ann undirected graph
/// @return 
std::vector<std::vector<int>> dfsSpanningTree(const std::vector<std::vector<int>> &adjMatrix, int start) {
    std::vector<bool> passed(adjMatrix.size());
    std::vector<std::vector<int>> spanning_tree(adjMatrix.size());
    std::function<void(int)> dfs = [&](int u) {
        passed[u] = true;
        for (int v = 0; v < (int)adjMatrix.size(); v++)
            if (adjMatrix[u][v]) {
                spanning_tree[u].push_back(v);
                spanning_tree[v].push_back(u);
                dfs(v);
            }
    };
    dfs(0);
    return spanning_tree;
}

/// @brief 
/// @param adjMatrix an undirected graph
/// @return 
std::vector<std::vector<int>> bfsSpanningTree(const std::vector<std::vector<int>> &adjMatrix, int start) {
    std::vector<bool> passed(adjMatrix.size());
    std::vector<std::vector<int>> spanning_tree(adjMatrix.size());
    std::queue<int> q;
    q.push(0);
    passed[0] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < (int)adjMatrix.size(); v++)
            if (adjMatrix[u][v]) {
                spanning_tree[u].push_back(v);
                spanning_tree[v].push_back(u);
                passed[v] = true;
                q.push(v);
            }
    }
    return spanning_tree;
}

bool isConnected(int u, int v, const std::vector<std::vector<int>> &adjMatrix) {
    std::queue<int> q;
    q.push(u);
    std::vector<bool> passed(adjMatrix.size());
    passed[u] = true;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int y = 0; y < (int)adjMatrix.size(); y++)
            if (adjMatrix[x][y] && !passed[y]) {
                if (y == v)
                    return true;
                passed[y] = true;
                q.push(y);
            }
    }

    while (!q.empty())
        q.pop();
    q.push(v);
    passed.assign(adjMatrix.size(), 0);
    passed[v] = true;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int y = 0; y < (int)adjMatrix.size(); y++)
            if (adjMatrix[x][y] && !passed[y]) {
                if (y == u)
                    return true;
                passed[y] = true;
                q.push(y);
            }
    }
    return false;
}

/// @brief 
/// @param adjMatrix a positively-weighted directed graph
/// @return 
std::vector<int> dijkstra(int start, int end, const std::vector<std::vector<int>> &adjMatrix){
    const int INF = (1 << (sizeof(int) * 8 - 2)) - 1;

    std::vector<int> distance(adjMatrix.size(), INF);
    distance[start] = 0;
    std::vector<int> pred(adjMatrix.size(), -1);

    std::priority_queue<std::pair<int, int>> pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [old_dist, u] = pq.top();
        pq.pop();
        for (int v = 0; v < (int)adjMatrix.size(); v++) {
            int new_dist = old_dist + adjMatrix[u][v];
            if (new_dist < distance[v]) {
                pred[v] = u;
                distance[v] = new_dist;
                pq.emplace(new_dist, v);
            }
        }
    }

    // Not connected
    if (distance[end] == INF)
        return {};

    std::vector<int> shortest_path;
    for (int u = end; pred[u] != -1; u = pred[u])
        shortest_path.push_back(u);
    std::reverse(shortest_path.begin(), shortest_path.end());
    return shortest_path;
}

/// @brief 
/// @param adjMatrix a positively-weighted directed graph
/// @return 
std::vector<int> bellmanFord(int start, int end, const std::vector<std::vector<int>> &adjMatrix) {
    const int INF = (1 << (sizeof(int) * 8 - 2)) - 1;

    std::vector<int> distance(adjMatrix.size(), INF);
    distance[start] = 0;
    std::vector<int> pred(adjMatrix.size(), -1);

    int n = (int)adjMatrix.size();
    for (int i = 0; i < n - 1; i++)
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                if (distance[u] + adjMatrix[u][v] < distance[v]) {
                    distance[v] = distance[u] + adjMatrix[u][v];
                    pred[v] = u;
                }
    
    // Not connected
    if (distance[end] == INF)
        return {};

    std::vector<int> shortest_path;
    for (int u = end; pred[u] != -1; u = pred[u])
        shortest_path.push_back(u);
    std::reverse(shortest_path.begin(), shortest_path.end());
    return shortest_path;
}