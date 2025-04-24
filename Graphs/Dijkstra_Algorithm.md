# 📘 Graph: Dijkstra’s Algorithm (Single Source Shortest Path)

## 🧩 Problem Statement

Given an **undirected, weighted graph** with  
- \(V\) vertices (numbered \(0\) to \(V-1\))  
- \(E\) edges  

Each edge is represented as \([u, v, w]\), indicating an edge between \(u\) and \(v\) of weight \(w\).  

Compute the **shortest distance** from a source vertex `src` to every other vertex. Return a vector `dist` of size \(V\) where `dist[i]` is the shortest path length from `src` to vertex \(i\).  

> **Note:** The graph is connected and contains **no negative-weight** cycles or edges.

---

## ✅ Example

```cpp
Input:
V = 5, E = 6
edges = [
  [0, 1, 4],
  [0, 2, 1],
  [2, 1, 2],
  [1, 3, 1],
  [2, 3, 5],
  [3, 4, 3]
]
src = 0
```
```cpp
Output:
dist = [0, 3, 1, 4, 7]
```
## 🔎 Approach: Dijkstra’s Algorithm (Min‑Heap Version)

1. **Build adjacency list**  
-   For each edge [u, v, w], add (v, w) to adj[u] and (u, w) to adj[v].  

2. **Initialize distances**  
   
```cpp
   dist.assign(V, INT_MAX);
   dist[src] = 0;
```
3. **Priority queue (min‑heap)**

- Store pairs (currentDistance, node).
- Always extract the node with the smallest tentative distance.

4. **Relaxation**

- For each neighbor (nei, wt) of node :
```cpp
if (dist[node] + wt < dist[nei]) {
    dist[nei] = dist[node] + wt;
    pq.push({dist[nei], nei});
}
```
5. **Result**
- After the heap is empty, dist[i] holds the shortest distance from src to i.

---
## 🧠 C++ Code

```cpp

vector<int> dijkstra(int V, vector<vector<int>>& edges, int src) {
    // 1. Build graph
        vector<vector<pair<int,int>>> adj(V);
        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
    
        // 2. Distance array, initialize to "infinite"
        const int INF = INT_MAX;
        vector<int> dist(V, INF);
        dist[src] = 0;
    
        // 3. Min-heap of (distance, node)
        priority_queue<
            pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>
        > minHeap;
        minHeap.push({0, src});
    
        // 4. Main loop: extract-min and relax edges
        while (!minHeap.empty()) {
            int currDist = minHeap.top().first;
            int u = minHeap.top().second;
            minHeap.pop();
    
            // If we pulled a stale entry, skip
            if (currDist > dist[u]) continue;
    
            for (auto &pr : adj[u]) {
                int v = pr.first, w = pr.second;
                if (currDist + w < dist[v]) {
                    dist[v] = currDist + w;
                    minHeap.push({dist[v], v});
                }
            }
        }
    
        return dist;
    }
```

## ⏱️ Time Complexity

- **Heap Operations:** Each push or pop takes (O(log V)).  
- **Total Work:** We process each vertex once and each edge once, leading to  
  \[
    O((V + E)log V)
  \]

---

## 💾 Space Complexity

- **Adjacency List:** Stores all vertices and edges → \(O(V + E)\).  
- **Distance Array:** One entry per vertex → \(O(V)\).  
- **Heap:** In the worst case, can hold all vertices → \(O(V)\).

**Overall:** \(O(V + E)\) space.


