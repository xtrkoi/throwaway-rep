#include <iostream>

/// @brief Find the integer `k` in the array `a[]` with `n` integers in linear time
/// @param a A pointer to the array
/// @param n Number of integers allocated by the array
/// @param k The specified integer
/// @return The index `i` where `a[i] == k`, or `-1` if such integer doesn't exist
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