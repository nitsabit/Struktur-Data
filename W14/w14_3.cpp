#include <bits/stdc++.h>
using namespace std;

struct WeightedGraph {
    int V;
    vector<vector<pair<int,int>>> adj;

    WeightedGraph(int v) : V(v), adj(v) {}

    void addEdge(int u, int v, int w) {
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w)); 
    }

    void printAdjList() {
        cout << "Weighted Adjacency List (" << V << " vertex):\n";
        for (int i = 0; i < V; i++) {
            cout << "  Vertex " << i << " -> [";
            for (int j = 0; j < (int)adj[i].size(); j++) {
                int neighbor = adj[i][j].first;
                int weight   = adj[i][j].second;
                cout << neighbor << "(w=" << weight << ")";
                if (j + 1 < (int)adj[i].size()) cout << ", ";
            }
            cout << "]\n";
        }
    }

    void printEdges() {
        cout << "\nDaftar Edge (u -- v, weight):\n";
        set<pair<int,int>> printed;
        for (int u = 0; u < V; u++) {
            for (int k = 0; k < (int)adj[u].size(); k++) {
                int v = adj[u][k].first;
                int w = adj[u][k].second;
                pair<int,int> e = make_pair(min(u,v), max(u,v));
                if (!printed.count(e)) {
                    printed.insert(e);
                    cout << "  " << u << " -- " << v << ", weight = " << w << "\n";
                }
            }
        }
    }
};

int main() {
    WeightedGraph wg(8);

    wg.addEdge(0, 1, 4);
    wg.addEdge(1, 2, 8);
    wg.addEdge(0, 3, 11);
    wg.addEdge(1, 4, 7);
    wg.addEdge(2, 5, 2);
    wg.addEdge(3, 4, 9);
    wg.addEdge(4, 5, 10);
    wg.addEdge(3, 6, 7);
    wg.addEdge(5, 7, 6);
    wg.addEdge(6, 7, 1);

    wg.printAdjList();
    wg.printEdges();

    return 0;
}
