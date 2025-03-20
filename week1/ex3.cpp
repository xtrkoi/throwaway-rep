// A program that generates all binary strings in increasing order
#include <iostream>
#include <string>

/// @brief Generate binary strings of length n
/// @param n The length of the binary strings
/// @param str Temporary variable that holds the string
void generateBinaryStrings(int n, std::string str = "") {
    if (n == 0) {
        std::cout << str << '\n';
        return;
    }

    for (char c : "01") {
        str += c;
        generateBinaryStrings(n - 1, str);
        str.pop_back();
    }
}

int main() {
    int n;
    std::cin >> n;
    generateBinaryStrings(n);
    return 0;
}