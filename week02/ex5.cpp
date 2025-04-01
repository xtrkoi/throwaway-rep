#include <iostream>

int shortest_subarray(int nums[], int n, long long target) {
    long long partial_sum_array[n];
    partial_sum_array[0] = nums[0];
    for (int i = 1; i < n; i++)
        partial_sum_array[i] = partial_sum_array[i - 1] + nums[i];

    int min_length = n + 1;

    for (int l_border = 0; l_border < n; l_border++) {
        int left = l_border, right = n - 1;
        while (left <= right) {
            int mid = (left + right) / 2;

            long long subarray_sum = 
                partial_sum_array[mid] - (l_border == 0 ? 0LL : partial_sum_array[l_border - 1]);

            if (subarray_sum >= target) {
                int subarray_length = mid - l_border + 1;
                min_length = (min_length > subarray_length ? subarray_length : min_length);

                right = mid - 1;
            } else
                left = mid + 1;
        }
    }

    return (min_length <= n ? min_length : 0);
}

int shortest_subarray_two_ptr(int nums[], int n, long long target) {
    long long current_sum = 0;
    int min_length = n + 1;

    for (int left = 0, right = -1; left < n; left++) {
        while (current_sum < target && right + 1 < n)
            current_sum += nums[++right];
        
        if (current_sum < target)
            break;
        
        int subarray_length = right - left + 1;
        min_length = (min_length > subarray_length ? subarray_length : min_length);

        current_sum -= nums[left];
    }

    return (min_length <= n ? min_length : 0);
}

int main() {
    int n;
    std::cin >> n;

    int nums[n];
    for (int i = 0; i < n; i++)
        std::cin >> nums[i];

    long long target;
    std::cin >> target;


    int sub = shortest_subarray(nums, n, target);

    std::cout << sub << '\n';

    return 0;
}