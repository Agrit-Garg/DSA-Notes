#include <iostream>
#include <unordered_map>
#include <vector>
#include <mutex>
using namespace std;

struct Node {
    string name;
    Node* parent = nullptr;
    vector<Node*> children;

    bool isLocked = false;
    int lockedBy = -1;
    int lockedDescendants = 0;

    mutex nodeMutex; // for thread-safe operations
};

unordered_map<string, Node*> nodeMap;
mutex mapMutex; // For thread-safe access to nodeMap

bool canLockOrUnlock(Node* node) {
    Node* curr = node->parent;
    while (curr) {
        lock_guard<mutex> guard(curr->nodeMutex);
        if (curr->isLocked) return false;
        curr = curr->parent;
    }
    return true;
}

void updateLockedDescendants(Node* node, int delta) {
    Node* curr = node->parent;
    while (curr) {
        lock_guard<mutex> guard(curr->nodeMutex);
        curr->lockedDescendants += delta;
        curr = curr->parent;
    }
}

bool hasLockedDescendants(Node* node, int uid, vector<Node*>& toUnlock) {
    lock_guard<mutex> guard(node->nodeMutex);
    if (node->isLocked) {
        if (node->lockedBy != uid) return false;
        toUnlock.push_back(node);
    }
    for (Node* child : node->children) {
        if (!hasLockedDescendants(child, uid, toUnlock)) return false;
    }
    return !toUnlock.empty();
}

bool lock(const string& name, int uid) {
    Node* node;
    {
        lock_guard<mutex> mapGuard(mapMutex);
        node = nodeMap[name];
    }

    lock_guard<mutex> guard(node->nodeMutex);
    if (node->isLocked || node->lockedDescendants > 0 || !canLockOrUnlock(node))
        return false;

    node->isLocked = true;
    node->lockedBy = uid;
    updateLockedDescendants(node, 1);
    return true;
}

bool unlock(const string& name, int uid) {
    Node* node;
    {
        lock_guard<mutex> mapGuard(mapMutex);
        node = nodeMap[name];
    }

    lock_guard<mutex> guard(node->nodeMutex);
    if (!node->isLocked || node->lockedBy != uid)
        return false;

    node->isLocked = false;
    node->lockedBy = -1;
    updateLockedDescendants(node, -1);
    return true;
}

bool upgrade(const string& name, int uid) {
    Node* node;
    {
        lock_guard<mutex> mapGuard(mapMutex);
        node = nodeMap[name];
    }

    lock_guard<mutex> guard(node->nodeMutex);
    if (node->isLocked || node->lockedDescendants == 0) return false;

    vector<Node*> toUnlock;
    if (!hasLockedDescendants(node, uid, toUnlock)) return false;

    for (Node* n : toUnlock) {
        lock_guard<mutex> g(n->nodeMutex);
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
    vector<string> names(N);

    for (int i = 0; i < N; ++i) {
        cin >> names[i];
        nodeMap[names[i]] = new Node{names[i]};
    }

    for (int i = 1; i < N; ++i) {
        int parentIndex = (i - 1) / m;
        nodeMap[names[i]]->parent = nodeMap[names[parentIndex]];
        nodeMap[names[parentIndex]]->children.push_back(nodeMap[names[i]]);
    }

    while (Q--) {
        int type, uid;
        string name;
        cin >> type >> name >> uid;

        bool result = false;
        if (type == 1) result = lock(name, uid);
        else if (type == 2) result = unlock(name, uid);
        else result = upgrade(name, uid);

        cout << (result ? "true" : "false") << endl;
    }

    return 0;
}
