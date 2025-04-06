// main.cpp
#include "libs/include/sort.h"
#include "libs/tests/DataGenerator.h"

#include <iostream>
#include <string>
#include <fstream>


int main(int argc, char const *argv[]) {
    for (int d_type = 0; d_type < num_data_props; d_type++) {
        // std::ofstream logger("data/\" std::string(data_props[d_type]) + ".csv");
        // logger << "Sorting Algorithm,";
        for (int d_size = 0; d_size < num_data_sizes; d_size++) {
            for (int iter = 0; iter < 5; iter++) {
                // logger << data_sizes[d_size] << ' ' << '(' << iter + 1 << ')' << ',';

            }
            // logger << data_sizes[d_size] << " (Average),";
        }
    }

    /* code */
    return 0;
}
