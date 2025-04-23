# 📘 Tree: Tree Locking System
## 🧩 Problem Statement

You're given a tree structure (specifically a **complete m-ary tree**) representing a **world map hierarchy**:

### ✅ Example:

```cpp
          World
         /     \
      Asia    Africa
     /   \     /    \
  China India SouthAfrica Egypt
```

On this tree, **three operations** are defined:
---

### 🔐 1. Lock(NodeName, UserID)

Locks the node **only if**:
- It is **not already locked**.
- **No ancestor or descendant** of this node is locked.

---

### 🔓 2. Unlock(NodeName, UserID)

Unlocks the node **only if**:
- The node is **currently locked by the same user**.

---

### ⬆️ 3. UpgradeLock(NodeName, UserID)

A **special operation** that:
- Locks the given node **by replacing all its locked descendants** (if any).

#### ✅ Conditions for success:
- The node itself is **not locked**.
- **At least one descendant is locked**.
- **All locked descendants are by the same user (UID)**.
- After upgrade:
  - The node gets locked.
  - All descendant locks are removed.

---

## 📥 Input Format

1. The first line contains the number of **nodes** in the tree `(N)`.
2. The second line contains number of **children per node** `(m)` in the n-ary tree.
3. The third line contains number of **queries** `(Q)`.
4. Next `N` lines: Names of the nodes in level-order.
5. Next `Q` lines: Queries in the format:  
   `OperationType NodeName UserID`

### 📌 OperationType
- `1` → Lock
- `2` → Unlock
- `3` → UpgradeLock

---

## 🔧 Sample Input
```cpp
7
2
5
World
Asia
Africa
China
India
SouthAfrica
Egypt
1 China 9
1 India 9
3 Asia 9
2 India 9
2 Asia 9
```
## 🔧 Sample Output:
```cpp
true
true
true
false 
true
```
---

## 🧠 Explanation

- **Query 1:** `1 China 9` → ✅ *Success*. Initially unlocked.
- **Query 2:** `1 India 9` → ✅ *Success*. No ancestor/descendant locked.
- **Query 3:** `3 Asia 9` → ✅ *Success*. Asia is unlocked, has descendants locked by same user.
- **Query 4:** `2 India 9` → ❌ *Fail*. India was unlocked during upgrade.
- **Query 5:** `2 Asia 9` → ✅ *Success*. Asia was locked by the same user during upgrade.


