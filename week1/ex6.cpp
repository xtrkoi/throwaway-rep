#include <iostream>

int n_queens_solver(int n, int row, bool col[], bool diag1[], bool diag2[]) {
    if (row == n)
        return 1;
    int res = 0;
    for (int i = 0; i < n; i++)
        if (!col[i] && !diag1[row + i] && !diag2[row - i + (n - 1)]) {
            col[i] = diag1[row + i] = diag2[row - i + (n - 1)] = true;
            res += n_queens_solver(n, row + 1, col, diag1, diag2);
            col[i] = diag1[row + i] = diag2[row - i + (n - 1)] = false;
        }
    return res;
}

int main() {
    int n;
    std::cin >> n;
    bool *col = new bool[n], *diag1 = new bool[2 * n], *diag2 = new bool[2 * n];
    for (int i = 0; i < n; i++)
    col[i] = 0;
    for (int i = 0; i < 2 * n; i++)
        diag1[i] = diag2[i] = 0;
    std::cout << n_queens_solver(n, 0, col, diag1, diag2) << '\n';
    return 0;
}