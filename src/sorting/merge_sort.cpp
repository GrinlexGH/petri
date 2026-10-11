#include <vector>

#include "sort.hpp"

std::int64_t Merge(std::int32_t* l, const std::int32_t* mid, const std::int32_t* r) {
    const std::size_t n = r - l;
    std::vector tmp(n, 0);

    std::int64_t inv = 0;

    const std::int32_t* i = l;
    const std::int32_t* j = mid;
    std::int32_t* k = tmp.data();

    while (i != mid && j != r) {
        if (*i <= *j) {
            *k = *i;
            ++i;
        } else {
            inv += mid - i;
            *k = *j;
            ++j;
        }
        ++k;
    }

    while (i < mid) {
        *k = *i;
        ++i;
        ++k;
    }

    while (j < r) {
        *k = *j;
        ++j;
        ++k;
    }

    for (std::size_t q = 0; q < n; ++q) {
        *l = tmp[q];
        ++l;
    }

    return inv;
}

std::int64_t MergeSort(std::int32_t* l, std::int32_t* r) {
    if (r - l <= 1) {
        return 0;
    }

    std::int64_t inv = 0;
    inv += MergeSort(l, l + (r - l) / 2);
    inv += MergeSort(l + (r - l) / 2, r);
    inv += Merge(l, l + (r - l) / 2, r);
    return inv;
}
