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

    void DFS(int start) {
        vector<bool> visited(V, false);
        stack<int> st;

        st.push(start);
        cout << "DFS dari vertex " << start << ": ";

        while (!st.empty()) {
            int node = st.top();
            st.pop();

            if (visited[node]) continue;
            visited[node] = true;
            cout << node << " ";

            for (int i = (int)adj[node].size() - 1; i >= 0; i--) {
                if (!visited[adj[node][i]])
                    st.push(adj[node][i]);
            }
        }
        cout << "\n";
    }

    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);
        cout << "BFS dari vertex " << start << ": ";

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << "\n";
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

    g.DFS(0);
    g.BFS(0);

    cout << "\n-- Mulai dari vertex berbeda --\n";
    g.DFS(4);
    g.BFS(4);

    return 0;
}
