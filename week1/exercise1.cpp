#include <iostream>

long long f[100000];

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
    fibonacci(5);
    for (int i = 0; i < 5; i++)
        std::cout << f[i] << ' ';
    return 0;
}