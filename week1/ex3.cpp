#include <iostream>
#include <string>

void generateBinaryStrings(int n, std::string str) {
    if (n == 0) {
        std::cout << str << '\n';
        return;
    }

    for (char c = '0'; c <= '1'; c++) {
        str += c;
        generateBinaryStrings(n - 1, str);
        str.pop_back();
    }
}

int main() {
    int n;
    std::cin >> n;
    generateBinaryStrings(n, "");
    return 0;
}