#include "dijkstras.h"

//Dijkstras helpers
void _set_dijkstra(int source, int numVertices, vector<int>& distances, 
    vector<int>& previous, vector<bool>& visited, 
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>& pq) {
    distances.assign(numVertices, INF);
    previous.assign(numVertices, -1);
    visited.assign(numVertices, false);
    distances[source] = 0;
    pq.push({0, source});
}

void _relax(int u, const Edge& edge, vector<int>& distances, 
    vector<int>& previous, priority_queue<pair<int, int>, 
    vector<pair<int, int>>, greater<pair<int, int>>>& pq) {
    int v = edge.dst, weight = edge.weight;
    if (distances[u] + weight < distances[v]) {
        distances[v] = distances[u] + weight;
        previous[v] = u;
        pq.push({distances[v], v});
    }
}

//Dijkstra’s Algorithm
vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numVertices = G.numVertices;
    vector<int> distances(numVertices);
    vector<bool> visited(numVertices);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    _set_dijkstra(source, numVertices, distances, previous, visited, pq);

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (visited[u]) continue;
        visited[u] = true;

        for (const Edge& edge : G[u]) {
            _relax(u, edge, distances, previous, pq);
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    vector<int> path;
    if (destination == -1 || (previous[destination] == -1 && destination != 0)) {
        return path;
    }
    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& path, int total) {
    for (int node : path) {
        cout << node << " ";
    }
    cout << "\nTotal cost is " << total << endl;
}
