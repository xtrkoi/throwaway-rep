#include <vector>

struct NODE {
    int key;
    NODE *p_left;
    NODE *p_right;

    NODE() : key(0), p_left(nullptr), p_right(nullptr) {}
    NODE(int __k) : key(__k), p_left(nullptr), p_right(nullptr) {}
};

// 1.
NODE *createNode(int data) { return new NODE(data); }

// 2. Pre-order
std::vector<int> NLR(NODE *pRoot) {
    if (!pRoot)
        return std::vector<int>();
    std::vector<int> traversal(1, pRoot->key);
    traversal.emplace_back(NLR(pRoot->p_left));
    traversal.emplace_back(NLR(pRoot->p_right));
    return traversal;
}

// 3. In-order
std::vector<int> LNR(NODE *pRoot) {
    if (!pRoot)
        return std::vector<int>();
    std::vector<int> traversal;
    traversal.emplace_back(LNR(pRoot->p_left));
    traversal.push_back(pRoot->key);
    traversal.emplace_back(LNR(pRoot->p_right));
    return traversal;
}

// 4. Post-order
std::vector<int> LRN(NODE *pRoot) {
    if (!pRoot)
        return std::vector<int>();
    std::vector<int> traversal;
    traversal.emplace_back(LRN(pRoot->p_left));
    traversal.emplace_back(LRN(pRoot->p_right));
    traversal.push_back(pRoot->key);
    return traversal;
}

// 5.
std::vector<std::vector<int>> LevelOrder(NODE *pRoot) {
    if (!pRoot)
        return std::vector<std::vector<int>>();

    std::vector<std::vector<NODE *>> traversal_pointers(1, std::vector<NODE *>(1, pRoot));
    std::vector<std::vector<int>> traversal(1, std::vector<int>(1, pRoot->key));

    bool traversing = true;
    do {
        std::vector<NODE *> new_layer_pointers;
        std::vector<int> new_layer;
        for (NODE *p : traversal_pointers.back()) {
            if (p->p_left)
                new_layer_pointers.push_back(p->p_left), new_layer.push_back(p->p_left->key);
            if (p->p_right)
                new_layer_pointers.push_back(p->p_right), new_layer.push_back(p->p_right->key);
        }
        if (new_layer.empty())
            traversing = false;
        else
            traversal_pointers.push_back(new_layer_pointers), traversal.push_back(new_layer);
    } while (traversing);
    return traversal;
}

// 6.
int countNode(NODE *pRoot) {
    if (!pRoot)
        return 0;
    return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}

// 7.
int sumNode(NODE *pRoot) {
    if (!pRoot)
        return 0;
    return pRoot->key + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}

// 8.
int heightNode(NODE *pRoot, int value) {
    if (!pRoot)
        return -1;
    if (pRoot->key == value)
        return std::max(heightNode(pRoot->p_left, pRoot->p_left->key), heightNode(pRoot->p_right, pRoot->p_right->key)) + 1;
    return -1;
}

// 9.
int Level(NODE *pRoot, NODE *p) {
    if (!pRoot)
        return -1;
    if (p == pRoot)
        return 0;
    if (int l = Level(pRoot->p_left, p); l >= 0)
        return l + 1;
    if (int l = Level(pRoot->p_right, p); l >= 0)
        return l + 1;
    return -1;
}

// 10.
int countLeaf(NODE *pRoot) {
    if (!pRoot)
        return 0;
    return std::max(1, countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right));
}