#include <iostream>

int linear_search(int a[], int n, int k) {
    for (int i = 0; i < n; i++)
        if (a[i] == k)
            return i;
    return -1;
}

int main() {
    int n;
    std::cin >> n;

    int a[n];
    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    int k;
    std::cin >> k;

    
    int position = linear_search(a, n, k);
    std::cout << position << '\n';
    
    return 0;
}