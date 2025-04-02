#include <iostream>

/// @brief Find the minimum integer in a rotated array with unique elements
/// @param a A pointer to the array. The array must contain unique elements and be sorted before rotated.
/// @param n Number of integers allocated by the array
/// @return The index `i` where `a[i]` is the smallest integer in the array
int find_min_rotated(int a[], int n) {
    int left = 0, right = n - 1;
    int first_position = -1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (a[mid] <= a[n - 1])
            first_position = mid, right = mid - 1;
        else
            left = mid + 1;
    }
    return first_position;
}

int main() {
    int n;
    std::cin >> n;

    int a[n];
    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    
    std::cout << a[find_min_rotated(a, n)] << '\n';

    return 0;
}