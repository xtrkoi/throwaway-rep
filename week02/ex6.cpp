#include <iostream>

int binary_search(int a[], int n, int k, int l_bound, int r_bound) {
    int left = (l_bound < 0 ? 0 : l_bound), right = (r_bound > n - 1 ? n - 1 : r_bound);
    while (left <= right) {
        int mid = (left + right) / 2;
        if (a[mid] == k)
            return mid;

        if (a[mid] < k)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}

bool find_pair_of_given_sum(int a[], int n, int target) {
    for (int i = 0; i < n - 1 && a[i] < target; i++) {
        if (binary_search(a, n, target - a[i], i, n - 1) != -1)
            return true;
    }
    return false;
}

bool find_pair_of_given_sum_two_ptr(int a[], int n, int target) {
    for (int left = 0, right = n - 1; left < right; left++) {
        while (left < right && a[left] + a[right] > target)
            right--;
        
        if (left == right)
            return false;
        
        if (a[left] + a[right] == target)
            return true;
    }
    return false;
}

int main() {
    int n;
    std::cin >> n;

    int a[n];
    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    int target;
    std::cin >> target;


    bool found_pair = find_pair_of_given_sum(a, n, target);
    std::cout << (found_pair ? "YES" : "NO") << '\n';

    return 0;
}