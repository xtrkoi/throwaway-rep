// main.cpp
#include "libs/include/sort.h"
#include "libs/tests/DataGenerator.h"

#include <iostream>
#include <string>
#include <fstream>

const char *tmp_path = ".\\util\\tmp";

void create_data(const std::string &data_type, const int data_size) {
    std::system((".\\bin\\datagen -o .\\util\\input.txt -s " + std::to_string(data_size) + " -t " + data_type).c_str());
}

void perform_sort(const std::string &algo_name) {
    std::system((".\\bin\\sorter -a " + algo_name + " -i .\\util\\input.txt -o .\\util\\" + algo_name + ".txt -tmp .\\util\\tmp").c_str());
}

int compare(const std::string &algo_name) {
    return std::system(("fc .\\util\\answer.txt .\\util\\" + algo_name + ".txt").c_str());
}

int main() {
    std::ofstream logger("data/benchmark.csv");
    if (!logger.is_open())
        return EXIT_FAILURE;
    logger << "Sorting Algorithm,Data Size,Data Type,Running Time (ms),Number of Comparisons,Validity\n";

    for (int d_size = 0; d_size < 6; d_size++) {
        for (int d_type = 0; d_type < num_data_props; d_type++) {
            create_data(data_props[d_type], data_sizes[d_size]);
            std::system(".\\bin\\sorter -a std-sort -i .\\util\\input.txt -o .\\util\\answer.txt -tmp .\\util\\tmp");

            for (int i_algo = 0; i_algo < algo_names_len; i_algo++) {
                // if (is_quadratic[i_algo] && data_sizes[d_size] >= 200'000)
                //     continue;

                perform_sort(algo_names[i_algo]);

                long long running_time, comparisons;
                std::ifstream get_data(".\\util\\tmp");
                if (get_data.is_open()) {
                    get_data >> running_time >> comparisons;
                    get_data.close();
                }

                logger  << algo_names[i_algo] << ',' 
                        << data_sizes[d_size] << ',' 
                        << data_props[d_type] << ',' 
                        << running_time << ',' 
                        << comparisons << ',' 
                        << (compare(algo_names[i_algo]) == 0 ? "Correct" : "Wrong") << std::endl;
            }
        }
    }

    /* code */
    return 0;
}
