// sort.h
#ifndef SORT_H
#define SORT_H

const int algo_names_len = 13;
extern const char * algo_names[algo_names_len];

namespace sort {
    long long bubble_sort(int *__first, int *__last);

    long long selection_sort(int *__first, int *__last);

    long long insertion_sort(int *__first, int *__last);

    long long merge_sort(int *__first, int *__last);

    long long merge_sort_iter(int *__first, int *__last);

    long long heap_sort(int *__first, int *__last);

    long long quick_sort(int *__first, int *__last);

    long long radix_sort(int *__first, int *__last);
    
    long long shell_sort(int *__first, int *__last);

    long long shaker_sort(int *__first, int *__last);

    long long counting_sort(int *__first, int *__last);

    long long flash_sort(int *__first, int *__last);
}

#endif