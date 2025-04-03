#include "DataGenerator.h"

#include <iostream>
#include <cstring>
#include <string>

bool is_option_flag(const char *s) {
    return strlen(s) > 0 && s[0] == '-';
}

void display_unrecognized_command_error(const char *s) {
    std::cerr << "'" << s << "'" << " isn't a recognized option.";
}

int main(int argc, char const *argv[]) {

    int data_size = 100;
    int data_property = 0;

    auto set_data_size = [&data_size](int v) -> void { data_size = v; };
    auto set_data_property = [&data_property](int t) -> void { data_property = t; };

    int arg_selector = 1;

    bool _s = false;
    bool _t = false;
    bool _o = false;

    // for (int i = 0; i < argc; i++)
    //     std::cout << argv[i] << '\n';
    

    while (arg_selector < argc) {
        if (!is_option_flag(argv[arg_selector])) {
            display_unrecognized_command_error(argv[arg_selector]);
            return EXIT_FAILURE;
        }

        if (strcmp(argv[arg_selector], "-s") == 0) {
            if (_s) {
                std::cerr << "Duplicate option: '-s'";
                return EXIT_FAILURE;
            }
            _s = true;

            set_data_size(std::stoi(argv[arg_selector + 1]));

            arg_selector += 2;
        }

        else if (strcmp(argv[arg_selector], "-t") == 0) {
            if (_t) {
                std::cerr << "Duplicate option: '-t'";
                return EXIT_FAILURE;
            }
            _t = true;

            set_data_property(std::stoi(argv[arg_selector + 1]));

            arg_selector += 2;
        }

        // Change output destination
        else if (strcmp(argv[arg_selector], "-o") == 0) {
            if (_o) {
                std::cerr << "Duplicate option: '-o'";
                return EXIT_FAILURE;
            }
            _o = true;

            if (!freopen(argv[arg_selector + 1], "w", stdout)) {
                std::cerr << "Error '-o': No such directory exists.";
                return EXIT_FAILURE;
            }

            arg_selector += 2;
        }

        else {
            display_unrecognized_command_error(argv[arg_selector]);
            return EXIT_FAILURE;
        }
    }
    
    int seq[data_size] = {};
    GenerateData(seq, data_size, data_property);

    // std::ios_base::sync_with_stdio(false);
    // std::cin.tie(nullptr);
    
    std::cout << data_size << '\n';
    for (int i = 0; i < data_size; i++)
    std::cout << seq[i] << ' ';
    std::cout << '\n';
    
    if (_o)
        std::fclose(stdout);

    return 0;
}
