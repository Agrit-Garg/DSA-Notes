# 📘 Graph: Shortest Path in Undirected Graph (Unit Weight)

## 🧩 Problem Statement

You are given an **undirected graph** represented using an adjacency list, where each edge has a **unit weight** (i.e., weight = 1).  
Your task is to find the **shortest path from a given source vertex to all other vertices** in the graph.

If a vertex is **unreachable**, return `-1` for that vertex.

---


### ✅ Example

**Input:**

```cpp
adj = [[1, 3], [0, 2], [1, 6], [0, 4], [3, 5], [4, 6], [2, 5, 7, 8], [6, 8], [7, 6]]
src = 0
```
**Ouput:**

```cpp
[0, 1, 2, 1, 2, 3, 3, 4, 4]
```
## 📌 Constraints

- 1 <= adj.size() <= 10^4
- 0 <= edges <= adj.size() - 1

## 🔎 Approach: Breadth-First Search (BFS)

**Breadth-First Search** is the most efficient approach for unweighted graphs to find the shortest path, as it explores all vertices at the current level before moving to the next level.

---

### 🚀 How it Works

1. Initialize a distance array `dist` with size equal to number of vertices and set all values to `INT_MAX`.
2. Set the distance of source node `src` to `0`.
3. Use a queue to perform BFS.
4. For each current node, explore its neighbors.
5. If the current path gives a shorter distance to the neighbor (`curr_distance + 1 < dist[neighbor]`), update it and push it into the queue.
6. After traversal, convert all `INT_MAX` entries to `-1` (indicating unreachable nodes).


## 🧠 C++ Code

```cpp
vector<int> shortestPath(vector<vector<int>>& adjacencyList, int sourceVertex) {
    int numberOfNodes = adjacencyList.size();

    // Initialize distances to infinity
    vector<int> distanceFromSource(numberOfNodes, INT_MAX);

    // Queue for BFS traversal: stores {node, distance}
    queue<pair<int, int>> bfsQueue;

    // Distance to source is zero
    distanceFromSource[sourceVertex] = 0;
    bfsQueue.push({sourceVertex, 0});

    while (!bfsQueue.empty()) {
        int currentNode = bfsQueue.front().first;
        int currentDistance = bfsQueue.front().second;
        bfsQueue.pop();

        // Explore neighbors
        for (int neighbor : adjacencyList[currentNode]) {
            // If a shorter path is found
            if (currentDistance + 1 < distanceFromSource[neighbor]) {
                distanceFromSource[neighbor] = currentDistance + 1;
                bfsQueue.push({neighbor, currentDistance + 1});
            }
        }
    }

    // Mark unreachable nodes as -1
    for (int &distance : distanceFromSource) {
        if (distance == INT_MAX) distance = -1;
    }

    return distanceFromSource;
}
```

## ⏱️ Time Complexity

- **BFS Traversal**: Each node is visited once, and each edge is explored once.  
- **Overall**: \( \mathcal{O}(V + E) \), where:
  - \( V \) is the number of vertices (nodes)
  - \( E \) is the number of edges in the graph

---

## 💾 Space Complexity

- **Distance Array**: Stores the shortest distance for each node → \( \mathcal{O}(V) \)
- **Queue**: Used for BFS traversal → \( \mathcal{O}(V) \) in the worst case

- **Overall Space Complexity**: \( \mathcal{O}(V + E) \)
