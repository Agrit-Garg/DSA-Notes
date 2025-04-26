# 📘 Graph: Bellman-Ford Algorithm

## 🔵 Bellman-Ford Algorithm

### Objective:
Find the shortest path from a `source vertex` to all other `vertices` in a weighted, directed graph.

### Key Features:
- **Works for graphs with negative weight edges.**
- **Can detect negative weight cycles in the graph.**

### Limitation of Dijkstra's Algorithm:
- Does not work with graphs that have negative weight edges.
- Cannot detect negative weight cycles.
---
## 🧩 Problem Statement

### Graph
- A weighted, directed graph with **V** vertices and **E** edges, where each edge is represented as `[u, v, w]` (an edge from vertex **u** to vertex **v** with weight **w**).
### Source
- A source vertex **src**.

### Objective
- Find the shortest distance from **src** to all other vertices.

### Constraints
- If a vertex is unreachable, its distance should be marked as **10^8**.
- If the graph contains a negative weight cycle, return `[-1]`.


---
## ✅ Example

```cpp
Input:
  V = 5
  edges = {{0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2}, {1, 4, 2}, {3, 2, 5}, {3, 4, -3}}
  src = 0

Output:
  [0, -1, 2, -2, 1]

```
## 📝 Explanation

- The **source vertex** is `0`.

- The **shortest distance from 0 to 1** is `-1` due to the edge `(0, 1, -1)`.

- The **shortest distance from 0 to 2** is `2` via the path `0 -> 1 -> 2`.

- The **shortest distance from 0 to 3** is `-2` via the path `0 -> 1 -> 3`.

- The **shortest distance from 0 to 4** is `1` via the path `0 -> 1 -> 4`.

---
## ⚡ Approach: Bellman-Ford Algorithm (Relaxation) 

### 1. Initialization:
Initialize the distance array `dist[]` with `10^8` for all vertices except the source vertex, which is set to 0.

### 2. Relaxation:
For `V-1` times, iterate through all edges and try to relax them. Relaxation means if `dist[u] + wt < dist[v]`, update `dist[v]`.

### 3. Negative Cycle Detection:
After `V-1` iterations, iterate over all edges again. If any edge can still be relaxed, return `[-1]` indicating the presence of a negative cycle.

### 4. Result:
If no negative cycle is found, return the `dist[]` array containing the shortest distances from `src` to all other vertices.


---
## 🧠 C++ Code

```cpp
vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {

    // Step 1: Initialize distance array with a large value (infinity)
    vector<int> dist(V, 1e8);
    dist[src] = 0;  // The distance to the source is 0

    // Step 2: Relax all edges (V-1) times
    for (int i = 0; i < V - 1; i++) {
        for (auto edge : edges) {
            int u = edge[0];  // Starting node
            int v = edge[1];  // Ending node
            int wt = edge[2]; // Weight of the edge
            
            // If the distance to the destination vertex can be shortened by taking the edge
            if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;  // Relax the edge
            }
        }
    }

    // Step 3: Check for negative weight cycles
    for (auto edge : edges) {
        int u = edge[0]; 
        int v = edge[1];  
        int wt = edge[2]; 

        // If we can relax an edge in the V-th pass, there is a negative cycle
        if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
            return {-1};  // Negative cycle detected
        }
    }

    return dist;
}


```

## ⏱️ Time Complexity 
- Relaxing all edges for `V-1` iterations takes `O(V × E)`, where `V` is the number of vertices and `E` is the number of edges.
- Checking for negative cycles takes another `O(E)`.

**Total Time Complexity:**  `O(V × E)`

## 💾 Space Complexity
- The distance array takes `O(V)` space to store the shortest distances for each vertex.
- The edges array stores `O(E)` edges.

**Total Space Complexity:**  `O(V + E)`

  





