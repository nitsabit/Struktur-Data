#include <bits/stdc++.h>
using namespace std;

struct Graph {
    int V;
    vector<vector<int>> adj;

    Graph(int v) : V(v), adj(v) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void printAdjList() {
        cout << "Adjacency List (" << V << " vertex):\n";
        for (int i = 0; i < V; i++) {
            cout << "  Vertex " << i << " -> [";
            for (int j = 0; j < (int)adj[i].size(); j++) {
                cout << adj[i][j];
                if (j + 1 < (int)adj[i].size()) cout << ", ";
            }
            cout << "]\n";
        }
    }
};

int main() {
    Graph g(8);

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 6);
    g.addEdge(5, 7);
    g.addEdge(6, 7);

    g.printAdjList();

    return 0;
}
