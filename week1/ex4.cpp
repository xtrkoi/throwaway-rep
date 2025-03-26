// A program that solves the Tower of Hanoi puzzle
#include <iostream>

/// @brief A recursion function that finds an optimal solution to the Tower of Hanoi puzzle with n discs
/// @param n_discs number of discs
/// @param from the starting tower
/// @param to the ending tower
/// @param aux the middle tower
void tower_of_hanoi_solver(int n_discs, int from, int to, int aux) {
    if (n_discs == 1) {
        std::cout << "Disc " << n_discs << ": " << char(from + 'A') << "->" << char(to + 'A') << '\n';
        return;
    }
    tower_of_hanoi_solver(n_discs - 1, from, aux, to);
    std::cout << "Disc " << n_discs << ": " << char(from + 'A') << "->" << char(to + 'A') << '\n';
    tower_of_hanoi_solver(n_discs - 1, aux, to, from);
}

int main() {
    int n;
    std::cin >> n;
    tower_of_hanoi_solver(n, 0, 2, 1);
    return 0;
}