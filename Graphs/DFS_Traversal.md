# 📘 Graph: Depth First Search (DFS)

## 🧩 Problem Statement
Given a connected undirected graph with \(V\) vertices (numbered 0 to
 V-1 ), represented as an adjacency list , perform a
  **Depth First Search (DFS)** starting from vertex `0`. Visit each 
  node’s neighbors in the exact order they appear in `adj`, and 
  return the sequence of visited vertices.

---
## ✅ Example

```cpp
Input:
  adj = [[2,3,1], [0], [0,4], [0], [2]]

Output: [0, 2, 4, 3, 1]

Explanation: 
Starting from 0, the DFS traversal proceeds as follows:
Visit 0 → Output: 0 
Visit 2 (the first neighbor of 0) → Output: 0, 2 
Visit 4 (the first neighbor of 2) → Output: 0, 2, 4 
Backtrack to 2, then backtrack to 0, and visit 3 → Output: 0, 2, 4, 3 
Finally, backtrack to 0 and visit 1 → Final Output: 0, 2, 4, 3, 1
```

```cpp
   0
 / | \
2  3  1
|
4
```
#### DFS order : 0 → 2 → 4 → 3 → 1
---

## 🔎 Approach: Depth First Search (Recursive)

1. **Visited array:** track seen nodes.  
2. **Recursive DFS function:**  
   - Mark `node` as visited and append to result.  
   - Recurse on each unvisited neighbor in `adj[node]` order.  
3. **Initiate** from node `0`.  

This ensures you explore as deep as possible down each path before backtracking.

---
## 🧠 C++ Code

```cpp
void dfsVisit(int u, vector<vector<int>>& adjacencyList, vector<bool>& seen, vector<int>& order) {

    seen[u] = true;
    order.push_back(u);

    // Explore all neighbors of u in the given adjacency order
    for (int v : adjacencyList[u]) {
        if (!seen[v]) {
            dfsVisit(v, adjacencyList, seen, order);
        }
    }
}

vector<int> depthFirstSearch( vector<vector<int>>& adjacencyList) {
    int n = adjacencyList.size();
    vector<bool> seen(n, false);   // Track visited nodes
    vector<int> order;            // Store DFS traversal order

    dfsVisit(0, adjacencyList, seen, order);
    return order;
}
```

## ⏱️ Time Complexity 
- **O(V + E)**: Each vertex and edge is visited once.

## 💾 Space Complexity
- **O(V)** for the recursive call stack in the worst case (a linear chain of V vertices).  
- **O(V)** for the `seen` boolean array.  
- **O(V)** for the output `order` list.  

**Total auxiliary space ⇒ O(V).**


