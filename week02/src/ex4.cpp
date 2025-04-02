#include <iostream>

/// @brief Find the maximum value in an array of positive integers
/// @param a A pointer to the array
/// @param n Number of integers in the array
/// @return The maximum value in the array, `0` if the array is empty
int max_arr(int a[], int n) {
    if (n == 0)
        return 0;
    int max_value = a[0];
    for (int i = 1; i < n; i++)
        max_value = (max_value < a[i] ? a[i] : max_value);
    return max_value;
}

/// @brief Calculate the sum of all values in an array
/// @param a A pointer to the array
/// @param n Number of integers in the array
/// @return The sum of all values in the array
long long sum_arr(int a[], int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];
    return sum;
}

/// @brief A checker function that verifies if with given capacity can the ship deliever all packages in the specified amount of days
/// @param weights A pointer to the array containing the weights of all packages as positive integers
/// @param n Number of integers in the array
/// @param days The maximum number of days the ship can finish delievering
/// @param capacity The capacity of the ship
/// @return A binary value `true` if the ship can finish delievering within `days` days, `false` otherwise
bool fit_in_schedule(int weights[], int n, int days, long long capacity) {
    long long current_cap = capacity;
    for (int i = 0; i < n; i++) {
        if (current_cap < weights[i])
            days--, current_cap = capacity;
        current_cap -= weights[i];
    }
    return days > 0;
}

/// @brief A function that finds the minimum capacity of the ship so the ship can finish delievering all packges within specified amount of days, using binary search
/// @param weights A pointer to the array containing the weights of all packages as positive integers
/// @param n Number of integers in the array
/// @param days The maximum number of days the ship can finish delievering
/// @return The minimum capacity that satisfies the requirement
long long find_minimum_capacity(int weights[], int n, int days) {
    long long left = max_arr(weights, n), right = sum_arr(weights, n);
    long long min_cap = right;
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        if (fit_in_schedule(weights, n, days, mid))
            min_cap = mid, right = mid - 1;
        else
            left = mid + 1;
    }
    return min_cap;
}

int main() {
    int n;
    std::cin >> n;

    int weights[n];
    for (int i = 0; i < n; i++)
        std::cin >> weights[i];

    int days;
    std::cin >> days;


    std::cout << find_minimum_capacity(weights, n, days) << '\n';

    return 0;
}