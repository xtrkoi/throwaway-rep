struct NODE {
    int key;
    NODE *p_left;
    NODE *p_right;

    NODE() : key(0), p_left(nullptr), p_right(nullptr) {}
    NODE(int __k) : key(__k), p_left(nullptr), p_right(nullptr) {}
};

/* Auxilary functions */

int max(int a, int b) { return a > b ? a : b; }
void swap(int &a, int &b) { int &c = b; return b = a, void(a = c); }

/* End of Auxilary functions */

NODE *Search(NODE *pRoot, int x) {
    if (!pRoot)
        return nullptr;
    if (pRoot->key == x)
        return pRoot;
    return (x < pRoot->key ? Search(pRoot->p_left, x) : Search(pRoot->p_right, x));
}

void Insert(NODE *&pRoot, int x) {
    if (!pRoot)
        pRoot = new NODE(x);
    else if ((x < pRoot->key ? pRoot->p_left : pRoot->p_right) != nullptr)
        Insert((x < pRoot->key ? pRoot->p_left : pRoot->p_right), x);
    else
        (x < pRoot->key ? pRoot->p_left : pRoot->p_right) = new NODE(x);
}

/// @todo A mess right now, please fix
void Remove(NODE *&pRoot, int x) {
    if (!pRoot)
        return;

    if (x < pRoot->key) {
        Remove(pRoot->p_left, x);
        return;
    }

    if (x > pRoot->key) {
        Remove(pRoot->p_right, x);
        return;
    }

    /// Unneeded, see the next case
    // if (!pRoot->p_left && !pRoot->p_right) {
    //     delete pRoot;
    //     pRoot = nullptr;
    //     return;
    // }

    if (!pRoot->p_left || !pRoot->p_right) {
        // If pRoot is a leaf (both children are `nullptr`) then `child` would be `nullptr` as well, same as the above
        NODE *child = (pRoot->p_left ? pRoot->p_left : pRoot->p_right);
        delete pRoot;
        pRoot = child;
        return;
    }

    NODE *successor = pRoot->p_right;
    while (successor->p_left != nullptr || successor->p_right != nullptr)
        successor = successor->p_right != nullptr ? successor->p_right : successor->p_left;
    pRoot->key = successor->key;
    Remove(pRoot->p_right, successor->key);
}

NODE *createTree(int a[], int n) {
    if (n <= 0)
        return nullptr;
    if (n == 1)
        return new NODE(a[0]);

    int mid = n / 2;

    // Inline quick-sort partition
    {
        int i = 0, j = n - 1;
        while (i < j) {
            while (a[i] <= a[mid]) i++;
            while (a[j] >= a[mid]) j--;
            if (i >= j)
                break;
            swap(a[i], a[j]);
        }
        mid = j;
    }
    NODE *pRoot = new NODE(a[mid]);
    pRoot->p_left = createTree(a, mid);
    pRoot->p_right = createTree(a + mid + 1, n - mid - 1);
}

void removeTree(NODE *&pRoot) {
    if (!pRoot)
        return;
    removeTree(pRoot->p_left);
    removeTree(pRoot->p_right);
    delete pRoot;
    pRoot = nullptr;
}

int Height(NODE *pRoot) {
    if (!pRoot)
        return 0;
    
    return 1 + max(Height(pRoot->p_left), Height(pRoot->p_right));
}

int countLess(NODE *pRoot, int x) {
    if (!pRoot)
        return 0;
    
    return countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x) + (pRoot->key < x);
}

int countGreater(NODE *pRoot, int x) {
    if (!pRoot)
        return 0;
    
    return countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x) + (pRoot->key > x);
}

bool isBST(NODE *pRoot) {
    if (!pRoot)
        return true;
    if (pRoot->p_left && pRoot->p_left->key > pRoot->key)
        return false;
    if (pRoot->p_right && pRoot->key > pRoot->p_right->key)
        return false;
    return isBST(pRoot->p_left) && isBST(pRoot->p_right);
}

bool isFullBST(NODE *pRoot) {
    if (!pRoot)
        return true;
    if ((pRoot->p_left != nullptr) != (pRoot->p_right != nullptr))
        return false;
    if (pRoot->p_left && pRoot->p_left->key > pRoot->key)
        return false;
    if (pRoot->p_right && pRoot->key > pRoot->p_right->key)
        return false;
    return isFullBST(pRoot->p_left) && isFullBST(pRoot->p_right);
}