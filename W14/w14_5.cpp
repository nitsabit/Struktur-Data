#include <bits/stdc++.h>
using namespace std;

struct SocialNetwork {
    int V;
    vector<string> names;
    // pair<teman_id, closeness_score>
    vector<vector<pair<int,int>>> adj;

    SocialNetwork(vector<string> userNames)
        : V(userNames.size()), names(userNames), adj(userNames.size()) {}

    void addFriendship(int u, int v, int closeness = 1) {
        adj[u].push_back(make_pair(v, closeness));
        adj[v].push_back(make_pair(u, closeness));
    }
    
    void listFriends(int user) {
        cout << "Teman " << names[user] << ": ";
        if (adj[user].empty()) {
            cout << "(tidak ada)\n";
            return;
        }
        for (size_t i = 0; i < adj[user].size(); i++) {
            int f = adj[user][i].first;
            int w = adj[user][i].second;
            cout << names[f] << "(score=" << w << ") ";
        }
        cout << "\n";
    }

    void friendSuggestions(int user) {
        set<int> direct;
        for (size_t i = 0; i < adj[user].size(); i++) direct.insert(adj[user][i].first);
        direct.insert(user);

        set<int> suggestions;
        for (set<int>::iterator it = direct.begin(); it != direct.end(); ++it) {
            int f = *it;
            if (f == user) continue;
            for (size_t i = 0; i < adj[f].size(); i++) {
                int ff = adj[f][i].first;
                if (!direct.count(ff))
                    suggestions.insert(ff);
            }
        }

        cout << "Saran teman untuk " << names[user] << ": ";
        if (suggestions.empty()) { cout << "(tidak ada)\n"; return; }
        for (set<int>::iterator it = suggestions.begin(); it != suggestions.end(); ++it)
            cout << names[*it] << " ";
        cout << "\n";
    }

    int socialDistance(int from, int to) {
        if (from == to) return 0;
        vector<int> dist(V, -1);
        queue<int> q;
        dist[from] = 0;
        q.push(from);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (size_t i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i].first;
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    if (v == to) return dist[v];
                    q.push(v);
                }
            }
        }
        return -1; 
    }

    void findInfluencer() {
        int maxDeg = -1, influencer = -1;
        for (int i = 0; i < V; i++) {
            if ((int)adj[i].size() > maxDeg) {
                maxDeg = adj[i].size();
                influencer = i;
            }
        }
        cout << "Influencer: " << names[influencer]
             << " (" << maxDeg << " teman)\n";
    }

    void detectCommunities() {
        vector<bool> visited(V, false);
        int idx = 1;
        cout << "Komunitas yang terdeteksi:\n";
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                cout << "  Komunitas " << idx++ << ": ";
                queue<int> q;
                q.push(i);
                visited[i] = true;
                while (!q.empty()) {
                    int u = q.front(); q.pop();
                    cout << names[u] << " ";
                    for (size_t j = 0; j < adj[u].size(); j++) {
                        int v = adj[u][j].first;
                        if (!visited[v]) {
                            visited[v] = true;
                            q.push(v);
                        }
                    }
                }
                cout << "\n";
            }
        }
    }

    void shortestPath(int from, int to) {
        if (from == to) {
            cout << "Jalur: " << names[from] << " (sama orang)\n";
            return;
        }
        vector<int> prev(V, -1);
        vector<bool> visited(V, false);
        queue<int> q;
        visited[from] = true;
        q.push(from);
        bool found = false;

        while (!q.empty() && !found) {
            int u = q.front(); q.pop();
            for (size_t i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i].first;
                if (!visited[v]) {
                    visited[v] = true;
                    prev[v] = u;
                    if (v == to) { found = true; break; }
                    q.push(v);
                }
            }
        }

        cout << "Jalur " << names[from] << " -> " << names[to] << ": ";
        if (!found) {
            cout << "tidak terhubung\n";
            return;
        }
        vector<string> path;
        for (int cur = to; cur != -1; cur = prev[cur])
            path.push_back(names[cur]);
        reverse(path.begin(), path.end());
        for (int i = 0; i < (int)path.size(); i++) {
            cout << path[i];
            if (i + 1 < (int)path.size()) cout << " -> ";
        }
        cout << " (" << (int)path.size() - 1 << " hop)\n";
    }
};

int main() {
    SocialNetwork sn(vector<string>({"Alice","Bob","Charlie","Diana","Eko","Fita","Gilang","Hana"}));

    sn.addFriendship(0, 1, 9);  // Alice - Bob
    sn.addFriendship(0, 3, 7);  // Alice - Diana
    sn.addFriendship(0, 4, 5);  // Alice - Eko
    sn.addFriendship(1, 2, 8);  // Bob   - Charlie
    sn.addFriendship(1, 5, 6);  // Bob   - Fita
    sn.addFriendship(2, 6, 4);  // Charlie - Gilang
    sn.addFriendship(3, 4, 10); // Diana - Eko
    sn.addFriendship(5, 7, 3);  // Fita  - Hana
    sn.addFriendship(6, 7, 7);  // Gilang- Hana

    cout << "=== FITUR 1: Teman Langsung ===\n";
    for (int i = 0; i < 8; i++) sn.listFriends(i);

    cout << "\n=== FITUR 2: Saran Pertemanan ===\n";
    sn.friendSuggestions(0); // Alice
    sn.friendSuggestions(2); // Charlie
    sn.friendSuggestions(7); // Hana

    cout << "\n=== FITUR 3: Jarak Sosial ===\n";
    cout << "Alice  -> Hana   : " << sn.socialDistance(0, 7) << " hop\n";
    cout << "Charlie -> Eko   : " << sn.socialDistance(2, 4) << " hop\n";
    cout << "Diana  -> Hana   : " << sn.socialDistance(3, 7) << " hop\n";
    cout << "Gilang -> Diana  : " << sn.socialDistance(6, 3) << " hop\n";

    cout << "\n=== FITUR 4: Influencer ===\n";
    sn.findInfluencer();

    cout << "\n=== FITUR 5: Deteksi Komunitas ===\n";
    sn.detectCommunities();

    cout << "\n=== FITUR 6: Jalur Terpendek ===\n";
    sn.shortestPath(4, 7); // Eko -> Hana
    sn.shortestPath(3, 6); // Diana -> Gilang
    sn.shortestPath(7, 0); // Hana -> Alice

    return 0;
}
