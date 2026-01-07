#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <climits>
using namespace std;

class Graph {
    struct Edge {
        int v, w;
        Edge* next;
    };
    int V;
    Edge** adj;
    bool* active;

    void DFSutil(int u, bool vis[]) {
        vis[u] = true;
        cout << u << " ";
        for (Edge* e = adj[u]; e; e = e->next) {
            if (!vis[e->v] && active[e->v]) DFSutil(e->v, vis);
        }
    }

    bool cycleUtil(int u, bool vis[], int parent) {
        vis[u] = true;
        for (Edge* e = adj[u]; e; e = e->next) {
            if (!vis[e->v] && active[e->v]) {
                if (cycleUtil(e->v, vis, u)) return true;
            } else if (e->v != parent && active[e->v]) return true;
        }
        return false;
    }

public:
    Graph(int v = 10) {
        V = v;
        adj = new Edge*[V];
        active = new bool[V];
        for (int i = 0; i < V; i++) {
            adj[i] = NULL;
            active[i] = false; // All stations start INACTIVE
        }
    }

    ~Graph() {
        for (int i = 0; i < V; i++) {
            Edge* curr = adj[i];
            while (curr) {
                Edge* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
        delete[] adj;
        delete[] active;
    }

    //  Add Station
    void addStation(int id) {
        if (id < 0 || id >= V) {
            cout << "Invalid station ID! Must be 0-" << (V-1) << "\n";
            return;
        }
        if (active[id]) {
            cout << "⚠ Station " << id << " is already active.\n";
            return;
        }
        active[id] = true;
        cout << "✓ Station " << id << " activated successfully.\n";
    }

    // Delete Station
    void deleteStation(int id) {
        if (id < 0 || id >= V) {
            cout << "Invalid station ID!\n";
            return;
        }
        if (!active[id]) {
            cout << "Station " << id << " is already inactive.\n";
            return;
        }
        
        // Remove all edges connected to this station (without confirmation output)
        int removedEdges = 0;
        for (int i = 0; i < V; i++) {
            if (i != id && active[i]) {
                // Check if edge exists before removing
                Edge* check = adj[id];
                bool hasEdge = false;
                while (check) {
                    if (check->v == i) {
                        hasEdge = true;
                        break;
                    }
                    check = check->next;
                }
                
                if (hasEdge) {
                    int weight = -1;
                    auto lambdaRemove = [&](int start, int target) {
                        Edge** cur = &adj[start];
                        while (*cur) {
                            if ((*cur)->v == target) {
                                Edge* t = *cur;
                                weight = t->w;
                                *cur = (*cur)->next;
                                delete t;
                                return;
                            }
                            cur = &((*cur)->next);
                        }
                    };
                    lambdaRemove(id, i);
                    lambdaRemove(i, id);
                    if (weight != -1) removedEdges++;
                }
            }
        }
        
        active[id] = false;
        if (removedEdges > 0) {
            cout << "✓ Station " << id << " deactivated (removed " << removedEdges << " route(s)).\n";
        } else {
            cout << "✓ Station " << id << " deactivated successfully.\n";
        }
    }

    void addEdge(int u, int v, int w) {
        if (u < 0 || u >= V || v < 0 || v >= V) {
            cout << "⚠ Invalid station IDs!\n";
            return;
        }
        if (!active[u] || !active[v]) {
            cout << "⚠ Cannot add route: Station " << (!active[u] ? u : v) << " is inactive!\n";
            return;
        }
        if (w <= 0) {
            cout << "⚠ Weight must be positive!\n";
            return;
        }
        
        adj[u] = new Edge{v, w, adj[u]};
        adj[v] = new Edge{u, w, adj[v]};
        cout << "✓ Route added: Station " << u << " ↔ Station " << v << " (Weight: " << w << ")\n";
    }

    int removeEdge(int u, int v) {
        if (u < 0 || u >= V || v < 0 || v >= V) {
            cout << "⚠ Invalid station IDs!\n";
            return -1;
        }
        
        int weight = -1;
        auto lambdaRemove = [&](int start, int target) {
            Edge** cur = &adj[start];
            while (*cur) {
                if ((*cur)->v == target) {
                    Edge* t = *cur;
                    weight = t->w;
                    *cur = (*cur)->next;
                    delete t;
                    return;
                }
                cur = &((*cur)->next);
            }
        };
        
        lambdaRemove(u, v);
        lambdaRemove(v, u);
        
        if (weight == -1) {
            cout << "⚠ Route between Station " << u << " and " << v << " not found!\n";
        } else {
            cout << "✓ Route removed: Station " << u << " ↔ Station " << v << " (Weight: " << weight << ")\n";
        }
        return weight;
    }

    void display() {
        cout << "\n=== Network Status ===\n";
        bool hasActiveStations = false;
        for (int i = 0; i < V; i++) {
            if (!active[i]) continue;
            hasActiveStations = true;
            cout << "Station " << i << ": ";
            
            bool hasRoutes = false;
            for (Edge* e = adj[i]; e; e = e->next) {
                if (active[e->v]) {
                    cout << "(→" << e->v << ", weight:" << e->w << ") ";
                    hasRoutes = true;
                }
            }
            if (!hasRoutes) cout << "No routes";
            cout << endl;
        }
        if (!hasActiveStations) {
            cout << "No active stations in the network.\n";
        }
        cout << "=====================\n";
    }

    void BFS(int s) {
        if (s < 0 || s >= V) {
            cout << "Invalid starting station!\n";
            return;
        }
        if (!active[s]) {
            cout << "Starting station is inactive!\n";
            return;
        }
        
        bool* vis = new bool[V]();
        int* q = new int[V];
        int f = 0, r = 0;
        
        vis[s] = true;
        q[r++] = s;
        
        cout << "BFS Traversal: ";
        while (f < r) {
            int u = q[f++];
            cout << u << " ";
            for (Edge* e = adj[u]; e; e = e->next) {
                if (!vis[e->v] && active[e->v]) {
                    vis[e->v] = true;
                    q[r++] = e->v;
                }
            }
        }
        cout << endl;
        
        delete[] vis;
        delete[] q;
    }

    void DFS(int s) {
        if (s < 0 || s >= V) {
            cout << "Invalid starting station!\n";
            return;
        }
        if (!active[s]) {
            cout << "Starting station is inactive!\n";
            return;
        }
        
        bool* vis = new bool[V]();
        cout << "DFS Traversal: ";
        DFSutil(s, vis);
        cout << endl;
        delete[] vis;
    }

    void printPath(int parent[], int j) {
        if (parent[j] == -1) return;
        printPath(parent, parent[j]);
        cout << " → " << j;
    }

    void dijkstra(int s) {
        if (s < 0 || s >= V) {
            cout << "Invalid starting station!\n";
            return;
        }
        if (!active[s]) {
            cout << "Starting station is inactive!\n";
            return;
        }
        
        int* d = new int[V];
        int* parent = new int[V];
        bool* vis = new bool[V]();

        for (int i = 0; i < V; i++) {
            d[i] = INT_MAX;
            parent[i] = -1;
        }
        d[s] = 0;

        for (int c = 0; c < V; c++) {
            int u = -1, m = INT_MAX;
            for (int i = 0; i < V; i++) {
                if (!vis[i] && active[i] && d[i] < m) {
                    m = d[i];
                    u = i;
                }
            }

            if (u == -1) break;
            vis[u] = true;

            for (Edge* e = adj[u]; e; e = e->next) {
                if (active[e->v] && d[u] != INT_MAX && d[u] + e->w < d[e->v]) {
                    d[e->v] = d[u] + e->w;
                    parent[e->v] = u;
                }
            }
        }

        cout << "\n=== Shortest Paths from Station " << s << " ===\n";
        bool foundPaths = false;
        for (int i = 0; i < V; i++) {
            if (active[i] && i != s) {
                if (d[i] != INT_MAX) {
                    cout << "To Station " << i << " (Distance: " << d[i] << "): " << s;
                    printPath(parent, i);
                    cout << endl;
                    foundPaths = true;
                } else {
                    cout << "Station " << i << " is unreachable from " << s << "\n";
                }
            }
        }
        if (!foundPaths) {
            cout << "No reachable stations from " << s << "\n";
        }
        
        delete[] d;
        delete[] vis;
        delete[] parent;
    }

    void MST() {
        int* key = new int[V];
        int* parent = new int[V];
        bool* inMST = new bool[V]();
        
        for (int i = 0; i < V; i++) {
            key[i] = INT_MAX;
            parent[i] = -1;
        }
        
        // Find first active station that has edges
        int start = -1;
        for (int i = 0; i < V; i++) {
            if (active[i] && adj[i] != NULL) {
                start = i;
                break;
            }
        }
        
        if (start == -1) {
            cout << "No active stations with routes!\n";
            delete[] key;
            delete[] parent;
            delete[] inMST;
            return;
        }
        
        key[start] = 0;
        
        for (int c = 0; c < V; c++) {
            int u = -1, m = INT_MAX;
            for (int i = 0; i < V; i++) {
                if (active[i] && !inMST[i] && key[i] < m) {
                    m = key[i];
                    u = i;
                }
            }
            
            if (u == -1) break;
            inMST[u] = true;
            
            for (Edge* e = adj[u]; e; e = e->next) {
                if (active[e->v] && !inMST[e->v] && e->w < key[e->v]) {
                    key[e->v] = e->w;
                    parent[e->v] = u;
                }
            }
        }
        
        // Count connected stations
        int connectedCount = 0;
        int activeCount = 0;
        for (int i = 0; i < V; i++) {
            if (active[i]) {
                activeCount++;
                if (inMST[i]) connectedCount++;
            }
        }
        
        cout << "\n=== Minimum Spanning Tree ===\n";
        int totalWeight = 0;
        int mstEdges = 0;
        
        for (int i = 0; i < V; i++) {
            if (active[i] && parent[i] != -1 && inMST[i]) {
                cout << "Route: " << parent[i] << " ↔ " << i << " (Weight: " << key[i] << ")\n";
                totalWeight += key[i];
                mstEdges++;
            }
        }
        
        if (mstEdges == 0) {
            cout << "No MST possible (no routes in network).\n";
        } else {
            cout << "Total MST Weight: " << totalWeight << endl;
            
            // Count stations that actually have edges (are part of the graph)
            int stationsWithEdges = 0;
            for (int i = 0; i < V; i++) {
                if (active[i] && adj[i] != NULL) stationsWithEdges++;
            }
            
            if (connectedCount < stationsWithEdges) {
                cout << "⚠ Warning: Graph is disconnected! MST covers only " 
                     << connectedCount << " of " << stationsWithEdges << " connected stations.\n";
            }
        }
        
        delete[] key;
        delete[] parent;
        delete[] inMST;
    }

    void getBusiestStation() {
        int maxConn = -1, station = -1;
        for (int i = 0; i < V; i++) {
            if (!active[i]) continue;
            int count = 0;
            for (Edge* e = adj[i]; e; e = e->next) {
                if (active[e->v]) count++;
            }
            if (count > maxConn) {
                maxConn = count;
                station = i;
            }
        }
        
        if (station != -1) {
            cout << "Busiest Station: " << station << " with " << maxConn << " routes.\n";
        } else {
            cout << "No active stations in network.\n";
        }
    }

    void detectCycle() {
        bool* vis = new bool[V]();
        bool cycleFound = false;
        
        for (int i = 0; i < V; i++) {
            if (active[i] && !vis[i]) {
                if (cycleUtil(i, vis, -1)) {
                    cout << "⚠ Cycle detected in the network!\n";
                    cycleFound = true;
                    break;
                }
            }
        }
        
        if (!cycleFound) {
            cout << "✓ No cycles detected in the network.\n";
        }
        
        delete[] vis;
    }

    // System Statistics
    void displaySystemStatus() {
        int activeStations = 0, totalRoutes = 0;
        for (int i = 0; i < V; i++) {
            if (active[i]) {
                activeStations++;
                for (Edge* e = adj[i]; e; e = e->next) {
                    if (active[e->v]) totalRoutes++;
                }
            }
        }
        
        cout << "\n=== System Status ===\n";
        cout << "Total Stations: " << V << "\n";
        cout << "Active Stations: " << activeStations << "\n";
        cout << "Inactive Stations: " << (V - activeStations) << "\n";
        cout << "Total Routes: " << totalRoutes / 2 << " (bidirectional)\n";
        cout << "====================\n";
    }
};

#endif