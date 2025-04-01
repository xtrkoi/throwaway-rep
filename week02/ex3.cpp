#include <iostream>

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