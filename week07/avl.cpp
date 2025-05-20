struct NODE {
    int key;
    NODE *p_left;
    NODE *p_right;
    int height;
    NODE() : key(0), p_left(nullptr), p_right(nullptr), height(0) {}
    NODE(int __k) : key(__k), p_left(nullptr), p_right(nullptr), height(0) {}
};

/* Auxilary functions */
int abs(int x) { return x > 0 ? x : -x; }
int max(int a, int b) { return a > b ? a : b; }
void swap(int &a, int &b) { int &c = b; return b = a, void(a = c); }

int balance(NODE *p) {
    int left = (p->p_left != nullptr ? p->p_left->height : -1);
    int right = (p->p_right != nullptr ? p->p_right->height : -1);
    return left - right;
}

void update_height(NODE *p) {
    if (!p)
        return;
    p->height = max(p->p_left != nullptr ? p->p_left->height : -1, p->p_right != nullptr ? p->p_right->height : -1) + 1;
}

NODE *rotate_left(NODE *p) {
    NODE *child = p->p_left;
    p->p_left = child->p_right;
    child->p_right = p;
    update_height(p);
    update_height(child);
    return child;
}

NODE *rotate_right(NODE *p) {
    NODE *child = p->p_right;
    p->p_right = child->p_left;
    child->p_left = p;
    update_height(p);
    update_height(child);
    return child;
}

void rebalance(NODE *&pRoot) {
    update_height(pRoot);

    if (balance(pRoot) > 1) {
        if (balance(pRoot->p_left) == 1)
            pRoot = rotate_left(pRoot);
        else
            pRoot->p_left = rotate_right(pRoot->p_left), pRoot = pRoot = rotate_left(pRoot);
    } else if (balance(pRoot) < -1) {
        if (balance(pRoot->p_right) == -1)
            pRoot = rotate_right(pRoot);
        else
            pRoot->p_right = rotate_left(pRoot->p_right), pRoot = rotate_right(pRoot);
    }
}

/* End of Auxilary functions */

NODE *createNode(int data) {
    return new NODE(data);
}

void Insert(NODE *&pRoot, int x) {
    if (!pRoot)
        pRoot = new NODE(x);
    else if ((x < pRoot->key ? pRoot->p_left : pRoot->p_right) != nullptr) {
        Insert((x < pRoot->key ? pRoot->p_left : pRoot->p_right), x);
    }
    else {
        (x < pRoot->key ? pRoot->p_left : pRoot->p_right) = new NODE(x);
    }

    rebalance(pRoot);
} 

void Remove(NODE *&pRoot, int x) {
    if (!pRoot)
        return;

    if (x < pRoot->key) {
        Remove(pRoot->p_left, x);
    } else if (x > pRoot->key) {
        Remove(pRoot->p_right, x);
    } else {
        if (!pRoot->p_left || !pRoot->p_right) {
            NODE *child = (pRoot->p_left ? pRoot->p_left : pRoot->p_right);
            delete pRoot;
            pRoot = child;
        } else {
            NODE *successor = pRoot->p_right;
            while (successor->p_left != nullptr || successor->p_right != nullptr)
                successor = successor->p_right != nullptr ? successor->p_right : successor->p_left;
            pRoot->key = successor->key;
            Remove(pRoot->p_right, successor->key);
        }
    }

    rebalance(pRoot);
}

bool isAVL(NODE *pRoot) {
    if (!pRoot)
        return true;
    if (pRoot->p_left && pRoot->p_left->key > pRoot->key)
        return false;
    if (pRoot->p_right && pRoot->key > pRoot->p_right->key)
        return false;
    return (abs(balance(pRoot)) < 2) && isAVL(pRoot->p_left) && isAVL(pRoot->p_right);
}