# 📘 Graph: Breadth First Search (BFS): Level Order Traversal

## 🧩 Problem Statement
Given a connected undirected graph with \(V\) vertices (numbered 0 to
V-1 ), represented as an adjacency list , perform a 
 **Breadth‑First Search (BFS)** starting from vertex `0`. Visit each
vertex’s neighbors in the **exact order** they appear in `adjacencyList`,
and return the **sequence of visited vertices**.

---

## ✅ Example

```vb
Input:
  adj = [[2,3,1], [0], [0,4], [0], [2]]

Output: [0, 2, 3, 1, 4]
```

```cpp
   0
 / | \
2  3  1
|
4
```
#### BFS order: 0 → 2 → 3 → 1 → 4
---

## 🔎 Approach: Standard BFS

1. **Visited array:** Track which nodes are already seen.  
2. **Queue:** Initialize with source node `0`, mark visited.
3. **Loop:**
    - Pop front node, append to result.  
    - For each neighbor in `adj[node]` order:
        - If not visited, mark visited and enqueue.
4. Return the result list.  

---

## 🧠 C++ Code

```cpp
vector<int> bfsTraversal(const vector<vector<int>>& adjacencyList) {
    int n = adjacencyList.size();
    vector<int> order;
    order.reserve(n);
    
    vector<bool> seen(n, false);
    queue<int> q;
    
    // Start from vertex 0
    seen[0] = true;
    q.push(0);
    
    while (!q.empty()) {
        int u = q.front(); 
        q.pop();
        
        order.push_back(u);
        
        // Enqueue unvisited neighbors in given order
        for (int v : adjacencyList[u]) {
            if (!seen[v]) {
                seen[v] = true;
                q.push(v);
            }
        }
    }
    
    return order;
}
```

## ⏱️ Time Complexity 
- Visiting each vertex exactly once and checking all its edges ⇒ **O(V + E)**.

## 💾 Space Complexity
- **O(V)** for the `seen` array.  
- **O(V)** for the queue in the worst case.  
- **O(V)** for the output `order` list.  
- Total auxiliary space ⇒ **O(V)**.


