# 📘 Graph: Detect Cycle in Undirected Graph


## 🧩 Problem Statement


- You're given an undirected graph with **V** vertices and **E** edges.

- Edges are given as a list of pairs `edges[][]`, where each edge connects two vertices.

- You need to determine if the graph contains a **cycle**.

- ✅ Return `true` if a cycle exists, otherwise `false`.

---

## ✅ Example

### Input:
```cpp
V = 4, E = 4  
edges = [[0, 1], [0, 2], [1, 2], [2, 3]]

```
### Output:
```cpp
true
```
### Explanation:
- One possible path: 0 → 1 → 2 → 0 forms a cycle.
```cpp
   0
  / \
 1---2
      \
       3
```

---
## 💡 Intuition

- While traversing the graph, if we **visit an already visited node** that is **not the parent**, it means there's an **alternate path**, indicating a **cycle**.

## ⚡ Approach: (BFS) 

- Use **BFS** to traverse each connected component.

- For each node, maintain its **parent** to avoid detecting the immediate back edge.

- If a **visited neighbor is not the parent**, a cycle exists.

- 🔁 Repeat for all unvisited nodes (graph may be disconnected).

---
## 🧠 C++ Code

```cpp
bool bfsCycleCheck(int start, vector<int>& visited, vector<vector<int>>& adjList) {
    queue<pair<int, int>> q; // {node, parent}
    visited[start] = 1;
    q.push({start, -1});
    
    while (!q.empty()) {
        int current = q.front().first;
        int parent = q.front().second;
        q.pop();

        for (int neighbor : adjList[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                q.push({neighbor, current});
            } 
            else if (neighbor != parent) {
                // A visited neighbor not equal to parent -> cycle
                return true;
            }
        }
    }

    return false;
}

bool isCycle(int V, vector<vector<int>>& edges) {
    vector<vector<int>> adj(V);
    
    // Convert edge list to adjacency list
    for (auto& edge : edges) {
        int u = edge[0], v = edge[1];
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected
    }

    vector<int> visited(V, 0);

    // Check for cycle in each disconnected component
    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            if (bfsCycleCheck(i, visited, adj))
                return true;
        }
    }

    return false;
}

```

## ⏱️ Time Complexity 
- **O(V + E)** : Traverses all vertices and edges once in BFS.


## 💾 Space Complexity
- `O(V)` for visited array and queue.
- `O(E)` for adjacency list.

  

