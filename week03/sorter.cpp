#include "libs/include/sort.h"
#include <algorithm>
#include <iostream>
#include <cstring>
#include <ctime>
#include <chrono>
#include <string>
#include <vector>
#include <iomanip>

bool is_option_flag(const char *s) {
    return strlen(s) > 0 && s[0] == '-';
}

bool is_help_command(const char *s) {
    return strcmp(s, "-help") == 0 || strcmp(s, "-h") == 0 || strcmp(s, "-?") == 0;
}

void display_help(const char *arg = "") {
    if (strlen(arg) == 0) {
        std::cout << "Option/Command: Description" << std::endl;
        // @todo: Add help messages
    } else {
        // @todo: Add help messages
    }
}

void display_unrecognized_command_error(const char *s) {
    std::cerr << "'" << s << "'" << " isn't a recognized option or command. Consider using '-help', '-h', or '-?' for a list of available options and commands.";
}

long long std_sort(int *__first, int *__last) {
    int comparisons = 0;
    std::sort(__first, __last, [&](int _v1, int _v2) {
        comparisons++;
        return _v1 < _v2;
    });
    return comparisons;
}

std::vector<std::string> algo_names = {
    "std-sort",
    "bubble-sort",
    "selection-sort",
    "insertion-sort",
    "merge-sort",
    "merge-sort-iter",
    "heap-sort",
    "quick-sort",
    "radix-sort",
    "shell-sort",
    "shaker-sort",
    "counting-sort",
    "flash-sort",
};

long long (*sort_algos[])(int *, int *) = {
    std_sort,
    sort::bubble_sort,
    sort::selection_sort,
    sort::insertion_sort,
    sort::merge_sort,
    sort::merge_sort_iter,
    sort::heap_sort,
    sort::quick_sort,
    sort::radix_sort,
    sort::shell_sort,
    sort::shaker_sort,
    sort::counting_sort,
    sort::flash_sort,
};

int get_sort_algo_id(const std::string &s) {
    for (int i = 0; i < (int)algo_names.size(); i++)
        if (algo_names[i] == s)
            return i;
    return -1;
}

int main(int argc, char const *argv[]) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long (*sort_algo)(int *, int *) = std_sort;
    std::string sort_algo_name = "std-sort";

    int arg_selector = 1;

    bool _a = false;
    bool _i = false;
    bool _o = false;

    // for (int i = 0; i < argc; i++)
    //     std::cout << argv[i] << '\n';
    
    while (arg_selector < argc) {
        if (!is_option_flag(argv[arg_selector])) {
            display_unrecognized_command_error(argv[arg_selector]);
            return EXIT_FAILURE;
        }

        // Display help
        if (is_help_command(argv[arg_selector])) {
            if (arg_selector == 1) {
                if (arg_selector + 1 < argc)
                    display_help(argv[arg_selector + 1]);
                else
                    display_help();
                return 0;
            } else {
                std::cerr << "The 'help' command can't be used in conjunction with other program's options.";
                return EXIT_FAILURE;
            }
        }

        // Sorting algorithm option
        if (strcmp(argv[arg_selector], "-a") == 0) {
            if (_a) {
                std::cerr << "Duplicate option: '-a'";
                return EXIT_FAILURE;
            }
            _a = true;

            sort_algo_name = argv[arg_selector + 1];
            int sort_algo_id = get_sort_algo_id(sort_algo_name);

            if (sort_algo_id == -1) {
                std::cerr << "Error '-a': " << sort_algo_name << " isn't a recognized sorting algorithm.";
                return EXIT_FAILURE;
            }

            sort_algo = sort_algos[sort_algo_id];

            arg_selector += 2;
        }

        // Change input source
        else if (strcmp(argv[arg_selector], "-i") == 0) {
            if (_i) {
                std::cerr << "Duplicate option: '-i'";
                return EXIT_FAILURE;
            }
            _i = true;

            if (!freopen(argv[arg_selector + 1], "r", stdin)) {
                std::cerr << "Error '-i': Failed to find or open " << argv[arg_selector + 1] << " for reading.";
                return EXIT_FAILURE;
            }

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

    int n;
    std::cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
        std::cin >> a[i];
    
    auto start = std::chrono::system_clock::now();

    long long num_of_ops = sort_algo(a, a + n);

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    for (int i = 0; i < n; i++)
        std::cout << a[i] << ' ';

    if (_i)
        std::fclose(stdin);
    if (_o)
        std::fclose(stdout);

    #define WRITE_TO_LOG 1
    #ifdef WRITE_TO_LOG
    
    freopen("sorter_log.log", "a", stderr);

    std::cerr << '\n';
    std::cerr << " * sorter.exe executed at " << std::ctime(&end_time) << '\n';
    std::cerr << "Sorting algorithm used: " << sort_algo_name << '\n';
    std::cerr << "Elapsed time: " << std::fixed << std::setprecision(6) << elapsed_seconds.count() << " (seconds)\n";
    std::cerr << "Number of comparisons: " << num_of_ops << std::endl;

    std::fclose(stderr);

    #endif

    return 0;
}
