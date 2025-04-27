//To check that our code is correct with thread safety, we simulate multiple threads trying to lock, unlock, or upgrade nodes concurrently. 
// We create multiple threads that perform operations like lock(), unlock(), and upgrade() on different nodes simultaneously.

#include <iostream>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <thread> 
using namespace std;

// Structure to represent each node in the tree
struct Node {
    string name;                        // Unique name of the node
    Node* parent = nullptr;             // Pointer to parent node
    vector<Node*> children;             // List of children nodes
    bool isLocked = false;              // Lock status of this node
    int lockedBy = -1;                  // User ID who locked the node
    int lockedDescendants = 0;          // Number of locked descendants
    mutex nodemutex;                    // Mutex for thread safety

    Node(string nodeName) : name(nodeName) {}
};

// Global map for quick access to nodes by name
unordered_map<string, Node*> nodeMap;

// Function definitions (same as your existing code)

bool canLockOrUnlock(Node* node) {
    Node* curr = node->parent;
    while (curr) {
        if (curr->isLocked) return false;
        curr = curr->parent;
    }
    return true;
}

void updateLockedDescendants(Node* node, int change) {
    Node* curr = node->parent;
    while (curr) {
        curr->lockedDescendants += change;
        curr = curr->parent;
    }
}

bool hasLockedDescendants(Node* node, int uid, vector<Node*>& toUnlock) {
    if (node->isLocked) {
        if (node->lockedBy != uid) return false;
        toUnlock.push_back(node);
    }
    for (Node* child : node->children) {
        if (!hasLockedDescendants(child, uid, toUnlock)) return false;
    }
    return !toUnlock.empty();
}

bool lock(string name, int uid) {
    Node* node = nodeMap[name];
    lock_guard<mutex> lock(node->nodemutex);

    if (node->isLocked || node->lockedDescendants > 0 || !canLockOrUnlock(node)) return false;
    node->isLocked = true;
    node->lockedBy = uid;
    updateLockedDescendants(node, 1);
    return true;
}

bool unlock(string name, int uid) {
    Node* node = nodeMap[name];
    lock_guard<mutex> lock(node->nodemutex);
 
    if (!node->isLocked || node->lockedBy != uid) return false;
    node->isLocked = false;
    node->lockedBy = -1;
    updateLockedDescendants(node, -1);
    return true;
}

bool upgrade(string name, int uid) {
    Node* node = nodeMap[name];
    lock_guard<mutex> lock(node->nodemutex);
    
    if (node->isLocked || node->lockedDescendants == 0) return false;

    vector<Node*> toUnlock;
    if (!hasLockedDescendants(node, uid, toUnlock)) return false;

    for (Node* n : toUnlock) {
        n->isLocked = false;
        n->lockedBy = -1;
        updateLockedDescendants(n, -1);
    }

    node->isLocked = true;
    node->lockedBy = uid;
    updateLockedDescendants(node, 1);
    return true;
}

int main() {
    int N, m, Q;
    cin >> N >> m >> Q;

    // Read node names and create node objects
    vector<string> names(N);
    for (int i = 0; i < N; ++i) {
        cin >> names[i];
        nodeMap[names[i]] = new Node{names[i]};
    }

    // Build a fully balanced m-ary tree
    for (int i = 1; i < N; ++i) {
        int parentIndex = (i - 1) / m; 
        Node* parent = nodeMap[names[parentIndex]]; 
        Node* child = nodeMap[names[i]];
        child->parent = parent;
        parent->children.push_back(child);
    }

    // Function to simulate a query (lock/unlock/upgrade) in a thread
    auto queryThread = [](int type, string name, int uid) {
        if (type == 1)
            cout << (lock(name, uid) ? "true" : "false") << endl;
        else if (type == 2)
            cout << (unlock(name, uid) ? "true" : "false") << endl;
        else
            cout << (upgrade(name, uid) ? "true" : "false") << endl;
    };

    // Create threads for multiple queries (simulating concurrent operations)
    vector<thread> threads;
    while (Q--) {
        int type, uid;
        string name;
        cin >> type >> name >> uid;

        // Launch a new thread for each query
        threads.push_back(thread(queryThread, type, name, uid));
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
