#include "../include/sort.h"
#include "../include/sort_util.h"

const char * algo_names[algo_names_len] = {
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

const bool is_quadratic[algo_names_len] = {
    false,
    true,
    true,
    true,
    false,
    false,
    false,
    false,
    false,
    false,
    true,
    false,
    false,
};

namespace sort {
    long long bubble_sort(int *__first, int *__last) {
        if (__first == __last)
            return 0;

        long long comparisons = 0;
        
        /// Optimized Bubble Sort (https://https://en.wikipedia.org/wiki/Bubble_sort#Optimizing_bubble_sort)
        int *new_i = __first;

        for (int *i = __last; i != __first; i = new_i) {
            new_i = __first;
            for (int *j = __first; sort_util::distance(j, i) > 1; ++j)
                if (++comparisons, *(j + 1) < *j) {
                    sort_util::swap_int(*j, *(j + 1));
                    new_i = j + 1;
                }
        }

        return comparisons;
    }
    
    long long selection_sort(int *__first, int *__last) {
        if (__first == __last)
            return 0;

        long long comparisons = 0;
        
        for (int *i = __first; i != __last; ++i) {
            int *min_ptr = i;
            for (int *j = i + 1; j != __last; ++j)
                if (++comparisons, *j < *min_ptr)
                    min_ptr = j;

            sort_util::swap_int(*i, *min_ptr);
        }

        return comparisons;
    }
    
    long long insertion_sort(int *__first, int *__last) {
        if (__first == __last)
            return 0;

        long long comparisons = 0;

        for (int *i = __first + 1; i != __last; ++i)
            for (int *j = i; j != __first; --j) {
                if (++comparisons, *j < *(j - 1))
                    sort_util::swap_int(*j, *(j - 1));
                else
                    break;
            }

        return comparisons;
    }
    
    long long merge_sort(int *__first, int *__last) {
        if (__first == __last)
            return 0;

        long long comparisons = 0;
        
        int D = sort_util::distance(__first, __last);
        if (D <= 1)
            return 0;

        int *aux = new int[D];

        comparisons += merge_sort(__first, __first + D / 2);
        comparisons += merge_sort(__first + D / 2, __last);
        comparisons += sort_util::merge(__first, __first + D / 2, __first + D / 2, __last, aux);

        sort_util::copy(aux, aux + D, __first);

        delete[] aux;

        return comparisons;
    }

    long long merge_sort_iter(int *__first, int *__last) {
        if (__first == __last)
            return 0;

        int __len = sort_util::distance(__first, __last);
        long long comparisons = 0;
        int *aux = new int[__len];

        for (int D = 1; D < __len; D *= 2)
            for (int *p = __first, *p_aux = aux; sort_util::distance(p + D, __last) > 0; p += D * 2, p_aux += D * 2) {
                int *_right = (sort_util::distance(p + D, __last) >= D ? p + D * 2 : __last);

                comparisons += sort_util::merge(p, p + D, p + D, _right, p_aux);
                sort_util::copy(p_aux, p_aux + sort_util::distance(p, _right), p);
            }

        delete[] aux;

        return comparisons;
    }
    
    long long heap_sort(int *__first, int *__last) {
        if (__first == __last)
            return 0;

        long long comparisons = 0;

        comparisons += sort_util::__make_heap(__first, __last);
        
        while (__first != __last)
            comparisons += sort_util::__pop_heap(__first, __last--);

        return comparisons;
    }
    
    long long quick_sort(int *__first, int *__last) {
        if (__first == __last)
            return 0;

        // Hybrid
        if (sort_util::distance(__first, __last) <= 8)
            return sort::selection_sort(__first, __last);

        long long comparisons = 0;
                
        int *p = nullptr;
        comparisons += sort_util::partition(__first, __last, &p);
        
        // Tail recursion
        if (sort_util::distance(__first, p) < sort_util::distance(p, __last)) {
            comparisons += quick_sort(__first, p);
            comparisons += quick_sort(p + 1, __last);
        } else {
            comparisons += quick_sort(p + 1, __last);
            comparisons += quick_sort(__first, p);
        }

        return comparisons;
    }
    
    long long radix_sort(int *__first, int *__last) {
        if (__first == __last)
            return 0;

        long long comparisons = 0;
        
        int max_value = -1;
        for (int *i = __first; i != __last; ++i)
            if (++comparisons, max_value < *i)
                max_value = *i;
        
        for (int _digit_place = 1; max_value / _digit_place > 0; _digit_place *= 10) {
            sort_util::__r_counting_sort(__first, __last, _digit_place);
        }

        return comparisons;
    }

    /// @brief Shell sort, with (3^k - 1) / 2 gaps, runs in \Theta(N^{3/2})
    /// @param __first 
    /// @param __last 
    /// @return 
    long long shell_sort(int *__first, int *__last) {
        if (__first == __last)
            return 0;

        long long comparisons = 0;
        int __len = sort_util::distance(__first, __last);
        
        int gap = 1;
        while (gap < __len / 3)
            gap = gap * 3 + 1;
        
        while (gap > 0) {
            for (int *i = __first + gap; i != __last; ++i)
                for (int *j = i; sort_util::distance(__first, j) >= gap && (++comparisons, *j < *(j - gap)); j -= gap)
                    sort_util::swap_int(*(j - gap), *j);

            gap /= 3;
        }

        return comparisons;
    }

    long long shaker_sort(int *__first, int *__last) {
        if (__first == __last)
            return 0;

        long long comparisons = 0;

        while (__first < __last) {
            int *__n_first = __last;
            int *__n_last = __first;

            for (int *i = __first; sort_util::distance(i, __last) > 1; ++i) {
                if (++comparisons, *(i + 1) < *i) {
                    sort_util::swap_int(*i, *(i + 1));
                    __n_last = i + 1;
                }
            }
            
            __last = __n_last;
            for (int *i = __last; sort_util::distance(__first, i) > 1; --i) {
                if (++comparisons, *(i - 1) < *(i - 2)) {
                    sort_util::swap_int(*(i - 2), *(i - 1));
                    __n_first = i - 2;
                }
            }

            __first = ++__n_first;
        }
        
        return comparisons;
    }

    long long counting_sort(int *__first, int *__last) {
        if (__first == __last)
            return 0;

        long long comparisons = 0;

        int min_value = *__first, max_value = *__first;
        for (int *i = __first; i != __last; ++i) {
            if (++comparisons, *i < min_value)
                min_value = *i;
            if (++comparisons, max_value < *i)
                max_value = *i;
        }
        
        int _size = max_value - min_value + 1;
        int *_v_count = new int[_size];

        for (int i = 0; i < _size; i++)
            _v_count[i] = 0;

        for (int *i = __first; i != __last; ++i)
            _v_count[*i - min_value]++;
        
        for (int i = 0; i < _size; i++)
            while (_v_count[i] > 0)
                *__first = i + min_value, ++__first, _v_count[i]--;

        delete[] _v_count;
        
        return comparisons;
    }

    long long flash_sort(int *__first, int *__last) {
        if (__first == __last)
            return 0;

        long long comparisons = 0;

        int min_value = *__first, max_value = *__first;
        for (int *i = __first; i != __last; ++i) {
            if (++comparisons, *i < min_value)
                min_value = *i;
            if (++comparisons, max_value < *i)
                max_value = *i;
        }

        if (min_value == max_value)
            return 0;
        
        int __len = sort_util::distance(__first, __last);
        int m = sort_util::max((int)(0.45 * __len), 1);

        auto get_bucket_id = [&m, &min_value, &max_value](int __value) -> int {
            return int(((double)m * (__value - min_value)) / (max_value - min_value + 1));
        };
        
        int *__bucket_size = new int[m];
        for (int i = 0; i < m; i++)
            __bucket_size[i] = 0;

        for (int *i = __first; i != __last; ++i)
            __bucket_size[get_bucket_id(*i)]++;
        
        for (int i = 1; i < m; i++)
            __bucket_size[i] += __bucket_size[i - 1];
        
        auto find_swap_index = [&__bucket_size, &get_bucket_id, &__first](int __bucket_id) -> int {
            int i;
            for (i = __bucket_size[__bucket_id - 1]; i < __bucket_size[__bucket_id]; ++i)
                if (get_bucket_id(*(__first + i)) != __bucket_id)
                    break;
            return i;
        };

        auto arrange_bucket = [&__first, &get_bucket_id, &find_swap_index](int l, int r, int v) -> void {
            for (int i = l; i < r; i++) {
                int __bucket_id = get_bucket_id(*(__first + i));
                while (__bucket_id != v) {
                    int swap_index = find_swap_index(__bucket_id);
                    sort_util::swap_int(*(__first + i), *(__first + swap_index));
                    __bucket_id = get_bucket_id(*(__first + i));
                }
            }
        };

        for (int i = 0; i < m - 1; i++) {
            if (i == 0)
                arrange_bucket(0, __bucket_size[i], i);
            else
                arrange_bucket(__bucket_size[i - 1], __bucket_size[i], i);
        }

        for (int i = 0; i < m; i++) {
            if (i == 0)
                comparisons += sort::insertion_sort(__first, __first + __bucket_size[i]);
            else
                comparisons += sort::insertion_sort(__first + __bucket_size[i - 1], __first + __bucket_size[i]);
        }

        delete[] __bucket_size;
        
        return comparisons;
    }
}