#include <iostream>

void towers_of_hanoi_solver(int n_discs, int from, int to, int aux) {
    if (n_discs == 1) {
        std::cout << "Disc " << n_discs << ": " << from << "->" << to << '\n';
        return;
    }
    towers_of_hanoi_solver(n_discs - 1, from, aux, to);
    std::cout << "Disc " << n_discs << ": " << from << "->" << to << '\n';
    towers_of_hanoi_solver(n_discs - 1, aux, to, from);
}

int main() {
    int n;
    std::cin >> n;
    towers_of_hanoi_solver(n, 0, 2, 1);
    return 0;
}