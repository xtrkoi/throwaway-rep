// A program that finds the n-th Fibonacci number with recursion
#include <iostream>

// An array used for memoization
long long f[1000000];

/// @brief Find the n-th Fibonacci number with recursion
/// @param n 
/// @return N-th Fibonacci number
long long fibonacci(int n) {
    if (n != 0 && f[n] == 0) {
        if (n == 0)
            f[n] = 0;
        else if (n == 1)
            f[n] = 1;
        else
            f[n] = fibonacci(n - 2) + fibonacci(n - 1);
    }
    return f[n];
}

int main() {
    int n;
    std::cin >> n;
    fibonacci(n);
    for (int i = 0; i < n; i++)
        std::cout << f[i] << ' ';
    return 0;
}