// A program that verify if an array is sorted ascendingly
#include <iostream>

/// @brief Verify if an array is sorted with recursion
/// @param a array pointer
/// @param n length of array
/// @return True if array is sorted, False otherwise
bool is_sorted(int a[], int n) {
    if (n <= 1)
        return true;
    return is_sorted(a, n - 1) && a[n - 2] <= a[n - 1];
}

int main() {
    int n;
    std::cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++)
        std::cin >> a[i];
    std::cout << (is_sorted(a, n) ? "The array is sorted" : "The array isn't sorted");
    return 0;
}