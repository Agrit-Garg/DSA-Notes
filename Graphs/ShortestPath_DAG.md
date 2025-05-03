# 📘 Graph: Shortest Path in Directed Acyclic Graph

### 🔹 What is a DAG?

A **Directed Acyclic Graph (DAG)** is a graph that is **directed** (edges have direction) and **acyclic** (no cycles).

---


## 🧩 Problem Statement

- You are given a **Directed Acyclic Graph** with **V vertices** (0 to V-1).
- An **edge list `edges[][]`** of length E is given, where each edge is of the form **[u, v, weight]**, representing a directed edge from **u to v** with **weight**.
- **Objective**: Find the **shortest distance** from **source vertex 0** to **every other vertex**.
- If a node is **not reachable**, return **-1** for that node.

---

## ✅ Example

### Input:
```cpp
V = 6  
edges = [
  [0,1,2],
  [0,4,1],
  [4,5,4],
  [4,2,2],
  [1,2,3],
  [2,3,6],
  [5,3,1]
]
```
### Output:
```cpp
[0, 2, 3, 6, 1, 5]
```

### Explanation:
- **0 → 1** = 2  
- **0 → 4 → 2** = 1 + 2 = 3  
- **0 → 4 → 5 → 3** = 1 + 4 + 1 = 6  
- **0 → 4** = 1  
- **0 → 4 → 5** = 1 + 4 = 5  

---
## 💡 Intuition
In a **DAG**, we can perform **Topological Sort** since there’s no cycle.

After sorting:

- Relax the distances in **topological order**.
- Each node is processed **once** and always **before its children**.
- This ensures efficient computation of **shortest paths**.

## ⚡ Approach: (Topological Sort) 

- Convert edge list to adjacency list.
- Run DFS to perform **Topological Sort**.
- Initialize distance from source (0) to all nodes as **∞**, except source = 0.
- Process nodes in **topo order**, and for each, **relax all its outgoing edges**.
- Replace any remaining **∞** with **-1**.

---
## 🧠 C++ Code

```cpp

// Perform DFS to get Topological Sort
void dfs(int node, vector<int> &visited, stack<int> &topoStack,
            vector<vector<pair<int,int>>> &adj) {
    visited[node] = 1;
    for (auto neighbor : adj[node]) {
        if (!visited[neighbor.first]) {
            dfs(neighbor.first, visited, topoStack, adj);
        }
    }
    topoStack.push(node);  // Push after visiting all neighbors
}

vector<int> shortestPath(int V, int E, vector<vector<int>>& edges) {
    // Step 1: Build adjacency list from edge list
    vector<vector<pair<int, int>>> adj(V);
    for (auto &edge : edges) {
        int u = edge[0], v = edge[1], wt = edge[2];
        adj[u].push_back({v, wt});
    }

    // Step 2: Topological Sort using DFS
    vector<int> visited(V, 0);
    stack<int> topoStack;
    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            dfs(i, visited, topoStack, adj);
        }
    }

    // Step 3: Initialize distance vector
    vector<int> dist(V, INT_MAX);
    dist[0] = 0;  // Distance to source is 0

    // Step 4: Relax edges in topological order
    while (!topoStack.empty()) {
        int curr = topoStack.top();
        topoStack.pop();

        if (dist[curr] != INT_MAX) {
            for (auto &neigh : adj[curr]) {
                int next = neigh.first, weight = neigh.second;
                if (dist[next] > dist[curr] + weight) {
                    dist[next] = dist[curr] + weight;
                }
            }
        }
    }

    // Step 5: Replace unreachable distances with -1
    for (int &d : dist) {
        if (d == INT_MAX) d = -1;
    }

    return dist;
}

```

### ⏱️ Time Complexity: O(V + E)
- **Topological Sort (DFS)**:
  - Visits every node once → O(V)
  - Explores all edges once → O(E)
  
- **Edge Relaxation** (one pass over topologically sorted nodes):
  - Each edge considered at most once → O(E)

### 💾 Space Complexity: O(V + E)
- **Adjacency List**: O(V + E)
- **Visited array & Distance array**: O(V)
- **Recursion stack (DFS) & Topological stack**: up to O(V)


