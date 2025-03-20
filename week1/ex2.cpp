// A program that finds the n factorial (n!)
#include <iostream>

/// @brief Find n factorial (n!)
/// @param n 
/// @return n factorial (n!)
long long factorial(int n) {
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}

int main() {
    int n;
    std::cin >> n;
    std::cout << factorial(n) << std::endl;
    return 0;
}