# 📘 Graph: Floyd-Warshall Algorithm

## 🔵 Floyd-Warshall Algorithm

### Goal:
- Find shortest paths between every pair of nodes in a directed weighted graph (even with negative edges).
- Also called **Multisource shortest path algorithm:** Shortest distance between every (i, j) pair.

### 🛑 Also Detects Negative Cycles
- After running the algorithm, if `cost[i][i] < 0` for any node i, a negative cycle exists.

---
## 🧩 Problem Statement

- You are given a **directed graph** represented by an adjacency matrix `dist[n][n]`.
- `dist[i][j]` = weight of edge from node `i` to `j`.
- `dist[i][j] = 1e8 (10^8)` if no direct edge.
- Modify the `dist` matrix **in-place** to store **shortest distances** between every pair.

---

## ✅ Example

### Input:
```cpp
dist = [
  [0,   4, 1e8, 5,   1e8],
  [1e8, 0, 1,   1e8, 6],
  [2,   1e8, 0, 3,   1e8],
  [1e8, 1e8, 1, 0,   2],
  [1,   1e8, 1e8, 4, 0]
]
```
### Output:
```cpp
[
  [0, 4, 5, 5, 7],
  [3, 0, 1, 4, 6],
  [2, 6, 0, 3, 5],
  [3, 7, 1, 0, 2],
  [1, 5, 5, 4, 0]
]
```

---
## ⚡ Approach: (Dynamic Programming) 

### 1. Idea:
- For each node `via` , check if going from `i → via → j` is shorter than directly `i → j`.
If yes, update `dist[i][j]`.

### 2. Steps:
1. Loop for each intermediate node `via = 0` to `n-1`.

2. For each source node `i` and destination node `j`:

3. If `dist[i][via] + dist[via][j] < dist[i][j]`, update `dist[i][j]`.

4. Skip update if any path is unreachable (`1e8`).


---
## 🧠 C++ Code

```cpp
void floydWarshall(vector<vector<int>> &dist) {
    int n = dist.size();
    
    // Try every node as an intermediate node (via)
    for (int via = 0; via < n; via++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                
                // If there is no path from i to via OR via to j, skip
                if (dist[i][via] == 1e8 || dist[via][j] == 1e8)
                    continue;
                
                // Update the distance if a shorter path is found via 'via'
                dist[i][j] = min(dist[i][j], dist[i][via] + dist[via][j]);
            }
        }
    }
}

```

## ⏱️ Time Complexity 
- O(V³) — Triple nested loop over all nodes.


## 💾 Space Complexity
- O(V²) — The dist matrix.

  

