#ifndef SORT_UTIL_H
#define SORT_UTIL_H

namespace sort_util {
    int distance(int *__first, int *__last);

    void swap_int(int &__first, int &__last);

    int *copy(int *__first, int *__last, int *__result);

    int max(int __v1, int __v2);

    // Merge Sort ultilities

    long long merge(int *__first1, int *__last1, int *__first2, int *__last2, int *__result);

    // Quick Sort utilities

    long long partition(int *__first, int *__last, int **__pivot);

    // Heap Sort utilities

    long long __down_heap(int *__first, int __nodeIndex, int __len);
    
    long long __pop_heap(int *__first, int *__last);

    long long __make_heap(int *__first, int *__last);

    // Radix Sort utilities

    long long __r_counting_sort(int *__first, int *__last, int _digit_place);
}

#endif