#include <bits/stdc++.h>
using namespace std;

const int INF = INT_MAX;

struct WeightedGraph {
    int V;
    vector<vector<pair<int,int>>> adj;

    WeightedGraph(int v) : V(v), adj(v) {}

    void addEdge(int u, int v, int w) {
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }

    pair<vector<int>, vector<int>> dijkstra(int src) {
        vector<int> dist(V, INF);
        vector<int> prev(V, -1);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

        dist[src] = 0;
        pq.push(make_pair(0, src));

        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d > dist[u]) continue;

            for (int k = 0; k < (int)adj[u].size(); k++) {
                int v = adj[u][k].first;
                int w = adj[u][k].second;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    prev[v] = u;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
        return make_pair(dist, prev);
    }

    vector<int> getPath(vector<int>& prev, int src, int dst) {
        vector<int> path;
        for (int cur = dst; cur != -1; cur = prev[cur])
            path.push_back(cur);
        reverse(path.begin(), path.end());
        if (path[0] != src) return vector<int>(); 
        return path;
    }

    void printShortestPaths(int src) {
        pair<vector<int>, vector<int>> result = dijkstra(src);
        vector<int> dist = result.first;
        vector<int> prev = result.second;

        cout << "Dijkstra dari vertex " << src << ":\n";
        cout << "  Vertex | Jarak | Jalur\n";
        cout << "  -------|-------|------\n";

        for (int i = 0; i < V; i++) {
            cout << "    " << i << "    |  ";
            if (dist[i] == INF) {
                cout << " INF | TIDAK TERJANGKAU\n";
                continue;
            }
            cout << setw(3) << dist[i] << "  | ";

            vector<int> path = getPath(prev, src, i);
            for (int j = 0; j < (int)path.size(); j++) {
                cout << path[j];
                if (j + 1 < (int)path.size()) cout << " -> ";
            }
            cout << "\n";
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

    wg.printShortestPaths(0);

    cout << "\n-- Coba dari vertex lain --\n";
    wg.printShortestPaths(3);

    return 0;
}
