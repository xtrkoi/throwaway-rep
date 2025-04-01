#include <iostream>

/// @brief Swap two integers
/// @param a A reference to integer a
/// @param b A reference to integer b
void swap_int(int &a, int &b) {
    int tmp = a;
    a = b, b = tmp;
}

/// @brief Sort an array in ascending order with Insertion Sort
/// @param a A pointer to the array of integers
/// @param n The number of integers in the array
void sort_insertion(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int j = i - 1;
        while (j >= 0 && a[j + 1] < a[j])
            swap_int(a[j], a[j + 1]), j--;
    }
}

/// @brief Finds the integer `k` with subarray `[L, R]`
/// @param a A pointer to the array of integers, sorted ascendingly
/// @param n The number of integers in the array
/// @param k The target integer
/// @param l_bound The left-most index of the subarray
/// @param r_bound The right-most index of the subarray
/// @return The index `i` where `L <= i <= R` and `a[i] == k`, `-1` if no such `i` exists
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

/// @brief A function that finds all zero-sum triplets, ordered and distinct
/// @param nums A pointer to the array
/// @param n The number of integers in the array
void find_all_zero_sum_triplets(int nums[], int n) {
    sort_insertion(nums, n);
    for (int i = 0; i < n; i++)
        std::cout << nums[i] << " \n"[i == n - 1];
    for (int i = 1; i < n - 1; i++) {
        if (i + 1 < n - 1 && nums[i] == nums[i + 1])
            continue;
        
        for (int j = 0; j < i; j++) {
            if (j + 1 < i && nums[j] == nums[j + 1])
                continue;
            
            int k = binary_search(nums, n, -nums[i] - nums[j], i + 1, n - 1);
            if (k != -1) {
                std::cout << '{' << nums[j] << ", " << nums[i] << ", " << nums[k] << "}\n";
            }
        }
    }
}

int main() {
    int n;
    std::cin >> n;

    int nums[n];
    for (int i = 0; i < n; i++)
        std::cin >> nums[i];
    
    find_all_zero_sum_triplets(nums, n);

    return 0;
}