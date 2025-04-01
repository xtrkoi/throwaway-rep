#include <iostream>

int max_arr(int a[], int n) {
    if (n == 0)
        return 0;
    int max_value = a[0];
    for (int i = 1; i < n; i++)
        max_value = (max_value < a[i] ? a[i] : max_value);
    return max_value;
}

long long sum_arr(int a[], int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];
    return sum;
}

bool fit_in_schedule(int weights[], int n, int days, long long capacity) {
    long long current_cap = capacity;
    for (int i = 0; i < n; i++) {
        if (current_cap < weights[i])
            days--, current_cap = capacity;
        current_cap -= weights[i];
    }
    return days > 0;
}

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