#include "../include/sort_util.h"

namespace sort_util {
    int distance(int *__first, int *__last) {
        return __last - __first;
    }

    void swap_int(int &__first, int &__last) {
        int __tmp = __first;
        __first = __last, __last = __tmp;
    }

    int *copy(int *__first, int *__last, int *__result) {
        while (__first != __last)
            *__result = *__first, ++__first, ++__result;
        return __result;
    }

    int max(int __v1, int __v2) {
        return (__v1 > __v2 ? __v1 : __v2);
    }

    long long merge(int *__first1, int *__last1, int *__first2, int *__last2, int *__result) {
        long long comparisons = 0;

        while (__first1 != __last1 && __first2 != __last2) {
            if (++comparisons, *__first2 < *__first1)
                *__result = *__first2, ++__first2;
            else
                *__result = *__first1, ++__first1;
            ++__result;
        }

        if (__first1 != __last1)
            sort_util::copy(__first1, __last1, __result);
        if (__first2 != __last2)
            sort_util::copy(__first2, __last2, __result);

        return comparisons;
    }

    /// @brief Middle pivot partition
    /// @param __first An iterator
    /// @param __last Another iterator
    /// @param __pivot Address of a pointer
    /// @return The number of comparisons
    long long partition(int *__first, int *__last, int **__pivot) {
        long long comparisons = 0;

        int __len = sort_util::distance(__first, __last);
        sort_util::swap_int(*(__last - 1), *(__first + __len / 2));
        *__pivot = __last - 1;
        int *__partitionIndex = __first;

        for (int *i = __first; i != __last; ++i) {
            if (++comparisons, *i < **__pivot) {
                sort_util::swap_int(*i, *__partitionIndex);
                ++__partitionIndex;
            }
        }

        sort_util::swap_int(**__pivot, *__partitionIndex);
        while (sort_util::distance(__first, __partitionIndex) < __len / 2 && (++comparisons, *__partitionIndex == *(__partitionIndex + 1)))
            ++__partitionIndex;
        while (sort_util::distance(__first, __partitionIndex) > __len / 2 && (++comparisons, *__partitionIndex == *(__partitionIndex - 1)))
            --__partitionIndex;
        *__pivot = __partitionIndex;

        return comparisons;
    } 

    long long __down_heap(int *__first, int __nodeIndex, int __len) {
        long long comparisons = 0;

        while (true) {
            int __leftChild = __nodeIndex * 2 + 1;
            int __rightChild = __nodeIndex * 2 + 2;
            int __largerNode = __nodeIndex;

            if (__leftChild < __len && (++comparisons, __first[__leftChild] > __first[__largerNode]))
                __largerNode = __leftChild;
            if (__rightChild < __len && (++comparisons, __first[__rightChild] > __first[__largerNode]))
                __largerNode = __rightChild;
            
            if (__largerNode == __nodeIndex)
                break;

            sort_util::swap_int(__first[__nodeIndex], __first[__largerNode]);
            __nodeIndex = __largerNode;
        }

        return comparisons;
    }

    long long __pop_heap(int *__first, int *__last) {
        long long comparisons = 0;

        if (__first == __last)
            return 0;

        sort_util::swap_int(*__first, *(__last - 1));

        comparisons += __down_heap(__first, 0, sort_util::distance(__first, __last) - 1);

        return comparisons;
    }

    long long __make_heap(int *__first, int *__last) {
        long long comparisons = 0;
        int __len = sort_util::distance(__first, __last);

        for (int __nodeIndex = (__len - 2) / 2; __nodeIndex >= 0; --__nodeIndex)
            comparisons += sort_util::__down_heap(__first, __nodeIndex, __len);

        return comparisons;
    }

    long long __r_counting_sort(int *__first, int *__last, int _digit_place) {
        const int BASE = 10;
        int _v_count[BASE] = {};

        for (int *i = __first; i != __last; ++i)
            _v_count[*i / _digit_place % 10]++;

        for (int i = 1; i < BASE; i++)
            _v_count[i] += _v_count[i - 1];

        int *aux = new int[sort_util::distance(__first, __last)];

        for (int *i = __last; i != __first; --i) {
            aux[_v_count[*(i - 1) / _digit_place % 10] - 1] = *(i - 1);
            _v_count[*(i - 1) / _digit_place % 10]--;
        }

        sort_util::copy(aux, aux + sort_util::distance(__first, __last), __first);
        delete[] aux;

        return 0;
    }
}