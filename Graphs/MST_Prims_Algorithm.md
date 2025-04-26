# 📘 Graph: Minimum Spanning Tree (Prim’s Algorithm)

## 🔵 What's a Spanning Tree?

A **spanning tree** is a subgraph that includes all **N** nodes and exactly **N-1** edges, with no cycles, and every node is reachable.


## 🔵 What's a Minimum Spanning Tree (MST)?

Among all possible spanning trees, a **Minimum Spanning Tree (MST)** has the minimum total weight (sum of edge weights).


## 🔵 Prim’s Algorithm (Greedy Approach)

- Builds the MST by picking the smallest weight edge at every step, ensuring no cycles are formed.
- Always extends from an already selected part of the MST.

---
## 🧩 Problem Statement
Given a connected, undirected, and weighted graph with **V** vertices and **E** edges, find the sum of the weights of the edges in its Minimum Spanning Tree (MST).

The graph is provided in the form of an adjacency list.

---
## ✅ Example

```cpp
Input:
  V = 5
  adjacency list =
  {
      0: {{1, 2}, {3, 6}},
      1: {{0, 2}, {2, 3}, {3, 8}, {4, 5}},
      2: {{1, 3}, {4, 7}},
      3: {{0, 6}, {1, 8}},
      4: {{1, 5}, {2, 7}}
  }
Output:
  Total MST Weight = 16

```
## 📝 Explanation

The MST edges are:

- 0 → 1 (weight 2)
- 1 → 2 (weight 3)
- 1 → 4 (weight 5)
- 0 → 3 (weight 6)

**Sum of weights:**  2 + 3 + 5 + 6 = 16

### Visualize MST edges selected:
```cpp
   (2)
0 ------ 1
|        | \
| (6)   (5) (3)
|        |   \
3        4    2

```
---
## ⚡ 1. Approach: Prim’s Algorithm (Greedy)
### Finding only MST Sum
- Maintain a **visited array** to track selected nodes.
- Use a **min-heap (priority queue)** to always pick the smallest weight edge.
- **Start with any node.**
- **For each node:**
  - Pick the minimum weight adjacent edge.
  - If the neighbor is **unvisited**, add it to the MST and push its adjacent edges into the heap.
  - Continue until **all nodes** are included.

### ✅ Ensures:
- No cycles
- Minimum total weight

---
## 🧠 C++ Code

```cpp
#include <vector>
#include <queue>
using namespace std;

// Function to find the sum of weights of the Minimum Spanning Tree (MST)
int spanningTree(int V, vector<vector<int>> adj[]) {
    // Min-heap: {weight, node}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

    // Track visited nodes
    vector<int> visited(V, 0);
    
    // Start from node 0 with weight 0
    minHeap.push({0, 0});
    
    int totalWeight = 0;
    
    while (!minHeap.empty()) {
        int weight = minHeap.top().first;
        int node = minHeap.top().second;
        minHeap.pop();
        
        // If node is already visited, skip
        if (visited[node]) continue;
        
        // Add edge weight to total MST weight
        visited[node] = 1;
        totalWeight += weight;
        
        // Traverse adjacent nodes
        for (auto neighbor : adj[node]) {
            int adjNode = neighbor[0];
            int edgeWeight = neighbor[1];
            
            // If adjacent node is unvisited, push it to the heap
            if (!visited[adjNode]) {
                minHeap.push({edgeWeight, adjNode});
            }
        }
    }
    
    return totalWeight;
}

```

## ⏱️ Time Complexity 
- Each edge is **pushed and popped** from the min-heap → **O(E log E)** operations.
- Processing neighbors for each node takes **O(E)**.
- **Final Time Complexity** ⇒ **O(E log E)**

## 💾 Space Complexity
- **O(V)** for the visited array.
- **O(E)** for the priority queue (min-heap stores up to all edges in the worst case).
- **Total Auxiliary Space** ⇒ **O(E)**

---

## ⚡ 2. Approach: Prim’s Algorithm with parent tracking (Greedy)
### Finding both MST Sum and the edges that form MST


1. **Use a min-heap** that stores `{weight, node, parent}`.
2. **Maintain a visited array** to avoid revisiting nodes.
3. **Maintain a list of MST edges** — store edges as `{parent, node}` whenever we pick a new node.
4. **Start with node 0** with weight 0 and parent -1 (no parent).
5. **For every extracted node**:
   - If not visited:
     - Mark as visited.
     - If parent exists (i.e., not -1), add the edge `(parent → node)` to MST edge list.
     - Add the weight to the total MST sum.
     - Push all adjacent unvisited neighbors into the min-heap.

✅ **This way, you collect both**:
- Total MST weight.
- List of edges forming the MST.
---
## 🧠 C++ Code
```cpp
#include <vector>
#include <queue>
using namespace std;

// Function to find MST weight and edges
pair<int, vector<pair<int, int>>> spanningTreeWithEdges(int V, vector<vector<int>> adj[]) {
    // Min-heap: {weight, node, parent}
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> minHeap;
    
    vector<int> visited(V, 0);        // To track visited nodes
    vector<pair<int, int>> mstEdges;  // To store MST edges: {parent, node}
    int totalWeight = 0;              // To store total weight of MST
    
    // Start with node 0, weight 0, parent -1
    minHeap.push({0, 0, -1});
    
    while (!minHeap.empty()) {
        auto [weight, node, parent] = minHeap.top();
        minHeap.pop();
        
        // Skip if node is already visited
        if (visited[node]) continue;
        
        visited[node] = 1;       // Mark node as visited
        totalWeight += weight;   // Add weight to total MST weight
        
        // If parent exists, add the edge (parent -> node)
        if (parent != -1) {
            mstEdges.push_back({parent, node});
        }
        
        // Push all adjacent nodes to the heap
        for (auto neighbor : adj[node]) {
            int adjNode = neighbor[0];
            int edgeWeight = neighbor[1];
            
            if (!visited[adjNode]) {
                minHeap.push({edgeWeight, adjNode, node});
            }
        }
    }
    
    return {totalWeight, mstEdges};
}
```

## ⏱️ Time Complexity
- Each edge is pushed and popped from the min-heap → **O(E log E)** operations.
- Processing neighbors takes **O(E)** time.

➔ **Total time complexity ⇒ O(E log E)**

## 💾 Space Complexity
- **O(V)** for the visited array.
- **O(E)** for the priority queue (at most all edges).
- **O(V)** for storing MST edges (V-1 edges ≈ O(V)).

➔ **Total auxiliary space ⇒ O(E)**

