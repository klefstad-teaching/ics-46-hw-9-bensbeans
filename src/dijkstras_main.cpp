#include "dijkstras.h"

int main() {
    const string filename = "src/small.txt";
    Graph G;
    file_to_graph(filename, G);
    int source = 0, destination = G.numVertices - 1; 

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);
    vector<int> path = extract_shortest_path(distances, previous, destination);

    print_path(path, distances[destination]);
    return 0;
}
