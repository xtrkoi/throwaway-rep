// main.cpp
#include "libs/include/sort.h"
#include "libs/tests/DataGenerator.h"

#include <iostream>
#include <string>
#include <fstream>

const char *tmp_path = ".\\data\\tmp";

void create_data(const std::string &data_type, const int data_size) {
    std::system((".\\bin\\datagen -o .\\data\\input.txt -s " + std::to_string(data_size) + " -t " + data_type).c_str());
}

void perform_sort(const std::string &algo_name) {
    std::system((".\\bin\\sorter -a " + algo_name + " -i .\\data\\input.txt -o .\\data\\outputs\\" + algo_name + ".txt -tmp .\\data\\tmp").c_str());
}

int compare(const std::string &algo_name) {
    return std::system(("fc .\\data\\answer.txt .\\data\\outputs\\" + algo_name + ".txt").c_str());
}

int main() {
    
    for (int d_type = 0; d_type < num_data_props; d_type++) {
        std::ofstream time_logger("data/benchmarks/time_" + std::string(data_props[d_type]) + ".csv");
        std::ofstream comp_logger("data/benchmarks/comp_" + std::string(data_props[d_type]) + ".csv");

        if (!time_logger.is_open() || !comp_logger.is_open())
            return EXIT_FAILURE;

        time_logger << "Data size,";
        comp_logger << "Data size,";

        for (int i = 0; i < algo_names_len; i++) {
            time_logger << algo_names[i] << ",";
            comp_logger << algo_names[i] << ",";
        }
        time_logger << std::endl;
        comp_logger << std::endl;

        for (int d_size = 0; d_size < num_data_sizes; d_size++) {
            create_data(data_props[d_type], data_sizes[d_size]);
            std::system(".\\bin\\sorter -a std-sort -i .\\data\\input.txt -o .\\data\\answer.txt -tmp .\\data\\tmp");
            
            time_logger << data_sizes[d_size] << ',';
            comp_logger << data_sizes[d_size] << ',';
            
            for (int i_algo = 0; i_algo < algo_names_len; i_algo++) {
                if (!is_quadratic[i_algo] || data_sizes[d_size] <= 200'000)
                    perform_sort(algo_names[i_algo]);

                long long running_time, comparisons;

                std::ifstream get_data(".\\data\\tmp");
                if (get_data.is_open()) {
                    get_data >> running_time >> comparisons;
                    get_data.close();
                }

                if ((is_quadratic[i_algo] && data_sizes[d_size] > 200'000) || compare(algo_names[i_algo]) != 0)
                    running_time = -1, comparisons = 0;

                time_logger << running_time << ',';
                comp_logger << comparisons << ',';
            }

            time_logger << std::endl;
            comp_logger << std::endl;
        }
        time_logger.close();
        comp_logger.close();
    }

    /* code */
    return 0;
}
